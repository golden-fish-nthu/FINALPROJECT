#include "pot.h"
#include "../shapes/Rectangle.h"
/*
    [pot function]
*/
Elements *New_pot(int label)
{
     pot *pDerivedObj = (pot *)malloc(sizeof(pot));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/pot.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 680;
     pDerivedObj->y = 300;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                                     pDerivedObj->y + pDerivedObj->height / 3,
                                                     pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                                     pDerivedObj->y + 2 * pDerivedObj->height / 3);
     // setting the interact object
     pObj->inter_obj[pObj->inter_len++] = Character_L;
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = pot_update;
     pObj->Interact = pot_interact;
     pObj->Draw = pot_draw;
     pObj->Destroy = pot_destory;
     return pObj;
}
void pot_update(Elements *self) {}
void pot_interact(Elements *self, Elements *tar) 
{
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
          pot *potpointer = (pot *)(self->pDerivedObj);
          int right_limit = WIDTH - chara->width / 2;
          int left_limit = 0 - chara->width / 2;
          // printf("chara : (%d, %d)\n", chara->x, chara->y);
          // printf("pan : (%d, %d)\n", pan->x, pan->y);
          if (((chara->x >= potpointer->x && chara->x < potpointer->x + potpointer->width) || (chara->x + chara->width >= potpointer->x && chara->x < potpointer->x + potpointer->width)) &&
           ((chara->y >= potpointer->y && chara->y < potpointer->y + potpointer->height) || (chara->y + chara->height >= potpointer->y && chara->y < potpointer->y + potpointer->height)) && 
           key_state[ALLEGRO_KEY_SPACE])
          {
               switch (chara->state)
               {
               case MOVE:
                    break;
               case TAKEVEGE:
               // cook beef
                    chara->state = TAKESALAD;
                    break;
               default:
                    break;
               }
               printf("use pot in pot.c");
          }

          if (chara->x < left_limit)
          {
               _Character_update_position(tar, (left_limit - chara->x), 0);
          }
          else if (chara->x > right_limit)
          {

               _Character_update_position(tar, (right_limit - chara->x), 0);
          }
     }
}
void pot_draw(Elements *self)
{
     pot *Obj = ((pot *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void pot_destory(Elements *self)
{
     pot *Obj = ((pot *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
