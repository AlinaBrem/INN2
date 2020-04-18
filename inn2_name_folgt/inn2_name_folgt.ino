#include <Gamebuino-Meta.h>

#include "texture.cpp"
#include "sprite.cpp"
#include "wonder_wall.cpp"
#include "linked_list.cpp"
#include "map.cpp"

LinkedList<Sprite *> sprite_list = LinkedList<Sprite *>();

WonderWall *ww = new WonderWall(35, 30, 8, 8, 23);

Map mymap = Map::load_map1(&sprite_list);

void setup()
{
  gb.begin();
  sprite_list.append_value((Sprite *)ww);
}

void loop()
{
  while (!gb.update())
    gb.display.clear(/*RED*/);

  if (gb.buttons.repeat(BUTTON_UP, 2))
  {
    ww->go_up();
  }
  else if (gb.buttons.repeat(BUTTON_DOWN, 2))
  {
    ww->go_down();
  }
  else if (gb.buttons.repeat(BUTTON_LEFT, 2))
  {
    ww->go_left();
  }
  else if (gb.buttons.repeat(BUTTON_RIGHT, 2))
  {
    ww->go_right();
  }

  if (gb.buttons.repeat(BUTTON_B, 0))
  {
    gb.display.drawImage(0, 0, my_img_buf);
    uint16_t ram = gb.getFreeRam();
    gb.display.print("RAM:");
    gb.display.println(ram);
  }
  else
  {
    draw();
    if (mymap.solid_at_position(ww->get_position()))
      gb.display.print("collision");
  }
}

void draw()
{
  auto it = sprite_list.get_Iterator();
  while (it.has_next())
  {
    Sprite **temp = it.get_next();
    (*temp)->draw();
  }
}
