#include <raylib.h>

int main(void) {
  InitWindow(1000, 800, "Test");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
