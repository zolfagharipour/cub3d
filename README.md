# Cub3D

## Overview

cub3D is a project that implements a first-person perspective 3D maze game using raycasting techniques, inspired by Wolfenstein 3D. Developed in C, it uses the MiniLibX library to handle graphics and interactions.

## Warning for 42 Students

This repository is intended as a reference and educational tool. **42 students are strongly advised not to copy this code without fully understanding its functionality.** Plagiarism in any form is against 42's principles and could lead to serious academic consequences. Use this repository responsibly to learn and better understand how to implement similar functionalities on your own.

## Features

- **Realistic 3D rendering using raycasting.**
- **Dynamic user controls**: Move with W, A, S, D, and rotate the view using the arrow keys.
- **Textured walls**: Each wall face (North, South, East, West) displays unique textures.
- **Configurable environment via .cub files to set up map layouts, wall textures, floor/ceiling colors, and player orientation.**

## Mandatory Requirements

**Controls:**
    W, A, S, D: Movement in the maze.
    Left/Right Arrow: Rotate the view.
    ESC: Exit the game.
    Red Cross on Window: Close the window and exit.

**Game Elements:**
    Walls (1): Block player movement.
    Open spaces (0): Navigable areas.
    Player starting position (N, S, E, W): Indicates player spawn and orientation.

**Configuration File (*.cub):**
    Defines textures, colors, and map layout.
    Must follow specific formatting rules (detailed below).

**Error Handling:**
    Misconfigured files or invalid map layouts will trigger an error message and exit.

**Performance:**
    Smooth gameplay with no segmentation faults, memory leaks, or crashes.

## Map Configuration (.cub File)

**Identifiers:**
    NO: Path to North wall texture.
    SO: Path to South wall texture.
    WE: Path to West wall texture.
    EA: Path to East wall texture.
    F: RGB values for floor color.
    C: RGB values for ceiling color.

**Map Rules:**
    Surrounded by walls (1).
    Spaces ( ) are valid but must not leave the map open.
    Only 0, 1, N, S, E, W are valid map characters.

## Bonus Features

**Doors:**
    Controlled by the SPACE key.
    Only one door (4 in the map) can be open at a time.

**Lighting Effects:**
    Walls light up differently based on their orientation.

**Animated Sprites:**
    A ninja character with the following behaviors:
        Starts invisible if far away.
        Becomes visible when the player is near.
        Has 4 smoke bombs; runs when attacked (E key).
        Dies after using all smoke bombs.

**Mouse Controls:**
    Rotate the view using the mouse.

**Minimap:**
    Displays the map layout and the player’s position in real-time.

## Compilation

```bash
git clone https://github.com/zolfagharipour/cub3D.git
cd cub3D
make
```

To compile the bonus version:

```bash
make bonus
```
## Usage

Standard operation:

```bash
./cub3D <path_to_map_file>
```
For the bonus version:

```bash
./cub3D_bonus <path_to_map_file>
```
