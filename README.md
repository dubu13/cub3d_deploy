# Cub3D Web Version

A web version of the Cub3D raycasting engine using Emscripten and MLX42.

## Prerequisites

This project requires **Emscripten** to compile for web.

**Install Emscripten:** https://emscripten.org/docs/getting_started/downloads.html

Make sure to source the Emscripten environment:
```bash
source path/to/emsdk/emsdk_env.sh
```

## Build

```bash
make
```

## Run

Serve the generated files with any web server:
```bash
python3 -m http.server 8000
```

Then open `http://localhost:8000/cub3D_web.html` in your browser.

## Controls

- **WASD** - Movement
- **Mouse** - Look around
- **ESC** - Exit