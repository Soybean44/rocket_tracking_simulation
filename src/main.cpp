#include <cmath>
#include <raylib.h>
#include <rcamera.h>
#include <sstream>

class Cube {
public:
  Vector3 pos;
  Vector3 size;
  Color color;
  Color border_color;

  Cube(Vector3 pos, Vector3 size, Color color, Color border_color)
      : pos(pos), size(size), color(color), border_color(border_color) {}

  void render() {
    DrawCubeV(pos, size, color);
    DrawCubeWiresV(pos, size, border_color);
  }
};

void TrackCube(Camera *cam, Vector2 pos) {
  // CameraPitch(&camera, 0.01, true, false, true); command to rotate camera
}

int main(void) {
  int screenWidth = 1000;
  int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Test");

  Vector2 targetPos = {(float)(screenWidth / 2), (float)(screenHeight / 2)};

  Camera3D camera = {0};
  camera.position = (Vector3){0.0f, 10.0f, 10.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Cube cube(Vector3{0, 1, 0}, Vector3{2, 2, 2}, RED, BLACK);

  camera.target = cube.pos; // This is the ideal case
  Vector2 cubeScreenPos;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    cubeScreenPos = GetWorldToScreen(cube.pos, camera);
    TrackCube(&camera, cubeScreenPos);

    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    DrawPlane(Vector3{0, 0, 0}, Vector2{100, 100}, GRAY);
    cube.render();

    EndMode3D();
    Vector2 posError = {.x = cubeScreenPos.x - targetPos.x,
                        .y = cubeScreenPos.y - targetPos.y};
    const char *pos_str =
        TextFormat("Pos Error: (%d, %d)", (int)posError.x, (int)posError.y);
    DrawText(pos_str, 10, 10, 24, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
