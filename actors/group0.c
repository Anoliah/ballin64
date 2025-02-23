#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

// Note: This bin does not use bin IDs, unlike the other segmented bins.
#include "mario/model.inc.c"

#include "bubble/model.inc.c"

#include "walk_smoke/model.inc.c"

#include "burn_smoke/model.inc.c"

#include "small_water_splash/model.inc.c"

#include "water_wave/model.inc.c"

#include "sparkle/model.inc.c"

#include "water_splash/model.inc.c"

#include "white_particle_small/model.inc.c"

#include "sparkle_animation/model.inc.c"

#ifdef S2DEX_TEXT_ENGINE
#include "src/s2d_engine/s2d_config.h"
#include FONT_C_FILE
#endif

#include "ballin/model.inc.c"
#include "mini_big_bounce/model.inc.c"
#include "mini_marioikart/model.inc.c"
#include "mini_snow/model.inc.c"
#include "gold_ring/model.inc.c"
#include "red_ring/model.inc.c"
#include "fire_bar/model.inc.c"
#include "retro_mini/model.inc.c"
#include "mini_mario_kart/model.inc.c"
#include "mini_lava/model.inc.c"
#include "custom_heart/model.inc.c"
#include "tutorial_base/model.inc.c"
#include "tutorial_exclamation/model.inc.c"
#include "mini_tutorial/model.inc.c"
#include "mini_ethan/model.inc.c"
#include "mini_logo/model.inc.c"
#include "level_menu/model.inc.c"
#include "bumper/model.inc.c"
#include "mini_pinball/model.inc.c"