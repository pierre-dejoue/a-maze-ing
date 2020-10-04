a-maze-ing
============
A mouse is looking for a piece of cheese

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](./LICENSE)

![Snapshot](misc/demo/AMazeIng.jpg)

## Usage

Run with an example file:

`a-maze-ing misc/example-input/mazes.txt`

## Requirements

Graphics library: [SFML](https://github.com/SFML/SFML) >= 2.5. Download the binaries specific to your build environment: [SFML Download](https://www.sfml-dev.org/download.php)

## Build with CMake

For example on Windows:

```
$ mkdir build
$ cd build
$ cmake -G "Visual Studio 15 2017 Win64" -DSFML_DIR="C:/SFML-2.5.1/lib/cmake/SFML" ..
$ cmake --build . --config Debug
```
