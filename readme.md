# Snow Simulation with Dynamic Backgrounds and Touch Input

![Snow Simulation in Action](example_screenshot.png)

## Overview

This program is a visually pleasing snow simulation that:
- Dynamically displays falling snowflakes with wind effects.
- Cycles through multiple background images stored in a directory.
- Allows interaction via a touchscreen to switch backgrounds.

It’s perfect for creating a holiday-themed display or experimenting with SDL2 graphics programming.

---

## Features

- ![Snowflake](https://img.icons8.com/emoji/48/000000/snowflake.png) **Dynamic Snow Animation**: Snowflakes of varying sizes fall with adjustable wind effects.
- ![Picture](https://img.icons8.com/emoji/48/000000/framed-picture.png) **Interactive Backgrounds**: Switch between backgrounds using a touchscreen device.
- ![Touchscreen](https://img.icons8.com/emoji/48/000000/finger-pointing.png) **Touchscreen Integration**: Works seamlessly with Linux input devices (`/dev/input`).

---

## Prerequisites

Ensure the following libraries are installed on your system:

- SDL2
- SDL2_image
- libevdev

Install them on Debian-based systems using:

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libevdev-dev
```
---
### Touch device
To find out your touch device, you can install evtest and use it to find the device
```bash
sudo apt install evtest
```
Run the software
```bash
sudo evtest
```
It should list some devices and one of the them is your touch device.  
Here's an example using [Pimoroni's HyperPixel 4.0 Square](https://shop.pimoroni.com/products/hyperpixel-4-square?variant=30138251444307)

```bash
evtest 

No device specified, trying to scan all of /dev/input/event*
Not running as root, no devices may be available.
Available devices:
/dev/input/event0:	vc4-hdmi
/dev/input/event1:	11-0048 EP0110M09
/dev/input/event2:	vc4-hdmi HDMI Jack
Select the device event number [0-2]: 
```
Select the one and see if outputs text. 

If you see text, that's the one. 

---
#### Add the user to the group input
---
You need to add your user (or the user running this program) to the *input* group. 
```bash
```
sudo usermod -aG input $USER

---
### Images
---
JPEG images must be placed in a images directory. 
```bash
mkdir images
```
Copy to the directory all the images you want to use. 

They must be JPEG and have the resolution that you want to use (usually the same as your monitor)

---
## How to Compile and Run

### Clone the Repository
```bash
git clone https://github.com/yourusername/snow_simulation.git
cd snow_simulation
```

### Compile
Use the included Makefile to compile the program:
```bash
make
```

### Run the Program
The program requires three command-line arguments:
1. **Width** (`-w`): Screen width (e.g., `1024`).
2. **Height** (`-h`): Screen height (e.g., `768`).
3. **Touchscreen Device** (`-e`): Input device path (e.g., `/dev/input/event0`).

Run the program as follows:
```bash
./snow_simulation -w 1024 -h 768 -e /dev/input/event0
```

### Display Help
To see the help message:
```bash
./snow_simulation --help
```

---

## Background Images

Background images must be placed in the `images` directory in the same location as the program. Only `.png` files are supported.

Example directory structure:
```
snow_simulation/
├── images/
│   ├── background1.png
│   ├── background2.png
│   └── background3.png
└── snow_simulation
```

---

## What Does It Do?

- Displays falling snow with a dynamic wind effect.
- Lets you change backgrounds by touching the screen.
- Supports multiple resolutions and touchscreen devices.

---

## Screenshot

Replace the placeholder below with a screenshot of the program in action:

![Snow Simulation in Action](example_screenshot.png)

---

## To-Do / Future Enhancements

- **Dynamic Background Scaling**: Automatically scale backgrounds to match screen resolution.
- **Additional Input Modes**: Add mouse or keyboard interaction as a fallback.
- **Audio Integration**: Play a festive tune during the simulation.
- **More Effects**: Introduce twinkling lights or a dynamic weather system.

---

## License

This program is distributed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

---

## Author

**Bruno Santos**  
<feiticeir0@whatgeek.com.pt>

