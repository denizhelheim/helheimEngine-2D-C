# Helheim Engine 2D - Architecture Overview

## Module Dependency Graph

```
main.c
  ├── globals.h          (Core game state and constants)
  ├── types.h            (Type definitions)
  ├── rendering.h        (Display system)
  ├── tile.h             (Map/tile system)
  ├── gameplay.h         (Game flow)
  └── menu.h             (UI menus)

globals.c
  └── types.h

rendering.c
  ├── types.h
  ├── globals.h
  └── windows.h          (Windows API)

entity.c
  ├── types.h
  ├── globals.h
  ├── math.h
  └── stdlib.h

particle.c
  ├── types.h
  └── globals.h

collision.c
  ├── types.h
  └── globals.h

tile.c
  ├── types.h
  ├── globals.h
  └── stdlib.h

inventory.c
  ├── types.h
  ├── globals.h
  └── string.h

input.c
  ├── types.h
  ├── globals.h
  ├── particle.h
  ├── conio.h
  └── math.h

gameplay.c
  ├── types.h
  ├── globals.h
  ├── entity.h
  ├── tile.h
  ├── rendering.h
  ├── input.h
  ├── particle.h
  ├── utils.h
  └── conio.h

menu.c
  ├── types.h
  ├── globals.h
  ├── entity.h
  ├── tile.h
  ├── conio.h
  └── stdio.h

utils.c
  └── windows.h
```

## Core Systems

### 1. Type System (`types.h`)
- **Enums:** EntityType, TileType, GameState, Difficulty
- **Structures:** Entity, Particle, InventoryItem, GameConfig, Vector2, AnimationComponent, PhysicsComponent, HealthComponent, BehaviorComponent

### 2. Global State (`globals.h/c`)
- Game state and configuration
- Map and entity arrays
- Player reference
- Score and health tracking
- Console buffers

### 3. Entity System (`entity.c`)
- Entity creation and destruction
- Animation component management
- Physics and health components
- Enemy AI (patrol, chase behaviors)
- Vision-based enemy detection

### 4. Rendering System (`rendering.c`) **[FIXED]**
- Console cursor positioning
- Screen buffer management
- Efficient partial updates
- **Fixed UI text alignment** with proper formatting
- Debug info display

### 5. Game Flow (`gameplay.c`)
- Level loading and initialization
- Main game loop
- Game state transitions (Playing → Paused → GameOver → Won)
- End screen display

### 6. Input System (`input.c`)
- Player movement handling
- Keyboard input processing
- Collision checking with movement
- Collectible pickup logic
- Enemy collision (damage)
- Hazard detection

### 7. Menu System (`menu.c`)
- Main menu with 8 options
- Settings menu (particles, animations, debug)
- Difficulty selector (Easy/Normal/Hard)
- Advanced level editor with 2D cursor
- Tutorial/how-to-play screen
- Credits/about screen

### 8. Tile System (`tile.c`)
- Tile type management (walls, lava, ice, exit, spawn)
- Tilemap initialization
- Default map generation with random walls and collectibles
- Walkability checks

### 9. Utility Systems
- **Collision (`collision.c`):** AABB collision detection, wall/hazard checks
- **Particle (`particle.c`):** Particle emission and updates
- **Inventory (`inventory.c`):** Item management
- **Utils (`utils.c`):** High-resolution timing with Windows performance counters

## Data Flow

```
Input → HandleInput() 
  → MovePlayerTo() 
    → Collision checks
    → Score updates
    → State changes

Update Loop:
  UpdateEntities() → UpdateEnemyAI()
  UpdateParticles()
  RenderGame() → DrawGameUI() [FIXED]

Game State Machine:
  STATE_MENU → STATE_PLAYING ↔ STATE_PAUSED
       ↓            ↓
  STATE_EDITOR  STATE_GAMEOVER/WON
```

## Build Targets

- **Release:** Optimized with `-O2` flag
- **Debug Ready:** Can add `-g` flag for debugging
- **Warnings:** All warnings enabled with `-Wall -Wextra`
- **Linking:** Requires `-lm` for math library (sqrt, cos, sin)

## Performance Characteristics

- **Rendering:** Incremental screen updates (only changed cells)
- **Frame Rate:** Configurable 20 FPS target
- **Memory:** Fixed arrays with MAX_ENTITIES=100, MAX_PARTICLES=500
- **Timing:** High-resolution performance counter based timing

## Future Enhancement Points

1. **Loading System:** Save/load custom levels to files
2. **Asset Manager:** Separate asset loading module
3. **Event System:** Event dispatcher for game events
4. **Sound System:** Audio module (currently disabled)
5. **Networking:** Multi-player support
6. **Configuration:** Load settings from config files
7. **Console Improvements:** Better color support
8. **Physics:** More advanced physics engine
