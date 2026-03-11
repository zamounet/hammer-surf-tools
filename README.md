# Surf Tools for Hammer++ (Build 8870)

A mod of Hammer++ with surf-related features.

## Features

### Clip Angle Measurer
- When using the clipping tool, it will show the surf angle if it's surfable.
- **Toggle**: press `o`.

### Ramp Angle Measurer
- When selecting a solid (not an entity or group), it will show the surf angle for each surfable face.

### Angle Fix
- Requires compiling with `vbspplusplus.exe` from the Tools++ compilers (for `func_detail_illusionary`)
- **Usage**: Select worldbrush rotated ramps and press `Ctrl + Alt + Shift + A`.

### Trigger Generator
- Creates triggers by extruding from selected faces.  
- For now they are hardcoded to be 2 unit tall `trigger_teleport`.
- You can press `Alt + Enter` after to set the teleport destination in bulk.
- **Usage**: Select some faces with the texture tool, then press `Ctrl + Alt + Shift + T`.

### Curved Ramp Generator
- Generates a curved ramp by a start segment and inputting direction, degrees, and number of segments.
- Convex ramps are not supported yet.  
- **Usage**: Select a start segment that’s not rotated, then press `Ctrl + Alt + Shift + S`.

## About Angle Steepness Rating
When you see ratings like `5/10` with the angle measure tools:

- `5/10`  → "Sweet spot" (~50 degrees)
- `0/10`  → Just barely surfable
- `10/10` → Ranges from "probably too steep to be fun" all the way to "too steep to stay on the ramp"
- This may be tweaked in the future.

## Notes
- There’s also a context menu in **Tools → Surf Tools** and in the right-click context menu.

## Installation
1. Extract `version.dll` to the directory where you have `hammerplusplus.exe`.

### Linux
- Use this environment variable:  
```bash
WINEDLLOVERRIDES="version=n,b"
```
