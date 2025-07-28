#include "track.h"

constexpr float delta = 1;
constexpr float step = 0.01;

// The PID loop for the cube tracking calculates posError which is e(t) as stated in
// https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller#Controller_theory
// We can then set the gain parameters for each stage and hopefully get a working controller 

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


