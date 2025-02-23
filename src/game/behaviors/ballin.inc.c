void ballin_explode(void){
    spawn_mist_particles_variable(0, 0, 80.f);
	spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, TINY_DIRT_PARTICLE_ANIM_STATE_BLUE);
	struct Object *explosion = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
	explosion->oGraphYOffset += 100.0f;
	explosion->oPosX = gMarioObject->oPosX;
	explosion->oPosY = gMarioObject->oPosY;
	explosion->oPosZ = gMarioObject->oPosZ;
    level_trigger_warp(gMarioState, WARP_OP_DEATH);
    set_mario_action(gMarioState, ACT_EXPLODING, 0);
	obj_mark_for_deletion(o);
}

void bhv_ballin_loop(void){
    o->oPosX = gMarioObject->oPosX;
    o->oPosY = gMarioObject->oPosY + 100;
    o->oPosZ = gMarioObject->oPosZ;
    if(gMarioState->action == ACT_GROUND_POUND || gMarioState->action == ACT_OIL_SLIP){
        o->oMoveAngleYaw += 7500;
    }
    else{
        o->oMoveAngleYaw = gMarioState->faceAngle[1];
    }
    o->oMoveAnglePitch += 100 * gMarioState->forwardVel;
    //Blow up if Mario Dies
    if(gMarioState->isDead || (gMarioState->health - 0x40 * gMarioState->hurtCounter) <= 0) {
        ballin_explode();
    }

    //Z + Start, fast reset (just kills Mario)
    if(gMarioState->controller->buttonPressed & START_BUTTON && gMarioState->controller->buttonDown & Z_TRIG) {
        if(gCanRestartLevel){
            ballin_explode();
        }
    }
}

void bhv_ballin_startup_init(void) {
    o->oGoombaScale = 0.0f;
}

void bhv_ballin_startup_loop(void) {
    if(o->oBehParams2ndByte){
        o->oMoveAngleYaw += 0x300;
    }else {
        o->oMoveAngleYaw -= 0x300;
    }
    o->oGoombaScale = approach_f32(o->oGoombaScale, 1.0f, 0.15f, 0.15f);
    cur_obj_scale(o->oGoombaScale);
}

void bhv_ballin_menu_loop(void) {
    f32 mag = gPlayer1Controller->stickMag;
    s32 targetPitchVel;
    s32 targetYawVel;

    if(mag > 0) {
        mag += 400;
        targetPitchVel = gPlayer1Controller->stickY  * 250;
        targetYawVel = gPlayer1Controller->stickX * 250;
        o->oAngleVelPitch = approach_s32(o->oAngleVelPitch, targetPitchVel, mag, mag);
        o->oAngleVelYaw = approach_s32(o->oAngleVelYaw, targetYawVel, mag, mag);
        o->oBallinMenuLastY = o->oAngleVelPitch;
        o->oBallinMenuLastX = o->oAngleVelYaw;
    }else {
        targetPitchVel = o->oBallinMenuLastY / 2;
        targetYawVel = o->oBallinMenuLastX / 2;
        o->oAngleVelPitch = approach_s32(o->oAngleVelPitch, targetPitchVel, 100, 100);
        o->oAngleVelYaw = approach_s32(o->oAngleVelYaw, targetYawVel, 100, 100);
    }

    o->oMoveAnglePitch += o->oAngleVelPitch;
    o->oMoveAngleYaw += o->oAngleVelYaw;
}

void bhv_ballin_menu_init(void) {
    cur_obj_scale(0.09375f);
    o->oAngleVelPitch = 0;
    o->oAngleVelYaw = 250;
    o->oBallinMenuLastY = o->oAngleVelPitch;
    o->oBallinMenuLastX = o->oAngleVelYaw;
}