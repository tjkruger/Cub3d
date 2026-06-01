# cub3d — Team Task Plan

Two-person split designed for maximum parallel work.
The handoff point is `t_main` — Person A fills it, Person B reads from it.

---

## Person A — Parser, Validation & Memory

# Cub3D - Remaining Tasks

## To Do

### 4. Error Handling
- Every `exit(1)` needs to call `free_all` before it
- No leaks on any exit path

### 5. Valgrind Check
- Run valgrind and confirm no leaks on any exit path
---

## Person B — Rendering, Raycasting & Game Loop

### 1. Stub Map Setup (use this until parser is done)
```c
char *map[] = {
    "111111111111",
    "100000000001",
    "101000010001",
    "100000000001",
    "100010000001",
    "111111111111",
    NULL
};
```
Hardcode a player position and direction so you can work fully independently.

### 2. Player Initialisation (`init.c`)
- Convert `t_map_data->player_pos` (int tile) to `t_player->pos` (float, center of tile: `tile + 0.5`)
- Set `t_player->dir` based on `player_orientation`:
  - `N` → `dir = {0, -1}`, `plane = {0.66, 0}`
  - `S` → `dir = {0, 1}`,  `plane = {-0.66, 0}`
  - `E` → `dir = {1, 0}`,  `plane = {0, 0.66}`
  - `W` → `dir = {-1, 0}`, `plane = {0, -0.66}`
- The camera plane magnitude determines your horizontal FOV (~66° with 0.66)
- Set `t_player->speed` from the `PLAYER_SPEED` define

### 3. Texture Loading
- Load all 4 textures with `mlx_load_png()` into `t_main->textures[0..3]`
- Use a consistent index: 0=North, 1=South, 2=East, 3=West
- Check return value — `mlx_load_png` returns NULL on failure
- Textures must be loaded before `mlx_loop` starts

### 4. Image Setup
- Create the render target with `mlx_new_image(mlx, WIDTH, HEIGHT)`
- Draw into `image->pixels` directly — this is your framebuffer
- After drawing a frame, display it with `mlx_image_to_window()`

### 5. DDA Raycasting Loop
One ray per vertical screen column (loop from `x = 0` to `x = WIDTH`):

- Calculate `cam_x = 2 * x / WIDTH - 1` (range -1.0 to 1.0)
- `ray.dir = player.dir + player.plane * cam_x`
- Calculate `delta_dist`: `{fabs(1/ray.dir.x), fabs(1/ray.dir.y)}`
- Set `step` (+1 or -1) and initial `side_dist` from player fractional position
- **DDA loop**: step through the grid, advancing on whichever axis has the shorter side_dist, until you hit a `1`
- Record which side was hit (`side`: 0=EW wall, 1=NS wall) — this determines which texture to use
- Calculate `perp_wall_dist` to avoid the fisheye effect

### 6. Wall Projection
- `line_height = HEIGHT / perp_wall_dist`
- `line_start = -line_height / 2 + HEIGHT / 2`
- `line_end   =  line_height / 2 + HEIGHT / 2`
- Clamp both to `[0, HEIGHT-1]`

### 7. Texture Mapping
- Select texture based on `side` and `ray.dir` (which of the 4 walls you hit)
- Calculate `wall_hit_x` — the exact fractional position where the ray hit the wall
- Map to `texture_x`: `wall_hit_x * texture->width`
- For each pixel row in `[line_start, line_end]`, sample the correct texel and write to the framebuffer

### 8. Floor and Ceiling
- Everything above `line_start` → fill with `map_data->ceiling_color`
- Everything below `line_end`  → fill with `map_data->floor_color`
- This can be done in the same column loop or a separate pass

### 9. Input & Movement (`game.c`)
Use `mlx_is_key_down()` inside the loop hook for smooth movement:

| Key | Action |
|-----|--------|
| `W` | Move forward along `dir` |
| `S` | Move backward along `dir` |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | `mlx_close_window()` |

- Before moving, check the target tile in the map — don't allow moving into a `1`
- Rotation: apply a 2D rotation matrix to both `dir` and `plane` using `ROTATION_SPEED`

### 10. `run_game()` and `end_game()`
- `run_game()`: register hooks with `mlx_loop_hook` and `mlx_key_hook`, then call `mlx_loop()`
- `end_game()`: `mlx_delete_texture()` for all 4 textures, `mlx_delete_image()`, `mlx_terminate()`

---

## Shared / Sync Points

| What | Who | When |
|------|-----|-------|
| `cub3d.h` prototypes | Both | Communicate before editing |
| `t_main` struct fields | A defines, B reads | Before B starts player init |
| Texture index convention (0=N,1=S…) | Agree early | Before either touches textures |
| Map coordinate system (row/col vs x/y) | Agree early | Before either touches the map |

---

## Suggested Order

```
Week 1
  A: arg check → file reading → color + texture parsing
  B: stub map → player init → DDA loop (no textures yet, just colored walls)

Week 2
  A: map extraction → map validation → flood fill
  B: texture mapping → floor/ceiling → movement + collision

Week 3
  A: free_all + leak check → plug into B's main
  B: polish input, clamp edge cases
  Both: integration, norm, final leak check
```
