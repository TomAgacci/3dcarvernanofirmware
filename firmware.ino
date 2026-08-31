// ============================================================
// 6-SIDED CARVING MACHINE — FINAL FIRMWARE FILE (.ino)
// Architecture A: Single Driver + Selector + 6 CNC-V3 Boards × 4 Motors
// ============================================================

#include <Arduino.h>
#include <math.h>

// -------------------- PIN DEFINITIONS --------------------
const uint8_t PIN_STEP   = 2;
const uint8_t PIN_DIR    = 3;
const uint8_t PIN_ENABLE = 4;

const uint8_t PIN_SEL0   = 5;
const uint8_t PIN_SEL1   = 6;
const uint8_t PIN_SEL2   = 7;
const uint8_t PIN_SEL3   = 8;

const uint8_t PIN_KILL   = 9;
const uint8_t BROADCOM_EMF_PIN = A0;

// -------------------- GLOBAL FLAGS --------------------
volatile bool killTriggered = false;

// -------------------- GEOMETRY / BUILD AREA --------------------
const float STYLUS_LENGTH_MM = 80.0f;

float blockX = 120.0f;
float blockY = 120.0f;
float blockZ = 120.0f;

// tune this to your mechanics
const float STEPS_PER_MM = 400.0f;

// Thickness thresholds
const float THIN_THRESHOLD_MM = 10.0f;
const float MID_THRESHOLD_MM  = 30.0f;

// -------------------- MOTOR MODEL --------------------
enum MotorRole : uint8_t {
  MOTOR_COREXY_A,
  MOTOR_COREXY_B,
  MOTOR_STYLUS,
  MOTOR_DEPTH
};

struct Motor {
  uint8_t   id;
  uint8_t   selCode;
  MotorRole role;
  long      remaining;
};

const uint8_t NUM_MOTORS = 24;
Motor motors[NUM_MOTORS];

// Per-motor speed (steps per second)
uint16_t motorSpeed[NUM_MOTORS];

// Side mapping: 6 sides, 4 motors each
struct Side {
  uint8_t coreA;
  uint8_t coreB;
  uint8_t stylus;
  uint8_t depth;
};

Side sides[6];

// Expected depth for recentering
long expectedDepth[6];

// -------------------- BROADCOM EMF / RESISTANCE --------------------
const int EMF_THRESHOLD = 40;
const uint8_t EMF_SAMPLE_DELAY_US = 20;

int readBroadcomEMF() {
  delayMicroseconds(EMF_SAMPLE_DELAY_US);
  return analogRead(BROADCOM_EMF_PIN);
}

bool detectResistance(uint8_t motorID) {
  selectMotor(motors[motorID].selCode);
  pulseStep(true);
  int emf = readBroadcomEMF();
  return (emf < EMF_THRESHOLD);
}

// -------------------- SELECTOR + PULSE --------------------
void selectMotor(uint8_t selCode) {
  digitalWrite(PIN_SEL0, (selCode & 0x01) ? HIGH : LOW);
  digitalWrite(PIN_SEL1, (selCode & 0x02) ? HIGH : LOW);
  digitalWrite(PIN_SEL2, (selCode & 0x04) ? HIGH : LOW);
  digitalWrite(PIN_SEL3, (selCode & 0x08) ? HIGH : LOW);
}

void pulseStep(bool dir) {
  digitalWrite(PIN_DIR, dir ? HIGH : LOW);
  digitalWrite(PIN_STEP, HIGH);
  delayMicroseconds(2);
  digitalWrite(PIN_STEP, LOW);
  delayMicroseconds(2);
}

// -------------------- SPEED HELPER --------------------
inline uint16_t speedToDelay(uint16_t sps) {
  if (sps == 0) return 0;
  return (uint16_t)(1000000UL / sps);
}

// -------------------- KILL SWITCH --------------------
void killISR() {
  killTriggered = true;
}

void emergencyStop() {
  digitalWrite(PIN_ENABLE, HIGH);
  for (uint8_t i = 0; i < NUM_MOTORS; i++) {
    motors[i].remaining = 0;
  }
  Serial.println("F-STOP TRIGGERED — MACHINE HALTED");
}

// -------------------- SCHEDULER --------------------
void stepScheduler() {
  bool anyRemaining = true;

  while (anyRemaining && !killTriggered) {
    anyRemaining = false;

    for (uint8_t i = 0; i < NUM_MOTORS; i++) {
      if (killTriggered) break;

      if (motors[i].remaining != 0) {
        anyRemaining = true;

        bool dir = (motors[i].remaining > 0);
        selectMotor(motors[i].selCode);
        pulseStep(dir);

        motors[i].remaining += (dir ? -1 : +1);

        uint16_t delayUs = speedToDelay(motorSpeed[i]);
        if (delayUs > 0) delayMicroseconds(delayUs);
      }
    }
  }

  if (killTriggered) {
    emergencyStop();
  }
}

// -------------------- COREXY --------------------
void queueCoreXYMove(uint8_t sideIndex, long xSteps, long ySteps) {
  Side &s = sides[sideIndex];
  long aSteps = xSteps + ySteps;
  long bSteps = xSteps - ySteps;
  motors[s.coreA].remaining += aSteps;
  motors[s.coreB].remaining += bSteps;
}

// -------------------- STYLUS / DEPTH --------------------
void queueStylusMove(uint8_t sideIndex, long stylusSteps) {
  motors[sides[sideIndex].stylus].remaining += stylusSteps;
}

void queueDepthMove(uint8_t sideIndex, long depthSteps) {
  motors[sides[sideIndex].depth].remaining += depthSteps;
}

void fineTuneStylus(uint8_t sideIndex, int8_t microSteps) {
  motors[sides[sideIndex].stylus].remaining += microSteps;
}

// -------------------- CLAMP LOGIC --------------------
const long CLAMP_MAX_STEPS     = 3000;
const long CLAMP_BACKOFF_STEPS = 50;

void clampSide(uint8_t sideIndex) {
  uint8_t m = sides[sideIndex].depth;
  long steps = 0;

  while (steps < CLAMP_MAX_STEPS) {
    selectMotor(motors[m].selCode);
    pulseStep(true);

    if (detectResistance(m)) {
      for (long i = 0; i < CLAMP_BACKOFF_STEPS; i++) {
        selectMotor(motors[m].selCode);
        pulseStep(false);
      }
      expectedDepth[sideIndex] = steps;
      break;
    }
    steps++;
  }
}

void clampOpposingSides(uint8_t sideA, uint8_t sideB) {
  clampSide(sideA);
  clampSide(sideB);
}

void clampAllOpposingSides() {
  clampOpposingSides(0, 3);
  clampOpposingSides(1, 4);
  clampOpposingSides(2, 5);
}

// -------------------- BLOCK SIZE PROBING --------------------
long probeDepthUntilResistance(uint8_t sideIndex) {
  uint8_t m = sides[sideIndex].depth;
  long steps = 0;
  const long PROBE_TRAVEL_STEPS = 5000;

  while (steps < PROBE_TRAVEL_STEPS) {
    selectMotor(motors[m].selCode);
    pulseStep(true);

    if (detectResistance(m)) break;
    steps++;
  }
  return steps;
}

void probeBlockSize() {
  long x0 = probeDepthUntilResistance(0);
  long x3 = probeDepthUntilResistance(3);
  blockX = (float)(x0 + x3) / STEPS_PER_MM;

  long y1 = probeDepthUntilResistance(1);
  long y4 = probeDepthUntilResistance(4);
  blockY = (float)(y1 + y4) / STEPS_PER_MM;

  long z2 = probeDepthUntilResistance(2);
  long z5 = probeDepthUntilResistance(5);
  blockZ = (float)(z2 + z5) / STEPS_PER_MM;

  Serial.print("Block size detected: ");
  Serial.print(blockX); Serial.print(" x ");
  Serial.print(blockY); Serial.print(" x ");
  Serial.println(blockZ);
}

// -------------------- THICKNESS / TECHNIQUE --------------------
float measureThickness(uint8_t sideIndex) {
  long steps = probeDepthUntilResistance(sideIndex);
  return steps / STEPS_PER_MM;
}

void useNarrowTechnique(uint8_t sideIndex) {
  motorSpeed[sides[sideIndex].stylus] = 200;
}

void useMediumTechnique(uint8_t sideIndex) {
  motorSpeed[sides[sideIndex].stylus] = 400;
}

void useWideTechnique(uint8_t sideIndex) {
  motorSpeed[sides[sideIndex].stylus] = 800;
}

void applyThicknessTechnique(uint8_t sideIndex) {
  float t = measureThickness(sideIndex);

  if (t < THIN_THRESHOLD_MM) {
    useNarrowTechnique(sideIndex);
  } else if (t < MID_THRESHOLD_MM) {
    useMediumTechnique(sideIndex);
  } else {
    useWideTechnique(sideIndex);
  }
}

void dynamicRecenterCheck(uint8_t sideIndex) {
  long actual = probeDepthUntilResistance(sideIndex);
  long delta  = actual - expectedDepth[sideIndex];
  const long RECENTER_THRESHOLD = 50;

  if (abs(delta) > RECENTER_THRESHOLD) {
    expectedDepth[sideIndex] = actual;
    clampSide(sideIndex);
  }
}

// -------------------- G-CODE HANDLING --------------------
void handleGcodeLine(const String &line) {
  if (line.startsWith("M700")) {
    clampAllOpposingSides();
    return;
  }

  if (line.startsWith("M701")) {
    probeBlockSize();
    return;
  }

  if (line.startsWith("G1")) {
    float x = NAN, y = NAN, z = NAN;
    float s = NAN, d = NAN;
    float feed = 500.0f;

    int idx;

    idx = line.indexOf('X');
    if (idx >= 0) x = line.substring(idx + 1).toFloat();

    idx = line.indexOf('Y');
    if (idx >= 0) y = line.substring(idx + 1).toFloat();

    idx = line.indexOf('Z');
    if (idx >= 0) z = line.substring(idx + 1).toFloat();

    idx = line.indexOf('S');
    if (idx >= 0) s = line.substring(idx + 1).toFloat();

    idx = line.indexOf('D');
    if (idx >= 0) d = line.substring(idx + 1).toFloat();

    idx = line.indexOf('F');
    if (idx >= 0) feed = line.substring(idx + 1).toFloat();

    uint16_t sps = (uint16_t)(feed * STEPS_PER_MM);
    for (uint8_t i = 0; i < NUM_MOTORS; i++)
      motorSpeed[i] = sps;

    long xSteps = isnan(x) ? 0 : (long)(x * STEPS_PER_MM);
    long ySteps = isnan(y) ? 0 : (long)(y * STEPS_PER_MM);
    long zSteps = isnan(z) ? 0 : (long)(z * STEPS_PER_MM);

    long stylusSteps = isnan(s) ? 0 : (long)(s * STEPS_PER_MM);
    long depthSteps  = isnan(d) ? 0 : (long)(d * STEPS_PER_MM);

    for (uint8_t side = 0; side < 6; side++) {
      queueCoreXYMove(side, xSteps, ySteps);
      queueStylusMove(side, stylusSteps);
      queueDepthMove(side, depthSteps);
    }
  }
}

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(115200);

  pinMode(PIN_STEP,   OUTPUT);
  pinMode(PIN_DIR,    OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);

  pinMode(PIN_SEL0, OUTPUT);
  pinMode(PIN_SEL1, OUTPUT);
  pinMode(PIN_SEL2, OUTPUT);
  pinMode(PIN_SEL3, OUTPUT);

  pinMode(PIN_KILL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_KILL), killISR, FALLING);

  digitalWrite(PIN_ENABLE, LOW);

  for (uint8_t i = 0; i < NUM_MOTORS; i++) {
    motors[i].id        = i;
    motors[i].selCode   = i & 0x0F;
    motors[i].role      = MOTOR_COREXY_A;
    motors[i].remaining = 0;
    motorSpeed[i]       = 500;
  }

  for (uint8_t side = 0; side < 6; side++) {
    sides[side].coreA  = side * 4 + 0;
    sides[side].coreB  = side * 4 + 1;
    sides[side].stylus = side * 4 + 2;
    sides[side].depth  = side * 4 + 3;

    motors[sides[side].coreA].role  = MOTOR_COREXY_A;
    motors[sides[side].coreB].role  = MOTOR_COREXY_B;
    motors[sides[side].stylus].role = MOTOR_STYLUS;
    motors[sides[side].depth].role  = MOTOR_DEPTH;

    expectedDepth[side] = 0;
  }

  blockX = 120.0f;
  blockY = 120.0f;
  blockZ = 120.0f;
}

// -------------------- LOOP --------------------
void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      handleGcodeLine(line);
    }
  }

  stepScheduler();

  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 1000) {
    for (uint8_t side = 0; side < 6; side++) {
      applyThicknessTechnique(side);
      dynamicRecenterCheck(side);
    }
    lastCheck = millis();
  }
}
