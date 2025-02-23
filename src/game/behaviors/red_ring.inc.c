f32 red_ring_calc_mario_dist(void) {
    Vec3f marioDist;
    vec3_diff(marioDist, &o->oPosVec, gMarioState->pos);
    marioDist[1] += 80.0f;
    return vec3_dot(marioDist, &o->oGoldRingNormalVec);
}

f32 red_ring_check_in_range(f32 dist) {
    return (sqrtf(sqr(o->oPosX - gMarioObject->header.gfx.pos[0]) +
                    sqr(o->oPosY - gMarioObject->header.gfx.pos[1]) + 
                    sqr(o->oPosZ - gMarioObject->header.gfx.pos[2])) < dist);
}

void red_ring_check_collision() {
    f32 marioDistInFront = red_ring_calc_mario_dist();

    if (!red_ring_check_in_range(500.0f)){
        o->oGoldRingMarioDistInFront = marioDistInFront;
        return;
    }

    if (o->oGoldRingMarioDistInFront * marioDistInFront < 0.0f) {
        s16 angleDiff = o->oFaceAngleYaw - gMarioState->faceAngle[1];
        
        //Launch Mario in the direction of the ring
        gMarioState->forwardVel += o->oBehParams2ndByte;

        //If Mario is facing the same 180 degree rotation as the ring,
        if((-0x4000 < angleDiff) && (angleDiff < 0x4000)){
            gMarioState->faceAngle[1] = o->oFaceAngleYaw;
        //Otherwise launch in the opposite directon
        } else {
            gMarioState->faceAngle[1] = o->oFaceAngleYaw - 0x8000;
        }

        gMarioState->vel[1] = 0;
        play_sound(SOUND_ACTION_BALLIN_DASH, gMarioState->marioObj->header.gfx.cameraToObject);
    }

    o->oGoldRingMarioDistInFront = marioDistInFront;
}

void bhv_red_ring_init(void) {
    o->oGoldRingNormalX = sins(o->oFaceAngleYaw);
    o->oGoldRingNormalY = sins(o->oFaceAnglePitch);
    o->oGoldRingNormalZ = coss(o->oFaceAngleYaw);

    o->oGoldRingMarioDistInFront = red_ring_calc_mario_dist();
}

//Check for collision with mario
void bhv_red_ring_loop(void) {
    red_ring_check_collision();
    o->oFaceAngleRoll += 0x300;
}