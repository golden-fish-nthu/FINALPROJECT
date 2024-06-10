#ifndef guest_H_INCLUDED
#define guest_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [guest object]
*/
typedef struct _guest
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} guest;
Elements *New_guest(int label);
void guest_update(Elements *self);
void guest_interact(Elements *self, Elements *tar);
void guest_draw(Elements *self);
void guest_destory(Elements *self);

#endif
