Helheim Engine 2D
Welcome to Helheim Engine 2D, a lightweight and efficient 2D movement framework built entirely in C. This project serves as the core foundation for what will eventually become a more complex terminal-based game engine.

🚀 Project Overview
Helheim Engine 2D is designed to handle the fundamentals of grid-based navigation. It manages player positioning, collision logic, and real-time environment rendering directly in the console. By utilizing a 2D array system, it creates a structured world where logic meets simplicity.

Current Features
Dynamic Grid System: A 16x16 environment (easily scalable in the code).

Collision Physics: A built-in IsWall check that prevents the player from passing through obstacles (#).

Smooth Input Handling: Uses the conio.h library to ensure the player moves instantly upon keypress without needing to hit enter.

Optimized Rendering: The engine clears and redraws the frame only when an action occurs, keeping the console clean.

🕹️ Controls
Once you compile and run the engine, use the classic WASD layout to navigate:
W: Move Up
A: Move Left
S: Move Down
D: Move Right

🛠️ The Future of Helheim
This is currently the "Alpha" phase of Helheim Engine 2D. I am working on expanding this into a fully-fledged terminal game development kit. Future updates will include:

Entity System: Adding NPCs and enemies with basic AI behaviors.

Map Loader: The ability to design maps in .txt files and load them into the engine.

Combat & Stats: Health bars, inventory systems, and turn-based or real-time combat mechanics.

Color Support: Moving beyond monochrome to bring the world of Helheim to life with ANSI colors.

Developer Note
I created Helheim Engine 2D to explore how low-level programming can simulate complex game mechanics. It’s a passion project focused on clean code and logic efficiency. As the engine grows, the goal is to make it a versatile tool for anyone wanting to build retro-style terminal games.

Feel free to contribute, suggest features, or use the engine for your own experiments.
