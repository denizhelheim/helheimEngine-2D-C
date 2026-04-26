# Quick Start Guide - Helheim Engine 2D Development

## Building the Project

### Option 1: Using Make
```bash
cd HelheimEngine-2D
make clean
make
make run
```

### Option 2: Direct GCC Compilation
```bash
gcc -Wall -Wextra -O2 -o HelheimEngine2D.exe \
  main.c globals.c entity.c particle.c inventory.c \
  collision.c tile.c rendering.c input.c gameplay.c \
  menu.c utils.c -lm
```

## File Structure Quick Reference

| File | What's in it | Key Functions |
|------|-----------|---|
| **main.c** | App entry point | `main()` |
| **types.h** | All type definitions | Structures, enums |
| **globals.h/c** | Game state variables | Game arrays, counters |
| **entity.c** | Game objects | `CreateEntity()`, `UpdateEnemyAI()` |
| **rendering.c** ✓ FIXED | Display system | `RenderGame()`, `DrawGameUI()` |
| **input.c** | Player controls | `HandleInput()`, `MovePlayerTo()` |
| **gameplay.c** | Game loop | `PlayCurrentLevel()`, `LoadDefaultLevel()` |
| **menu.c** | All menus | `ShowMainMenu()`, `AdvancedLevelEditor()` |
| **tile.c** | Level/map | `InitializeDefaultMap()`, `SetTile()` |
| **particle.c** | Effects | `EmitParticle()`, `UpdateParticles()` |
| **collision.c** | Hit detection | `IsWall()`, `IsHazard()` |
| **inventory.c** | Items system | `AddToInventory()`, `RemoveFromInventory()` |
| **utils.c** | Helpers | `GetCurrentTimeMS()` |

## Common Tasks

### Add a New Menu Option
1. Edit `menu.c` - add case to `ShowMainMenu()`
2. Create new function `YourNewMenu()` in `menu.c`
3. Add forward declaration to `menu.h`

### Create a New Entity Type
1. Add enum to `types.h` (EntityType)
2. Implement logic in `entity.c`
3. Update `CreateEntity()` if needed

### Fix Display Issues
- All text rendering → `rendering.c` (especially `DrawGameUI()`)
- Coordinate calculations → `rendering.c` and `input.c`

### Add New Tile Type
1. Add to `TileType` enum in `types.h`
2. Update `SetTile()` in `tile.c`
3. Add collision/interaction logic to appropriate files

## Known Fixed Issues

✓ **UI Text Alignment** - Fixed in rendering.c:
- Changed printf format from `%-Xd` to `%Xd` + padding
- Ensures proper alignment of Score, Health, Stars, Time

## Development Tips

1. **Compilation:** Always compile with `-Wall -Wextra` to catch issues
2. **Linking:** Don't forget `-lm` for math functions
3. **Window Console:** App requires Windows console, uses Windows API
4. **Frame Rate:** Set by `FRAME_TIME_MS` constant in globals.h
5. **Debugging:** Enable with `gameConfig.showDebugInfo = 1`

## Code Style Notes

- **Naming:** snake_case for functions, UPPER_CASE for macros
- **Structures:** Component-based entity system
- **Global Variables:** Declared in globals.h, defined in globals.c
- **Headers:** Include guards on all .h files
- **Comments:** Section headers like `// ===== SYSTEM NAME =====`

## Compilation Warnings to Ignore (None Expected!)

The code compiles cleanly with:
```bash
gcc -Wall -Wextra -Werror
```

All compiler warnings have been addressed.
