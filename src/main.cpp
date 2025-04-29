#include <raylib.h>

int main(void) {
  InitWindow(1000, 800, "Test");

  Camera3D camera = {0};
  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(SKYBLUE);

    BeginMode3D(camera);

    DrawPlane(Vector3{0, 0, 0}, Vector2{10, 10}, GRAY);
    DrawCubeV(Vector3{0, 0, 0}, Vector3{1, 1, 1}, RED);

    EndMode3D();
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
