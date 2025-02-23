#include "game/level_update.h"

f32 gold_ring_calc_mario_dist(void) {
    Vec3f marioDist;
    vec3_diff(marioDist, &o->oPosVec, gMarioState->pos);
    marioDist[1] += 80.0f;
    return vec3_dot(marioDist, &o->oGoldRingNormalVec);
}

f32 gold_ring_check_in_range(f32 dist) {
    return (sqrtf(sqr(o->oPosX - gMarioObject->header.gfx.pos[0]) +
                    sqr(o->oPosY - gMarioObject->header.gfx.pos[1]) + 
                    sqr(o->oPosZ - gMarioObject->header.gfx.pos[2])) < dist);
}

void gold_ring_check_collision() {
    f32 marioDistInFront = gold_ring_calc_mario_dist();

    if (!gold_ring_check_in_range(1000.0f)){
        o->oGoldRingMarioDistInFront = marioDistInFront;
        return;
    }

    if (o->oGoldRingMarioDistInFront * marioDistInFront < 0.0f) {
        gCanRestartLevel = 0;
        play_sound(SOUND_MENU_COLLECT_SECRET, gGlobalSoundSource);
        level_control_timer(TIMER_CONTROL_STOP);
        
        play_course_clear(FALSE);
        o->oAction = 1;
    }

    o->oGoldRingMarioDistInFront = marioDistInFront;
}

void gold_ring_send_to_results() {
    o->oTimer++;
    gCameraMovementFlags |= CAM_MOVE_FIX_IN_PLACE;
    if(o->oTimer > 60) {
        //Send mario to end game play state
        set_play_mode(PLAY_MODE_ENDING_LEVEL);
    }
}

//This handles starting the timer
void bhv_gold_ring_init(void) {
    gCanRestartLevel = 1;
    o->oGoldRingNormalX = sins(o->oFaceAngleYaw);
    o->oGoldRingNormalY = sins(o->oFaceAnglePitch);
    o->oGoldRingNormalZ = coss(o->oFaceAngleYaw);

    o->oGoldRingMarioDistInFront = gold_ring_calc_mario_dist();

    o->oAction = 0;
    o->oTimer = 0;

    //Behavior param = seconds
    gSlideTimeToBeat = o->oBehParams2ndByte * 30;
    level_control_timer(TIMER_CONTROL_SHOW);
    level_control_timer(TIMER_CONTROL_START);
}

//Check for collision with mario
void bhv_gold_ring_loop(void) {
    if(o->oAction == 0){
        gold_ring_check_collision();
    } else {
        gold_ring_send_to_results();
    }
    o->oFaceAngleRoll += 0x300;
}

//[TUTORIAL] Check for collision with mario
void bhv_gold_ring_tutorial_loop(void) {
    if(o->oAction == 0){
        gold_ring_check_collision();
    } else {
        gold_ring_send_to_results();
    }
    o->oFaceAngleRoll += 0x300;
}

//[TUTORIAL] Don't start timer
void bhv_gold_ring_tutorial_init(void) {
    o->oGoldRingNormalX = sins(o->oFaceAngleYaw);
    o->oGoldRingNormalY = sins(o->oFaceAnglePitch);
    o->oGoldRingNormalZ = coss(o->oFaceAngleYaw);

    o->oGoldRingMarioDistInFront = gold_ring_calc_mario_dist();

    o->oAction = 0;
    o->oTimer = 0;

    //Behavior param = seconds
    gSlideTimeToBeat = 0xFFFF;
}