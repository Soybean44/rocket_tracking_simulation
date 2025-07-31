#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

struct State {
  Vector2 integral;
  Vector2 pastError;
};

void TrackCube(Camera *cam, Vector3 cubePos, Vector2 targetPos, State* state);
