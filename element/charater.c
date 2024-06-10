#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>

/*
   [Character function]
*/
Elements *New_Character(int label, Scene* scene)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[5][10] = {"move", "takebeef", "takevege", "takesteak", "takesalad"};
    for (int i = 0; i < 5; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/godhotpot.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 200;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 100;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    // setting the interact object

    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = MOVE;
    pDerivedObj->new_proj = false;
    pDerivedObj->scene = scene;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(ele->pDerivedObj));
    if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_W])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, -5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_S])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, 5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_W])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, -5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_S])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, 5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            _Character_update_position(ele, 0, -5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            _Character_update_position(ele, 0, 5);
            chara->state = MOVE;
        }
        
        if (chara->gif_status[chara->state]->done)
            chara->state = MOVE;
    }
    else{
    	if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_W])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, -5);
        }
        else if (key_state[ALLEGRO_KEY_A] && key_state[ALLEGRO_KEY_S])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, 5);
        }
        else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_W])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, -5);
        }
        else if (key_state[ALLEGRO_KEY_D] && key_state[ALLEGRO_KEY_S])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, 5);
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(ele, -5, 0);
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(ele, 5, 0);
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            _Character_update_position(ele, 0, -5);
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            _Character_update_position(ele, 0, 5);
        }
    }
}

void Character_draw(Elements *const ele)
{
    Character *chara = ((Character *)(ele->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());

    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, chara->dir ? ALLEGRO_FLIP_HORIZONTAL : 0);
    }
}

void Character_destory(Elements *const ele)
{
    Character *Obj = ((Character *)(ele->pDerivedObj));

    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
    {
        algif_destroy_animation(Obj->gif_status[i]);
    }

    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Character_update_position(Elements *const ele, int dx, int dy)
{
    Character *chara = ((Character *)(ele->pDerivedObj));
    int new_x = chara->x + dx;
    int new_y = chara->y + dy;

    Floor* floor = (Floor*) chara->scene->ele_list[Floor_L]->ele->pDerivedObj;

    bool collision = false;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            int barrier_x = j * floor->width;
            int barrier_y = i * floor->height;
            int torrence = 10;

            if ((floor->map_data[i][j] == 1 || floor->map_data[i][j] == 10 || floor->map_data[i][j] == 11) &&
            (((new_x >=  barrier_x+torrence && new_x < barrier_x + floor->width-torrence) || (new_x + chara->width >= barrier_x+torrence && new_x < barrier_x + floor->width-torrence))
            && ((new_y >=  barrier_y+torrence && new_y < barrier_y + floor->height-torrence) || (new_y + chara->height >= barrier_y+torrence && new_y < barrier_y + floor->height-torrence))))
            {
                collision = true;
                break;
            }
            
        }
        if (collision) break;
    }

    if (collision) return;

    // Check if the new position is within the boundaries
    if (new_x >= 0 && new_x + chara->width <= WIDTH)
    {
        chara->x = new_x;
        chara->hitbox->update_center_x(chara->hitbox, dx);
    }

    if (new_y >= 0 && new_y + chara->height <= HEIGHT)
    {
        chara->y = new_y;
        chara->hitbox->update_center_y(chara->hitbox, dy);
    }
}

void Character_interact(Elements *const self, Elements *const target) 
{
}
