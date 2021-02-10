// #include <stdlib.h>
//
#define JCW_WIDTH       60
#define JCW_HEIGHT      40
// #define JCW_LIVE_CELLS  30
#define JCW_LIVE_CELLS  20
// #define WAIT = 150
#include "conway.h"

#define CELL_WIDTH 8
#define CELL_HEIGHT 8

/*******************************************************************************************
 *
 *   raylib [textures] example - Image processing
 *
 *   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
 *
 *   This example has been created using raylib 3.5 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2016 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>             // Required for: free()

#define NUM_PATTERNS  3

typedef enum {
  RANDOM,
  MANUAL,
  EMT,
} Patterns;

static const char *patternsText[] = {
  "RANDOM",
  "MANUAL",
  "EMT",
};

void drawRandom() {
  for (int y = 1; y < JCW_HEIGHT + 1; y++) {
    for (int x = 1; x < JCW_WIDTH + 1; x++) {
      // putchar(JCW_board[y][x] == 1 ? '*' : ' ');
      if (JCW_board[y][x] == 1) {
        DrawRectangle(220+1+(x-1)*CELL_WIDTH, 50+1+(y-1)*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, BLACK);
      }
    }
  }
}

int main(void) {
  const int screenWidth  = 740;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Conway's Game of Life");


  int  currentProcess = RANDOM;
  bool boardReload    = true;
  int         wait = 0;
  Rectangle toggleRecs[NUM_PATTERNS] = {0};

  for (int i = 0; i < NUM_PATTERNS; i++) {
    toggleRecs[i] = (Rectangle){40.0f, (float)(50 + 32 * i), 150.0f, 30.0f};
  }

  // SetTargetFPS(60);
  SetTargetFPS(30);

  while (!WindowShouldClose()) {
    // Mouse toggle group logic
    for (int i = 0; i < NUM_PATTERNS; i++) {
      if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
          currentProcess = i;
          boardReload    = true;
        }
        break;
      }
    }

    // Keyboard toggle group logic
    if (IsKeyPressed(KEY_DOWN)) {
      currentProcess++;
      if (currentProcess > (NUM_PATTERNS - 1)) {
        currentProcess = 0;
      }
      boardReload = true;
    } else if (IsKeyPressed(KEY_UP)) {
      currentProcess--;
      if (currentProcess < 0) {
        currentProcess = NUM_PATTERNS - 1;
      }
      boardReload = true;
    }

    // Reload board when required
    if (boardReload) {
      switch (currentProcess) {
      case RANDOM:
        JCW_clearBoard();
        JCW_randomize();
        JCW_initBoard();
        break;
      case MANUAL:
        // DrawRectangle(0,0,20,20,DARKGRAY);
        break;
      default: break;
      }
      boardReload = false;
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // DrawRectangle(280, 50, 20, 20, BLACK);
    DrawRectangleLines(220, 50, JCW_WIDTH*CELL_WIDTH+2, JCW_HEIGHT*CELL_HEIGHT+2, GRAY);
    drawRandom();

    // if (IsKeyPressed(KEY_ENTER)) {
    // }
    if (wait == 0) {
      JCW_nextGeneration();
      wait   = 10;
    }
    if (wait > 0) {
      wait -= 1;
    }


    DrawText("IMAGE PROCESSING:", 40, 30, 10, DARKGRAY);

    // Draw rectangles
    for (int i = 0; i < NUM_PATTERNS; i++) {
      DrawRectangleRec(toggleRecs[i], (i == currentProcess) ? SKYBLUE : LIGHTGRAY);
      DrawRectangleLines((int)toggleRecs[i].x, (int)toggleRecs[i].y,
                         (int)toggleRecs[i].width, (int)toggleRecs[i].height, (i == currentProcess) ? BLUE : GRAY);
      int x = (int)(toggleRecs[i].x + toggleRecs[i].width / 2 - MeasureText(patternsText[i], 10) / 2);
      int y = (int)toggleRecs[i].y + 11;
      DrawText(patternsText[i], x, y, 10, (i == currentProcess) ? DARKBLUE : DARKGRAY);
    }

    EndDrawing();
  }

  CloseWindow();

  return (0);
}
