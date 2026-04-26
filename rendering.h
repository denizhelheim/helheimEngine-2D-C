#ifndef RENDERING_H
#define RENDERING_H

// Console functions
void SetCursorPosition(int x, int y);
void HideCursor();
void InitializeScreenBuffers();
void ClearGameScreen();

// Rendering
void RenderGame();
void DrawDebugInfo();

#endif // RENDERING_H
