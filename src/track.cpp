#include "track.h"
#include <iostream>

constexpr float delta = 1;
constexpr float step = 0.01;
float Kp = 1e-1;
float Kd = 1e-1;
float Ki = 1e-1;

// The PID loop for the cube tracking calculates posError which is e(t) as
// stated in
// https://en.wikipedia.org/wiki/Proportional%E2%80%93integral%E2%80%93derivative_controller#Controller_theory
// We can then set the gain parameters for each stage and hopefully get a
// working controller

void TrackCube(Camera *cam, Vector3 cubePos, Vector2 targetPos, State *state) {
  float dt = GetFrameTime();
  Vector2 cubeScreenPos = GetWorldToScreen(cubePos, *cam);
  Vector2 error = {.x = cubeScreenPos.x - targetPos.x,
                   .y = targetPos.y - cubeScreenPos.y};
  Vector2 derivative = {0};

  if (!dt) {
    Vector2 derivative = {
      .x = (error.x - state->pastError.x) / dt,
      .y = (error.y - state->pastError.y) / dt,
    };
  } 

  state->integral.x = error.x * dt;
  state->integral.y = error.y * dt;


  float motor_speed_x = Kp * error.x + Ki * state->integral.x +
                        Kd * derivative.x;
  float motor_speed_y = Kp * error.y + Ki * state->integral.y +
                        Kd * derivative.y;

  state->pastError = error;

  std::cout << "Error: (" << error.x << ", " << error.y
            << ")\n";
  std::cout << "Motor speed: (" << motor_speed_x << ", " << motor_speed_y
            << ")\n";

  CameraPitch(cam, motor_speed_y * step * DEG2RAD, true, false,
              true);                                     // Move vertically
  CameraYaw(cam, motor_speed_x * step * DEG2RAD, false); // Move horizontally
}
