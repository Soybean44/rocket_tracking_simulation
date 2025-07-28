#include <track.h>

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


