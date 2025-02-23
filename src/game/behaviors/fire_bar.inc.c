struct ObjectHitbox sFireBarFireHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 100,
    /* damageOrCoinValue: */ 32,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void fire_spin_around_center () {
    s16 pitch = o->parentObj->oFaceAnglePitch;
    s16 yaw = o->parentObj->oFaceAngleYaw;

    f32 x, y, z;
    x = coss(pitch) * coss(yaw);
    z = coss(pitch) * sins(yaw);
    y = sins(pitch);

    o->oPosX = o->parentObj->oPosX + (o->oBehParams2ndByte * 400 * x);
    o->oPosY = o->parentObj->oPosY + (o->oBehParams2ndByte * 400 * y);
    o->oPosZ = o->parentObj->oPosZ + (o->oBehParams2ndByte * 400 * z);
}

void bhv_fire_bar_fire_init(void) {
    o->oTimer = 0;
    obj_set_hitbox(o, &sFireBarFireHitbox);
}

void bhv_fire_bar_fire_loop(void) {
    fire_spin_around_center();
}

void bhv_fire_bar_init(void) {
    for (u16 i = 0; i < o->oBehParams2ndByte; i++){
        spawn_object_relative_with_scale(i + 1, (i + 1) * 400, 0, 0, 2.0f, o, MODEL_FIRE_BAR, bhvFireBarFire);
    }
}

void bhv_fire_bar_loop(void) {
    o->oFaceAnglePitch += 0x300;
}