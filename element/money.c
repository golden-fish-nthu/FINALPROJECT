#include "money.h"
#include <stdio.h>
#include <stdlib.h>
/*
    [money function]
*/
Elements *New_money(int label, int i, int j, Scene* scene)
{
     Money *pDerivedObj = (Money *)malloc(sizeof(Money));
     Elements *pObj = New_Elements(label);
     // setting derived object member
     pDerivedObj->img = al_load_bitmap("assets/image/money.png");
     pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
     pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
     _money_load_map(pDerivedObj);
     pDerivedObj->x = j * pDerivedObj->width;
     pDerivedObj->y = i * pDerivedObj->height;

     // setting the interact object
     pObj->inter_obj[pObj->inter_len++] = Character_L;

     pDerivedObj->scene = scene;
     New_Order(pDerivedObj);

     // setting derived object function
     pObj->pDerivedObj = pDerivedObj;
     pObj->Draw = money_draw;
     pObj->Update = money_update;
     pObj->Interact = money_interact;
     pObj->Destroy = money_destory;
     return pObj;
}
void _money_load_map(Money *money)
{
     FILE *data;
     data = fopen("assets/map/gamescene_map.txt", "r");
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                fscanf(data, "%d", &money->map_data[i][j]);
          }
     }
     fclose(data);
}
void money_update(Elements *ele) 
{
}
void money_interact(Elements *self, Elements *tar)
{
     Money* money = (Money* )self->pDerivedObj;
     if (tar->label == Character_L)
     {
          Character *chara = (Character *)(tar->pDerivedObj);
          if (((chara->x >=  money->x && chara->x < money->x + money->width) || (chara->x + chara->width >= money->x && chara->x < money->x + money->width))
          && ((chara->y >=  money->y && chara->y < money->y + money->height) || (chara->y + chara->height >= money->y && chara->y < money->y + money->height))
          && key_state[ALLEGRO_KEY_E])
          {
               CharacterType character_type = chara->state;
               MoneyType money_type = money->order;
               
               if (character_type == MOVE)
               {
                    printf("money thing not found\n");
               }
               else if ((character_type == TAKEVEGE && money_type == VEGET)||
               (character_type == TAKEBEEF && money_type == BEEF)||
               (character_type == TAKESTEAK && money_type == STEAK)||
               (character_type == TAKESALAD && money_type == SALAD))
               {
                    // correct order
                    switch (character_type)
                    {
                    case TAKEVEGE:
                         money->scene->score += 50;
                         chara->state = MOVE;
                         New_Order(money);
                         break;
                    case TAKEBEEF:
                         money->scene->score += 100;
                         chara->state = MOVE;
                         New_Order(money);
                         break;
                    case TAKESTEAK:
                         money->scene->score += 400;
                         chara->state = MOVE;
                         New_Order(money);
                         break;
                    case TAKESALAD:
                         money->scene->score += 200;
                         chara->state = MOVE;
                         New_Order(money);
                         break;
                    default:
                         printf("money.c food not found\n");
                         break;
                    }
               }
               else
               {
                    int penalty_time = 30;
                    double* timer = money->scene->countdowntimerpointer;
                    // wrong order
                    if (*timer - penalty_time <= 0)
                         *timer = 0.01;
                    else
                         *timer -= penalty_time;
                         
                    chara->state = MOVE;
               }
          }
     }
}
void New_Order(Money *money)
{
     money->order = rand() % 4;
     char order_img_type[4][10] = {"beef", "veget", "steak", "salad"};
     char buffer[50];
     sprintf(buffer, "assets/image/money_%s.png", order_img_type[money->order]);
     money->order_img = al_load_bitmap(buffer);
}

void money_draw(Elements *self)
{
     Money *Obj = ((Money *)(self->pDerivedObj));
     for (int i = 0; i < 10; i++)
     {
          for (int j = 0; j < 16; j++)
          {
                if (Obj->map_data[i][j]==13)
                {
                     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
                     al_draw_bitmap(Obj->order_img, Obj->x, Obj->y+50, 0);
                }
          }
     }
}
void money_destory(Elements *self)
{
     Money *Obj = ((Money *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
     free(Obj);
     free(self);
}
