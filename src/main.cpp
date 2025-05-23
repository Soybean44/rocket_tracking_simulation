#include <algorithm>
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
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
    DrawCubeWiresV(pos, Vector3Add(size, Vector3{0.01, 0.01, 0.01}),
                   border_color);
  }
};

constexpr float delta = 1;
constexpr float step = 0.01;

void TrackCube(Camera *cam, Vector3 cubePos, Vector2 targetPos) {
  bool isNotCenter;
  Vector2 posError, cubeScreenPos;
  // Keep adjusting the camera while the rocket isnt in the center
  // It is in the center when no adjustments ahve been made
  do {
    isNotCenter = false;
    cubeScreenPos = GetWorldToScreen(cubePos, *cam);
    posError = {.x = cubeScreenPos.x - targetPos.x,
                .y = cubeScreenPos.y - targetPos.y};

    if (posError.y < -delta) {
      CameraPitch(cam, step * DEG2RAD, true, false, true); // Move 1 step
      isNotCenter = true;
    }
    if (posError.y > delta) {
      CameraPitch(cam, -step * DEG2RAD, true, false, true); // Move 1 step
      isNotCenter = true;
    }
    if (posError.x < -delta) {
      CameraYaw(cam, step * DEG2RAD, false); // Move 1 step
      isNotCenter = true;
    }
    if (posError.x > delta) {
      CameraYaw(cam, -step * DEG2RAD, false); // Move 1 step
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
  camera.position = (Vector3){0.0f, 10.0f, 20.0f};
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  Cube cube(Vector3{0, 1, 0}, Vector3{2, 2, 2}, RED, BLACK);
  Vector2 cubeScreenPos;
  // start by making the camera look at the rocket directly
  camera.target = cube.pos;
  SetTargetFPS(60);

  float t = 0;
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    cubeScreenPos = GetWorldToScreen(cube.pos, camera);

    t += 5 * dt;
    cube.pos.y = t;                     // Move the rocket up
    cube.pos.x = 9 * (float)sin(t / 2); // Move the rocket horizontally

    TrackCube(&camera, cube.pos, targetPos);

    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    // Draw ground
    DrawPlane(Vector3{0, 0, 0}, Vector2{50, 50}, DARKGREEN);
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
