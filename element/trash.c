#include "trash.h"
#include "../shapes/Rectangle.h"
/*
    [trash function]
*/
Elements *New_Trash(int label)
{
     Trash *pDerivedObj = (Trash *)malloc(sizeof(Trash));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/trash.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     pDerivedObj->x = 45;
     pDerivedObj->y = 560;
     pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                                     pDerivedObj->y + pDerivedObj->height / 3,
                                                     pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                                     pDerivedObj->y + 2 * pDerivedObj->height / 3);
     pObj->inter_obj[pObj->inter_len++] = Character_L;
     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Update = Trash_update;
     pObj->Interact = Trash_interact;
     pObj->Draw = Trash_draw;
     pObj->Destroy = Trash_destory;
     return pObj;
}
void Trash_update(Elements *self) {}
void Trash_interact(Elements *self, Elements *tar) 
{
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
		Trash *trash = (Trash *)(self->pDerivedObj);
          if (((chara->x >=  trash->x && chara->x < trash->x + trash->width) || (chara->x + chara->width >= trash->x && chara->x < trash->x + trash->width))
               && ((chara->y >=  trash->y && chara->y < trash->y + trash->height) || (chara->y + chara->height >= trash->y && chara->y < trash->y + trash->height))
               && key_state[ALLEGRO_KEY_E])
          {
               chara->state = MOVE;
          }
     }
}
void Trash_draw(Elements *self)
{
     Trash *Obj = ((Trash *)(self->pDerivedObj));
     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Trash_destory(Elements *self)
{
     Trash *Obj = ((Trash *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj->hitbox);
     free(Obj);
     free(self);
}
