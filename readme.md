# Interactive Winter Wonderland Simulation with Dynamic Backgrounds and Touch Input :christmas_tree: :santa:
![License](https://img.shields.io/badge/license-GPLv3-blue.svg) ![SDL2](https://img.shields.io/badge/dependency-SDL2-blue.svg)

![Snow Simulation in Action](https://hackster.imgix.net/uploads/attachments/1802123/christmaswonderland_l7ZQh8uRFL.gif?auto=compress&gifq=35&w=740&h=555&fit=max&fm=mp4)

## :guitar: Overview

This program is a visually pleasing snow simulation that:
- Dynamically displays falling snowflakes with wind effects.
- Cycles through multiple background images stored in a directory.
- Allows interaction via a touchscreen to switch backgrounds.

It’s perfect for creating a holiday-themed display or experimenting with SDL2 graphics programming.

---

## :mega: Features

- :snowflake: **Dynamic Snow Animation**: Snowflakes of varying sizes fall with adjustable wind effects.
- :rice_scene: **Interactive Backgrounds**: Switch between backgrounds using a touchscreen device.
- :phone: **Touchscreen Integration**: Works seamlessly with Linux input devices (`/dev/input`).

---

## :pushpin: Prerequisites

Ensure the following libraries are installed on your system:

- SDL2
- SDL2_image
- libevdev

Install them on Debian-based systems using:

```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libevdev-dev
```
---
### :wave: Touch device
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
Select one, touch it and see if outputs text. 

If you see text, that's the one you should use.

---
#### :bowtie: Add the user to the group input
---
You need to add your user (or the user running this program) to the *input* group. 
```bash
sudo usermod -aG input $USER
```

---
### :rice_scene: Images
---
JPEG images must be placed in a images directory. 
```bash
mkdir images
```
Copy to the directory all the images you want to use. 

They must be JPEG and have the resolution that you want to use (usually the same as your monitor)

Here are the ones included in the project
#### Background 1
![Background 1](images/christmas1.jpg)
#### Background 2
![Background 2](images/christmas2.jpg)
#### Background 3
![Background 3](images/christmas3.jpg)
#### Background 4
![Background 4](images/christmas4.jpg)
---
## :rocket: How to Compile and Run

### Clone the Repository
```bash
git clone https://github.com/feiticeir0/ChristmasSnowGlobe
cd ChristmasSnowGlobe
```

### Compile
Use the included Makefile to compile the program:
```bash
make
```

### :bicyclist: Run the Program
The program requires three command-line arguments:
1. **Width** (`-w`): Screen width (e.g., `1024`).
2. **Height** (`-h`): Screen height (e.g., `768`).
3. **Touchscreen Device** (`-e`): Input device path (e.g., `/dev/input/event0`).

Run the program as follows:
```bash
./christmasSnowBall -w 1024 -h 768 -e /dev/input/event0
```
### :hand: Touch Device
Using Pimoroni's Hyperpixel Square 4.0, sometimes the touch device changes between reboots. So, it may not always be event0.

I've created a script to find the correct touch device for the Pimoroni's Hyperpixel Touch 4.0. This way, when invoking the Christmas Snow Globe in a script (automatically, for example), I always have the right device.

To use the script to find the device, the correct invocation is:

```bash
cd ChristmasSnowGlobe;./christmasSnowGlobe -h 720 -w 720 -e /dev/input/$(./findPimoronisTouchDevice.sh) &
```
The script findPimoronisTouchDevice.sh returns the correct event device for the touch screen.

### :question: Display Help
To see the help message:
```bash
./christmasSnowBall --help
```

---

## :rice_scene: Background Images

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

## Demo

![Snow Simulation in Action]([video/christmaswonderland.mp4](https://github.com/feiticeir0/ChristmasSnowGlobe/raw/refs/heads/main/video/christmaswonderland.mp4))

---

## To-Do / Future Enhancements

- **Dynamic Background Scaling**: Automatically scale backgrounds to match screen resolution.
- **Audio Integration**: Play a festive tune during the simulation.
- **More Effects**: Introduce twinkling lights or a dynamic weather system.

---

## License

This program is distributed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

---

## Author

**Bruno Santos**  
<feiticeir0@whatgeek.com.pt>

