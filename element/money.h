#ifndef money_H_INCLUDED
#define money_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h"
#include <stdlib.h>
/*
    [money object]
*/
typedef enum MoneyType
{
    BEEF = 0,
    VEGET,
    STEAK,
    SALAD

} MoneyType;

typedef struct _Money
{
     int x, y;          // the position of image
     int width, height; // the width and height of image
     ALLEGRO_BITMAP *img;
     int map_data[10][16];
     Scene *scene;
     MoneyType order;
     ALLEGRO_BITMAP *order_img;
} Money;



Elements *New_money(int label, int i, int j, Scene* scene);
void New_Order(Money *money);
void _money_load_map(Money *money);
void money_update(Elements *self);
void money_interact(Elements *self, Elements *tar);
void money_draw(Elements *self);
void money_destory(Elements *self);

#endif
