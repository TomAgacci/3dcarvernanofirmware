===============================================================
WIRING DIAGRAM — ARCHITECTURE A
Single Driver + Selector + 6 CNC‑V3 Boards × 4 Motors Each
===============================================================

                    ┌──────────────────────────────┐
                    │          ARDUINO NANO        │
                    └──────────────────────────────┘
 STEP  (D2) ───────────────────────────────► BOARD0 X.STEP
 DIR   (D3) ───────────────────────────────► BOARD0 X.DIR
 EN    (D4) ───────────────────────────────► BOARD0 EN

 SEL0  (D5) ───────────────────────────────► SELECTOR SEL0
 SEL1  (D6) ───────────────────────────────► SELECTOR SEL1
 SEL2  (D7) ───────────────────────────────► SELECTOR SEL2
 SEL3  (D8) ───────────────────────────────► SELECTOR SEL3

 KILL  (D9) ─────── SWITCH ───────────────► GND   (INPUT_PULLUP)

 EMF   (A0) ───────────────────────────────► Broadcom AFE OUT

 5V ───────────────────────────────────────► BOARD0 / SELECTOR / AFE
 GND ──────────────────────────────────────► BOARD0 / SELECTOR / AFE

===============================================================
CNC‑V3 SHIELD — BOARD0 (THE ONLY BOARD WITH A DRIVER)
===============================================================

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 0        │
                    │     (MAIN DRIVER BOARD)      │
                    └──────────────────────────────┘

 12–24V PSU + ─────────────────────────────► VIN / +12V
 12–24V PSU GND ───────────────────────────► GND

 DRIVER (X‑axis slot ONLY):
    A+ ─────────────────────────────────────► SELECTOR COMMON_A+
    A- ─────────────────────────────────────► SELECTOR COMMON_A-
    B+ ─────────────────────────────────────► SELECTOR COMMON_B+
    B- ─────────────────────────────────────► SELECTOR COMMON_B-

 NOTE:
 • Y/Z/A driver slots EMPTY.
 • BOARD0 is the ONLY board with a stepper driver installed.

===============================================================
SELECTOR BOARD — 24 CHANNELS
===============================================================

                    ┌──────────────────────────────┐
                    │         SELECTOR BOARD       │
                    └──────────────────────────────┘

 SEL0 ◄───────────────────────────────────── NANO D5
 SEL1 ◄───────────────────────────────────── NANO D6
 SEL2 ◄───────────────────────────────────── NANO D7
 SEL3 ◄───────────────────────────────────── NANO D8

 COMMON_A+ ◄──────────────────────────────── BOARD0 DRIVER A+
 COMMON_A- ◄──────────────────────────────── BOARD0 DRIVER A-
 COMMON_B+ ◄──────────────────────────────── BOARD0 DRIVER B+
 COMMON_B- ◄──────────────────────────────── BOARD0 DRIVER B-

 24 OUTPUT CHANNELS:
   CH0  → BOARD0 MOTOR0 (A+/A-/B+/B-)
   CH1  → BOARD0 MOTOR1
   CH2  → BOARD0 MOTOR2
   CH3  → BOARD0 MOTOR3

   CH4  → BOARD1 MOTOR4
   CH5  → BOARD1 MOTOR5
   CH6  → BOARD1 MOTOR6
   CH7  → BOARD1 MOTOR7

   CH8  → BOARD2 MOTOR8
   CH9  → BOARD2 MOTOR9
   CH10 → BOARD2 MOTOR10
   CH11 → BOARD2 MOTOR11

   CH12 → BOARD3 MOTOR12
   CH13 → BOARD3 MOTOR13
   CH14 → BOARD3 MOTOR14
   CH15 → BOARD3 MOTOR15

   CH16 → BOARD4 MOTOR16
   CH17 → BOARD4 MOTOR17
   CH18 → BOARD4 MOTOR18
   CH19 → BOARD4 MOTOR19

   CH20 → BOARD5 MOTOR20
   CH21 → BOARD5 MOTOR21
   CH22 → BOARD5 MOTOR22
   CH23 → BOARD5 MOTOR23

===============================================================
CNC‑V3 BOARDS 1–5 (MOTOR CARRIER BOARDS)
===============================================================

Each board carries 4 motors but has NO driver installed.

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 1        │
                    │      (MOTORS 4–7 ONLY)       │
                    └──────────────────────────────┘
   MOTOR4 A+/A-/B+/B- ◄────────────── SELECTOR CH4
   MOTOR5 A+/A-/B+/B- ◄────────────── SELECTOR CH5
   MOTOR6 A+/A-/B+/B- ◄────────────── SELECTOR CH6
   MOTOR7 A+/A-/B+/B- ◄────────────── SELECTOR CH7

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 2        │
                    │      (MOTORS 8–11)           │
                    └──────────────────────────────┘
   MOTOR8  ◄──────── SELECTOR CH8
   MOTOR9  ◄──────── SELECTOR CH9
   MOTOR10 ◄──────── SELECTOR CH10
   MOTOR11 ◄──────── SELECTOR CH11

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 3        │
                    │      (MOTORS 12–15)          │
                    └──────────────────────────────┘
   MOTOR12 ◄──────── SELECTOR CH12
   MOTOR13 ◄──────── SELECTOR CH13
   MOTOR14 ◄──────── SELECTOR CH14
   MOTOR15 ◄──────── SELECTOR CH15

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 4        │
                    │      (MOTORS 16–19)          │
                    └──────────────────────────────┘
   MOTOR16 ◄──────── SELECTOR CH16
   MOTOR17 ◄──────── SELECTOR CH17
   MOTOR18 ◄──────── SELECTOR CH18
   MOTOR19 ◄──────── SELECTOR CH19

                    ┌──────────────────────────────┐
                    │        CNC‑V3 BOARD 5        │
                    │      (MOTORS 20–23)          │
                    └──────────────────────────────┘
   MOTOR20 ◄──────── SELECTOR CH20
   MOTOR21 ◄──────── SELECTOR CH21
   MOTOR22 ◄──────── SELECTOR CH22
   MOTOR23 ◄──────── SELECTOR CH23

===============================================================
POWER / GROUND
===============================================================
12–24V PSU + ─────────► BOARD0 VIN / +12V  
12–24V PSU GND ───────► BOARD0 GND  
BOARD1–BOARD5 GND ────► COMMON GND  
SELECTOR GND ─────────► COMMON GND  
AFE GND ──────────────► COMMON GND  
NANO GND ─────────────► COMMON GND  

ALL GROUNDS MUST BE COMMON.

===============================================================
END
===============================================================
