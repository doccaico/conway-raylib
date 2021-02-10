#include "raylib.h"

#define SCREEN_WIDTH    740
#define SCREEN_HEIGHT   450
#define NUM_PATTERNS    9

#define JCW_WIDTH       60
#define JCW_HEIGHT      40
#define JCW_LIVE_CELLS  25
#define CELL_WIDTH      8
#define CELL_HEIGHT     8

#include "conway.h"
#include "presets.h"

typedef enum {
  RANDOM,
  GOSPER,
  SIMKIN,
  P46,
  GLIDER,
  SIX,
  BI,
  NEW,
  BLOCKER,
} Patterns;

static const char *patternsText[] = {
  "Random",
  "Gosper glider gun",
  "Simkin glider gun",
  "P46 gun",
  "Glider pusher",
  "6 bits",
  "Bi-gun",
  "New gun 1",
  "Blocker",
};

void draw() {
  for (int y = 1; y < JCW_HEIGHT + 1; y++) {
    for (int x = 1; x < JCW_WIDTH + 1; x++) {
      if (JCW_board[y][x] == 1) {
        DrawRectangle(220 + 1 + (x - 1) * CELL_WIDTH, 50 + 1 + (y - 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, BLACK);
      }
    }
  }
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(60);

  int       currentProcess           = RANDOM;
  int       run                      = false;
  bool      boardReload              = true;
  int       wait                     = 0;
  Rectangle toggleRecs[NUM_PATTERNS] = {0};

  for (int i = 0; i < NUM_PATTERNS; i++) {
    toggleRecs[i] = (Rectangle){40.0f, (float)(50 + 36.5 * i), 150.0f, 30.0f};
  }


  JCW_randomize();

  while (!WindowShouldClose()) {
    // Mouse toggle group logic
    for (int i = 0; i < NUM_PATTERNS; i++) {
      if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
          currentProcess = i;
          boardReload    = true;
          run            = false;
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
      run         = false;
    } else if (IsKeyPressed(KEY_UP)) {
      currentProcess--;
      if (currentProcess < 0) {
        currentProcess = NUM_PATTERNS - 1;
      }
      boardReload = true;
      run         = false;
    } else if (IsKeyPressed(KEY_ENTER)) {
      run = !run;
    }

    if (boardReload) {
      JCW_clearBoard();
      switch (currentProcess) {
      case RANDOM:
        JCW_initBoard();
        break;
      case GOSPER:
        JCW_gosperGliderGun();
        break;
      case SIMKIN:
        JCW_simkinGliderGun();
        break;
      case P46:
        JCW_p46Gun();
        break;
      case GLIDER:
        JCW_gliderPusher();
        break;
      case SIX:
        JCW_6bits();
        break;
      case BI:
        JCW_biGun();
        break;
      case NEW:
        JCW_newGun1();
        break;
      case BLOCKER:
        JCW_blocker();
        break;
      default:
        break;
      }
      boardReload = false;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw board
    DrawRectangleLines(220, 50, JCW_WIDTH * CELL_WIDTH + 2, JCW_HEIGHT * CELL_HEIGHT + 2, GRAY);
    draw();

    if (wait == 0) {
      if (run) {
        JCW_nextGeneration();
      }
      wait = 5;
    }
    if (wait > 0) {
      wait -= 1;
    }


    DrawText("R.I.P John Horton Conway", 50, 30, 10, DARKGRAY);
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
