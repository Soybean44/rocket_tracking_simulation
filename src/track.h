#pragma once
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

  inline void render() {
    DrawCubeV(pos, size, color);
    DrawCubeWiresV(pos, Vector3Add(size, Vector3{0.01, 0.01, 0.01}),
                   border_color);
  }
};


void TrackCube(Camera *cam, Vector3 cubePos, Vector2 targetPos);
