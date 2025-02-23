enum tutorial_dialogue_state {
    STATE_NONE,
    STATE_TALKING,
    STATE_END
};

struct ObjectHitbox sTutorialHitBox = {
    /* interactType:      */ INTERACT_TEXT,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 50,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};



void tutorial_dialogue(void) {
    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if(cutscene_object_with_dialog(CUTSCENE_DIALOG, o, GET_BPARAM1(o->oBehParams))) {
                o->oAction = STATE_END;
            }
        }
    
}

void bhv_tutorial_base_init(void){
    spawn_object_relative_with_scale(0, 0, 450, 0, 3.0f, o, MODEL_TUTORIAL_EXCLAMATION, bhvTutorialExclamation);
    obj_set_hitbox(o, &sTutorialHitBox);
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    o->oAction = STATE_NONE;
}

void bhv_tutorial_base_loop(void){
    switch(o->oAction){
        case STATE_NONE:
            if(o->oInteractStatus == INT_STATUS_INTERACTED) {
                o->oAction = STATE_TALKING;
            }
            break;
        case STATE_TALKING:
            tutorial_dialogue();
            break;
        case STATE_END:
            o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oInteractStatus = INT_STATUS_NONE;
            set_mario_npc_dialog(MARIO_DIALOG_STOP);
            o->oAction = STATE_NONE;
            break;
    }
    
}

void bhv_tutorial_exclamation_loop(void){
    o->oFaceAngleYaw += 0x400;
    o->oPosY += 2 * sins(o->oFaceAngleYaw);
}