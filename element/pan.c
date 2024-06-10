#include "pan.h"
#include "../shapes/Rectangle.h"
/*
    [pan function]
*/
Elements *New_Pan(int label)
{
     Pan *pDerivedObj = (Pan *)malloc(sizeof(Pan));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/pan.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 480;
     pDerivedObj->y = 325;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                         pDerivedObj->y + pDerivedObj->height / 3,
                                         pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                         pDerivedObj->y + 2 * pDerivedObj->height / 3);
     // setting the interact object
     pObj->inter_obj[pObj->inter_len++] = Character_L;
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = Pan_update;
     pObj->Interact = Pan_interact;
     pObj->Draw = Pan_draw;
     pObj->Destroy = Pan_destory;
     return pObj;
}
void Pan_update(Elements *self) {}
void Pan_interact(Elements *self, Elements *tar)
{
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
          Pan *pan = (Pan *)(self->pDerivedObj);
          int right_limit = WIDTH - chara->width / 2;
          int left_limit = 0 - chara->width / 2;
          // printf("chara : (%d, %d)\n", chara->x, chara->y);
          // printf("pan : (%d, %d)\n", pan->x, pan->y);
          if (((chara->x >= pan->x && chara->x < pan->x + pan->width) || (chara->x + chara->width >= pan->x && chara->x < pan->x + pan->width)) &&
           ((chara->y >= pan->y && chara->y < pan->y + pan->height) || (chara->y + chara->height >= pan->y && chara->y < pan->y + pan->height)) && 
           key_state[ALLEGRO_KEY_SPACE])
          {
               switch (chara->state)
               {
               case MOVE:
                    break;
               case TAKEBEEF:
               // cook beef
                    chara->state = TAKESTEAK;
                    break;
               default:
                    break;
               }
               printf("use pan in pan.c");
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
void Pan_draw(Elements *self)
{
     Pan *Obj = ((Pan *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Pan_destory(Elements *self)
{
     Pan *Obj = ((Pan *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
