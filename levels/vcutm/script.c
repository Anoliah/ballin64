#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/vcutm/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_vcutm_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0_TEXTURE(0x09, _outside_yay0SegmentRomStart, _outside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x07, _vcutm_segment_7SegmentRomStart, _vcutm_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x05, _group8_yay0SegmentRomStart, _group8_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group8_geoSegmentRomStart, _group8_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xa, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_9), 
	LOAD_MODEL_FROM_GEO(MODEL_VCUTM_SEESAW_PLATFORM, vcutm_geo_0001F0), 
	LOAD_MODEL_FROM_GEO(MODEL_VCUTM_WARP_PIPE, warp_pipe_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, vcutm_area_1),
		WARP_NODE(0x0A, LEVEL_VCUTM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_VCUTM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_VCUTM, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 14086, 11352, 14589, 0, 0, 0, (5 << 16), bhvTtmBowlingBallSpawner),
		OBJECT(MODEL_BUMPER, 953, 9921, -3080, 0, 90, 0, (25 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, 3944, 9921, -820, 0, -90, 0, (25 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, 953, 9921, 1659, 0, 90, 0, (25 << 16), bhvBumper),
		OBJECT(MODEL_NONE, 4636, 10184, 884, 0, 0, 0, (9 << 16), bhvFireBar),
		OBJECT(MODEL_NONE, 4636, 10184, -2170, 0, -180, 0, (9 << 16), bhvFireBar),
		OBJECT(MODEL_GOLD_RING, -11097, -4886, 15385, 0, 0, 0, (32 << 16), bhvGoldRing),
		OBJECT(MODEL_BUMPER, 9842, 6648, -7337, 0, -180, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, 1591, 5062, -7337, 0, -180, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, -6547, 3583, -7337, 0, -180, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, 6300, 5941, -12813, 0, 0, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, -2726, 4252, -12813, 0, 0, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, -7873, 3236, -7313, 0, -146, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, -14410, 3236, -7596, 0, 87, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_BUMPER, -8127, 3236, -13125, 0, -2, 0, (48 << 16), bhvBumper),
		OBJECT(MODEL_NONE, -1980, -7863, 14034, 0, 90, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 90, -1980, -7863, 14034),
		TERRAIN(vcutm_area_1_collision),
		MACRO_OBJECTS(vcutm_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_WALUIGI),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 90, -1980, -7863, 14034),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
