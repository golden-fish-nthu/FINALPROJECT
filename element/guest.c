#include "guest.h"
#include "../shapes/Rectangle.h"
/*
   [guest function]
*/
Elements *New_guest(int label)
{
    guest *pDerivedObj = (guest *)malloc(sizeof(guest));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/guest.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 400;
    pDerivedObj->y = 500;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = guest_update;
    pObj->Interact = guest_interact;
    pObj->Draw = guest_draw;
    pObj->Destroy = guest_destory;
    return pObj;
}
void guest_update(Elements *self) {}
void guest_interact(Elements *self, Elements *tar) {}
void guest_draw(Elements *self)
{
    guest *Obj = ((guest *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void guest_destory(Elements *self)
{
    guest *Obj = ((guest *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
