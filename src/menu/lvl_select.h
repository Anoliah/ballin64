#ifndef LVL_SELECT_H
#define LVL_SELECT_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"

#define MAX_SLIDES 8

enum Lvl_Select_Menu_State {
    STATE_DEFAULT,
    STATE_MOVING,
    STATE_ASK_ERASE,
    STATE_ERASED
};

enum Delete_Menu_Selected_Option {
    DELETE_YES,
    DELETE_NO
};

s32 lvl_select_update_and_select_level(UNUSED s32 arg, UNUSED s32 unused);

void beh_level_selector_init(void);
void beh_level_selector_loop(void);
void bhv_slide_selector_model_loop(void);

Gfx *geo_lvl_select_strings_and_glyphs(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx);

#endif // LVL_SELECT_H