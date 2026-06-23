*This project has been created as part of the 42 curriculum by awolschi, tjkruger.*

# Cub3D

## Description
Cub3D is a small first-person 3D renderer inspired by early raycasting games such as Wolfenstein 3D.

The goal of the project is to build a minimal 3D engine in C, using a 2D map described in a `.cub` file and projecting it into a pseudo-3D view with:
- DDA-based raycasting
- Wall texturing
- Floor and ceiling coloring
- Real-time player movement and rotation

This implementation uses:
- MLX42 for window management, rendering, and texture loading
- A custom `libft`
- A custom `get_next_line`

## Features
- `.cub` map parsing and validation
- Texture loading for north/south/east/west walls (PNG)
- Collision-aware movement (`W`, `A`, `S`, `D`)
- Camera rotation with arrow keys
- Exit with `ESC`

## Instructions
### Prerequisites
- Linux
- `cc` (or `gcc`/`clang` compatible with the Makefile)
- `make`
- `cmake`
- `glfw3` development package

On Debian/Ubuntu, you can install the main dependencies with:

```bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev
```

### Compilation
From the repository root:

```bash
make
```

This will:
- Build `libft`
- Configure and build MLX42 in `MLX42/build`
- Compile the project executable `Cub3d`

### Execution
Run the program with exactly one `.cub` map file:

```bash
./Cub3d maps/testmap.cub
```

Other example maps:

```bash
./Cub3d maps/subject_map.cub
./Cub3d maps/just_player_and_walls.cub
```

### Controls
- `W` / `S`: move forward/backward
- `A` / `D`: strafe left/right
- `Left Arrow` / `Right Arrow`: rotate camera
- `ESC`: close the window

### Cleaning
```bash
make clean
make fclean
make re
```

## Project Structure
- `src/`: game loop, raycasting, movement, rendering, texture handling
- `src/val_ini/`: map parsing and validation pipeline
- `include/`: shared headers and project structs
- `libft/`: custom utility library
- `GNL/`: line-by-line file reader implementation
- `maps/`: valid and invalid map examples
- `MLX42/`: graphics library source

## Resources
### Classic references
- 42 Subject for Cub3D
- Lode's Computer Graphics Tutorial (Raycasting):
  - https://lodev.org/cgtutor/raycasting.html
- Permadi Ray Casting Tutorial:
  - https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
- MLX42 documentation:
  - https://github.com/codam-coding-college/MLX42
- GLFW documentation:
  - https://www.glfw.org/documentation.html

### AI usage disclosure
AI tools were used as an assistant for:
- drafting and improving project documentation (including this README),
- clarifying specific C/MLX42 API behavior during development,
- suggesting debugging directions for parsing/rendering issues.

All architecture choices, code integration, and final validation decisions were made by the project authors.
