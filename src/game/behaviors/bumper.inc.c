struct ObjectHitbox sBumperHitBox = {
    /* interactType:      */ INTERACT_NONE,
    /* downOffset:        */ 100,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 325,
    /* height:            */ 325,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bumper_slide() {
    //Move to target
    o->oBumperTimer++;
    if(o->oBumperTimer >= o->oBumperSlideLength) {
        o->oForwardVel *= -1;
        o->oBumperTimer = 0;
    }
    cur_obj_move_using_fvel_and_gravity();
}

//Check for collision
void bumper_act_0(void) {
    if(obj_check_if_collided_with_object(o, gMarioObject)) {
        o->oAction = 1;
        //Send Mario backwards
        gMarioState->forwardVel += 32;
        gMarioState->forwardVel *= -1;
        gMarioState->slideVelX *= -1;
        gMarioState->slideVelZ *= -1;
        if(gMarioState->pos[1] - o->oPosY > 50) {
            gMarioState->vel[1] *= -1;
            gMarioState->vel[1] += 20;
            if(gMarioState->action == ACT_GROUND_POUND) {
                gMarioState->action = ACT_FREEFALL;
            }
        } else if (gMarioState->action == ACT_IDLE){
            gMarioState->slideVelX += -30;
            gMarioState->slideVelZ += -30;
            gMarioState->action = ACT_BUTT_SLIDE;
        }
        play_sound(SOUND_ACTION_BALLIN_BUMP, gMarioObject->header.gfx.cameraToObject);
    }
}

//Expand
void bumper_act_1(void) {
    o->oBumperScale = approach_f32(o->oBumperScale, 1.3f, 0.1f, 0.1f);
    cur_obj_scale(o->oBumperScale);
    if(o->oBumperScale == 1.3f) {
        o->oAction = 2;
    }
}

//Shrink
void bumper_act_2(void) {
    o->oBumperScale = approach_f32(o->oBumperScale, 1.0f, 0.1f, 0.1f);
    cur_obj_scale(o->oBumperScale);
    if(o->oBumperScale == 1.0f) {
        o->oAction = 0;
    }
}

void (*sBumperActions[])(void) = {
    bumper_act_0,
    bumper_act_1,
    bumper_act_2,
};

void bhv_bumper_init(void) {
    obj_set_hitbox(o, &sBumperHitBox);
    o->oAction = 0;
    o->oBumperScale = 1.0f;
    o->oBumperTimer = 0;
    o->oForwardVel = o->oBehParams2ndByte;
    o->oBumperSlideLength = 120;
}

void bhv_bumper_loop(void) {
    bumper_slide();
    cur_obj_call_action_function(sBumperActions);
}