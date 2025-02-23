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
#include "levels/sa/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sa_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _sa_segment_7SegmentRomStart, _sa_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _inside_yay0SegmentRomStart, _inside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _bitfs_skybox_yay0SegmentRomStart, _bitfs_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_5), 
	JUMP_LINK(script_func_global_14), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, sa_area_1),
		WARP_NODE(0x0A, LEVEL_SA, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_SA, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_SA, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -2526, 4003, -14007, 0, -90, 0, (4 << 16), bhvFireBar),
		OBJECT(MODEL_NONE, -1300, 4314, -12576, 0, 90, 0, (4 << 16), bhvFireBar),
		OBJECT(MODEL_NONE, -201, 4734, -14007, 0, -90, 0, (4 << 16), bhvFireBar),
		OBJECT(MODEL_NONE, 1755, 5107, -12576, 0, 90, 0, (4 << 16), bhvFireBar),
		OBJECT(MODEL_NONE, 3038, 5511, -14007, 0, -90, 0, (4 << 16), bhvFireBar),
		OBJECT(MODEL_GOLD_RING, -13042, 2198, 7708, 0, -180, 0, (32 << 16), bhvGoldRing),
		OBJECT(MODEL_CUSTOM_HEART, 12720, 6559, -4592, 0, 0, 0, 0x00000000, bhvRecoveryHeart),
		OBJECT(MODEL_RED_RING, -3983, 4645, -13290, 0, 90, 0, (80 << 16), bhvRedRing),
		OBJECT(MODEL_RED_RING, -4596, 4645, -13290, 0, 90, 0, (80 << 16), bhvRedRing),
		OBJECT(MODEL_RED_RING, -5196, 4645, -13290, 0, 90, 0, (80 << 16), bhvRedRing),
		OBJECT(MODEL_RED_RING, 8672, 6696, -11746, 0, 69, 0, (100 << 16), bhvRedRing),
		OBJECT(MODEL_NONE, -4002, 9535, 5661, 0, -175, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, -175, -4002, 9535, 5661),
		TERRAIN(sa_area_1_collision),
		MACRO_OBJECTS(sa_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_FLAMESTAG),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -175, -4002, 9535, 5661),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
