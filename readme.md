# Image to ASCII

## Overview

The **ASCII Project** is a C++ program that converts images into ASCII art, allowing you to visualize images using only characters. It’s a fun and creative way to explore text-based graphics and understand pixel-to-character mapping.

---

## Features

* Converts images to ASCII art
* Adjustable width (number of characters per line)
* Supports three quality levels: **low**, **medium**, **high**
* Automatically maintains aspect ratio for better results
* Saves output as `.txt` files in an `ascii_output` folder

---

## Installation

1. Clone the repository:

```bash
git clone https://github.com/yourusername/ascii-project.git
cd ascii-project
```

2. Make sure you have **C++ compiler** and **OpenCV** installed:

```bash
sudo apt update
sudo apt install g++ libopencv-dev cmake
```

---

## Usage

### Compile the program

```bash
g++ main.cpp -o ascii `pkg-config --cflags --libs opencv4` or make
```

### Run the program

```bash
./ascii <folder_path> [width] [quality]
```

* `<folder_path>` → Path to folder containing images (required)
* `[width]` → Optional width in characters (default: 150)
* `[quality]` → Optional quality: `low` (default), `medium`, `high`

#### Examples

* Default width & low quality:

```bash
./ascii ./images
```

* Custom width 200 & medium quality:

```bash
./ascii ./images 200 medium
```

* Custom width 180 & high quality:

```bash
./ascii ./images 180 high
```

---

## How It Works

1. Reads each image in the provided folder using OpenCV
2. Converts the image to grayscale and enhances contrast
3. Resizes the image to the specified width while maintaining aspect ratio
4. Maps each pixel to a character based on brightness and quality level
5. Saves ASCII art to a `.txt` file inside `ascii_output`

---

## ASCII Character Sets

| Quality | Character Set                                |                           
| ------- | -------------------------------------------- | 
| Low     | `@%#*+=-:.`                                  |                           
| Medium  | `s@&#%OX0CLi!~+-?1`                          |                           
| High    | \`S\@B%8\&WM#oahkbdpqmwZO0QLCJUYXzcvunxrjft/ |

---

## Dependencies

* **C++17** or higher
* **OpenCV 4.x**

---

## Future Improvements

* Support for color ASCII output
* Real-time video-to-ASCII conversion
* Configurable custom character sets

---

## License

This project is licensed under the MIT License.

