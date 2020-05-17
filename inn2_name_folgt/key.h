#include "sprite.cpp"

#ifndef KEY_H
#define KEY_H

class Key : public Sprite
{
public:
  Key(int x, int y, int w, int h, int t);
  
  ~Key() = default;
};

#endif //KEY_H
