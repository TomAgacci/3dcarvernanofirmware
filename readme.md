===============================================================<br>
3D CARVER Nano<br>
===============================================================<br><br>

Print the stylus. Imprint half in sand. Pour water. Freeze. Imprint other half in sand. Pour water. Freeze.<br>

Combine. Melt water. Pour aluminum.

The end result uses:<br>
1 arduino nano<br>
6 CNC V3 shields<br>
24 motors<br>
1 basic broadcom stepper driver<br>
6 80mm Screwshape Styluses<br>
www.thingiverse.com/thing:6198549

The stepper switches instantly between motors synchronized. It sends signals to the motors from
1 stepper driver by communicating quickly between all motors and 1 driver back and forth.

It's all corexy on all 6 sides.

You install the firmware and add the machine to the slicer as if it were a 3d printer.

The Styluses clamp, preventing movement of the block.

It's all corexy

You need 2020 bars to craft the machine as well as small parts you can find online.
I do not have a design for a machine but this is a machinist project, and the
firnware is simple and all put together - and not that difficult to line up.

You need 120mm^3 blocks made of carvable plastic or hempcrete.

Screw Shape Stylus
www.thingiverse.com/thing:6198549

# Clean‑Room Arduino Core (CC BY‑NC‑ND)

This project includes a fully legal, clean‑room reimplementation of the
Arduino API surface. It contains **no copyrighted Arduino core code** and is
licensed under **Creative Commons Attribution–NonCommercial–NoDerivatives 4.0**.

## Purpose

This core exists to:
- Allow firmware to compile without depending on copyrighted Arduino sources.
- Provide a stable API surface for custom machines, simulators, and tooling.
- Enable CC‑licensed projects to remain legally compliant.

## What’s Included

All files are merged into a single header: `ArduinoCore.h`.

It contains clean‑room stubs for:

- GPIO
- Timing
- Serial
- Stream
- Print
- Wire (I²C)
- SPI
- Ethernet
- WiFi
- SD
- Servo
- SoftwareSerial
- EEPROM
- USBAPI
- Keyboard
- Mouse
- Tone
- IPAddress
- Client / Server
- pins_arduino
- binary helpers

## Legal Notes

- No copyrighted Arduino code is included.
- All implementations are original and minimal.
- Only the *shape* of the API is reproduced.
- No functional hardware access is provided.

## Usage

Include the core:

```cpp
#include "ArduinoCore.h"

===============================================================<br>
LICENSE — Creative Commons Attribution–NonCommercial–NoDerivatives 4.0<br>
===============================================================<br>

This project is licensed under the Creative Commons 
Attribution–NonCommercial–NoDerivatives 4.0 International License.

You are free to:
  • Share — copy and redistribute the material in any medium or format

Under the following terms:
  • Attribution — You must give appropriate credit, provide a link to the license,
    and indicate if changes were made.
  • NonCommercial — You may not use the material for commercial purposes.
  • NoDerivatives — If you remix, transform, or build upon the material, 
    you may not distribute the modified material.

No additional restrictions:
  • You may not apply legal terms or technological measures that legally restrict 
    others from doing anything the license permits.

Full legal text:
  https://creativecommons.org/licenses/by-nc-nd/4.0/legalcode

Human‑readable summary:
  https://creativecommons.org/licenses/by-nc-nd/4.0/

===============================================================
END OF LICENSE
===============================================================
