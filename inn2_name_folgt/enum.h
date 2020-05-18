#ifndef ENUM_H
#define ENUM_H

enum class ComputerTextureId
{
  up_on = 43,
  up_off = 41,
  down_on = 32,
  down_off = 30,
  left_on = 33,
  left_off = 31,
  right_on = 42,
  right_off = 40
};

enum class PlayerTextureId
{
  move_up = 61,
  move_down = 71,
  move_left = 76,
  move_right = 66,
  idle_up = 60,
  idle_down = 70,
  idle_left = 75,
  idle_right = 65,
  interacting_up = 64,
  interacting_down = 74,
  interacting_left = 79,
  interacting_right = 69,
};

enum class DoorTextureId
{
  open = 49,
  closed = 48
};

// position of the collision points
//    *     *
//  *         *
//       P
//  *         *
//    *     *
enum class CollisionPoints
{
  front_left,
  front_right,
  back_left,
  back_right,
  middle_left_front,
  middle_left_back,
  middle_right_front,
  middle_right_back
};

enum class Direction
{
  up,
  down,
  left,
  right
};

enum TileType
{
  solid,
  not_solid,
  key,
  computer,
  door,
  player,
  trap
};

#endif //ENUM_H