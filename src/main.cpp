#include <cmath>
#include <raylib.h>
#include <rcamera.h>

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

constexpr float delta = 1;
constexpr float step = 0.1;

void TrackCube(Camera *cam, Vector3 cubePos, Vector2 targetPos) {
  bool isNotCenter;
  do {
    isNotCenter = false;
    Vector2 cubeScreenPos = GetWorldToScreen(cubePos, *cam);
    Vector2 posError = {.x = cubeScreenPos.x - targetPos.x,
                        .y = cubeScreenPos.y - targetPos.y};

    if (posError.y < -delta) {
      CameraPitch(cam, step * DEG2RAD, true, false, false); // Move 1 step
      isNotCenter = true;
    }
    if (posError.y > delta) {
      CameraPitch(cam, -step * DEG2RAD, true, false, false); // Move 1 step
      isNotCenter = true;
    }
    if (posError.x < -delta) {
      CameraYaw(cam, step * DEG2RAD, true); // Move 1 step
      isNotCenter = true;
    }
    if (posError.x > delta) {
      CameraYaw(cam, -step * DEG2RAD, true); // Move 1 step
      isNotCenter = true;
    }
  } while (isNotCenter);
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
  Vector2 cubeScreenPos;
  camera.target = cube.pos;
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    cubeScreenPos = GetWorldToScreen(cube.pos, camera);

    cube.pos.y += 5 * dt;                    // Move the rocket up
    cube.pos.x = 3 * (float)sin(cube.pos.y); // Move the rocket horizontally

    TrackCube(&camera, cube.pos, targetPos);

    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    DrawPlane(Vector3{0, 0, 0}, Vector2{100, 100}, GRAY);
    cube.render();

    EndMode3D();
    Vector2 posError = {.x = cubeScreenPos.x - targetPos.x,
                        .y = cubeScreenPos.y - targetPos.y};
    const char *pos_str =
        TextFormat("Pos Error: (%f, %f)", posError.x, posError.y);
    DrawText(pos_str, 10, 10, 24, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
