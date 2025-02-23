#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "audio/external.h"
#include "behavior_data.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "file_select.h"
#include "game/area.h"
#include "game/game_init.h"
#include "game/ingame_menu.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/print.h"
#include "game/save_file.h"
#include "game/segment2.h"
#include "game/segment7.h"
#include "game/spawn_object.h"
#include "game/rumble_init.h"
#include "sm64.h"
#include "text_strings.h"
#include "game/puppyprint.h"
#include "lvl_select.h"

#include <ultra64.h>

unsigned char slideStar[] = { GLYPH_STAR, GLYPH_SPACE };

static struct Object *sSlideModels[MAX_SLIDES];

static enum LevelNum sValidSlides[MAX_SLIDES] = {
    LEVEL_WMOTR,
    LEVEL_BITDW,
    LEVEL_BITFS,
    LEVEL_BITS,
    LEVEL_PSS,
    LEVEL_SA,
    LEVEL_VCUTM,
    LEVEL_ENDING
};

static char sLevelNames[MAX_SLIDES][25] = {
    "TUTORIAL",
    "THE BIG BOUNCE",
    "MARIO KART",
    "ICY ROADS AHEAD",
    "RETRO",
    "FIREBALL",
    "PINBALL",
    "???"
};

static s16 sSelectedSlide = 0;
static s16 sAvailableSlides;
static s16 sGap;
static s16 sDistanceFromCenter = 400;
static s16 sMenuRotation;
static s16 sTargetRotation;
static s16 sMenuSpeed;
static s16 sBobAngle;
static enum Lvl_Select_Menu_State sMenuState;
static u16 sBestTime[3];
static u8 sRank;

static s16 sLevelSelectMenuTimer;
static enum Delete_Menu_Selected_Option sDeleteMenuSelected;



s32 getCourseIndexFromValidSlide(enum LevelNum level) {
    switch(level){
        case LEVEL_BOB:
            return COURSE_NUM_TO_INDEX(COURSE_BOB);
            break;
        case LEVEL_WMOTR:
            return COURSE_NUM_TO_INDEX(COURSE_WMOTR);
            break;
        case LEVEL_BITDW:
            return COURSE_NUM_TO_INDEX(COURSE_BITDW);
            break;
        case LEVEL_BITFS:
            return COURSE_NUM_TO_INDEX(COURSE_BITFS);
            break;
        case LEVEL_BITS:
            return COURSE_NUM_TO_INDEX(COURSE_BITS);
            break;
        case LEVEL_PSS:
            return COURSE_NUM_TO_INDEX(COURSE_PSS);
            break;
        case LEVEL_SA:
            return COURSE_NUM_TO_INDEX(COURSE_SA);
            break;
        case LEVEL_VCUTM:
            return COURSE_NUM_TO_INDEX(COURSE_VCUTM);
            break;
        case LEVEL_ENDING:
            return COURSE_NUM_TO_INDEX(COURSE_CAKE_END);
            break;
        default:
            return COURSE_NONE;
            break;
    }
}

void getSegmentedSlideTime(u16 *segmentedSlideTime, u16 slideTime) {
    segmentedSlideTime[0] = slideTime / 1800;
    segmentedSlideTime[1] = (slideTime - (segmentedSlideTime[0] * 1800)) / 30;
    segmentedSlideTime[2] = (slideTime - (segmentedSlideTime[0] * 1800) - (segmentedSlideTime[1] * 30)) * 33;
}

//Updates displayed best time, and rank
void updateSlideBestTime(){
    getSegmentedSlideTime(sBestTime, save_file_get_time_from_index(getCourseIndexFromValidSlide(sValidSlides[sSelectedSlide])));
    enum SlideRank currRank = save_file_get_rank_from_index(getCourseIndexFromValidSlide(sValidSlides[sSelectedSlide]));
    switch(currRank){
        case RANK_S:
            sRank = 'S';
            break;
        case RANK_A:
            sRank = 'A';
            break;
        case RANK_B:
            sRank = 'B';
            break;
        case RANK_C:
            sRank = 'C';
            break;
        case RANK_F:
            sRank = 'F';
            break;
        default:
            sRank = '-';
            break;
    }
}

void orbit_center(struct Object *centerObject, struct Object *orbitObject, s16 offset) {
    orbitObject->oPosX = centerObject->oPosX + (sDistanceFromCenter * coss(centerObject->oFaceAngleYaw - offset));
    orbitObject->oPosZ = centerObject->oPosZ + (sDistanceFromCenter * sins(centerObject->oFaceAngleYaw - offset));
}

//Handle a prompt asking if the player really wants to erase their save
void ask_erase(){
    if ((gPlayer1Controller->buttonDown & R_JPAD
        || gPlayer1Controller->rawStickX > 60)
        && sDeleteMenuSelected == DELETE_YES) {

        sDeleteMenuSelected = DELETE_NO;
        play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
    }
    else if ((gPlayer1Controller->buttonDown & L_JPAD
        || gPlayer1Controller->rawStickX < -60)
        && sDeleteMenuSelected == DELETE_NO) {

        sDeleteMenuSelected = DELETE_YES;
        play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
    }
    else if (gPlayer1Controller->buttonPressed & A_BUTTON || gPlayer1Controller->buttonPressed & START_BUTTON){
        if(sDeleteMenuSelected == DELETE_YES){
            sLevelSelectMenuTimer = 0;
            play_sound(SOUND_MARIO_WAAAOOOW, gGlobalSoundSource);
            play_transition(WARP_TRANSITION_FADE_INTO_BOWSER, 30, 0x00, 0x00, 0x00);
            sMenuState = STATE_ERASED;
        }else{
            sMenuState = STATE_DEFAULT;
        }
    } else if (gPlayer1Controller->buttonPressed & B_BUTTON) {
        sMenuState = STATE_DEFAULT;
    }
}

//Erases the save file
void delete_save(){
    save_file_erase(0);
    
    //Reset last selected slide and send back to splash screen
    gLastSelectedSlideIndex = 0;
}

void printMenuText() {
    char textBytes[64];

    //SIDE PANEL
    prepare_blank_box();
    render_blank_box_rounded((SCREEN_WIDTH / 3) * 2, (SCREEN_HEIGHT / 3) - 15, SCREEN_WIDTH, SCREEN_HEIGHT, 0x79, 0x8E, 0xBA, 200);
    finish_blank_box();

    //BOTTOM PANEL
    prepare_blank_box();
    render_blank_box_rounded(0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255);
    finish_blank_box();

    //SELECT A SLIDE
    print_small_text(SCREEN_WIDTH / 3, 200, "SELECT A SLIDE", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);

    //SLIDE NAME
    print_set_envcolour(0x00, 0x00, 0x00, 0xFF);
    print_small_text((SCREEN_WIDTH / 6) * 5, (SCREEN_HEIGHT / 6) * 2, sLevelNames[sSelectedSlide], PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_PLAIN);
    
    //BEST TIME
    print_small_text((SCREEN_WIDTH / 6) * 5, ((SCREEN_HEIGHT / 6) * 3), "Best Time", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);
    //If no saved score, print -- instead
    if(sBestTime[0] + sBestTime[1] + sBestTime[2] == 0){
        print_small_text((SCREEN_WIDTH / 6) * 5, ((SCREEN_HEIGHT / 6) * 3) + 15, "--'--\"--", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);
    }else{
        sprintf(textBytes, "%.2d'%.2d\"%.2d", sBestTime[0], sBestTime[1], sBestTime[2]);
        print_small_text((SCREEN_WIDTH / 6) * 5, ((SCREEN_HEIGHT / 6) * 3) + 15, textBytes, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);
    }

    //SHOW STAR
    if(save_file_get_star_flags(gCurrSaveFileNum - 1, getCourseIndexFromValidSlide(sValidSlides[sSelectedSlide]))){
        print_text((SCREEN_WIDTH / 6) * 5 - 37, 78, "^");
    }

    //BEST RANK
    sprintf(textBytes, "Rank: %c", sRank);
    print_small_text((SCREEN_WIDTH / 6) * 5, ((SCREEN_HEIGHT / 6) * 3) + 30, textBytes, PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);

    //CONTROL INFO
    print_small_text(SCREEN_WIDTH / 3, 215, "Press A to play", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_OUTLINE);
    print_small_text(SCREEN_WIDTH - 5, SCREEN_HEIGHT - 15, "Z + Start: Erase Save", PRINT_TEXT_ALIGN_RIGHT, PRINT_ALL, FONT_VANILLA);

    //Show the prompt for erasing the file
    if(sMenuState == STATE_ASK_ERASE) {
        //BACK PANEL
        prepare_blank_box();
        render_blank_box_rounded(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, (SCREEN_WIDTH / 4) * 3, (SCREEN_HEIGHT / 2) + 25, 0, 0, 0, 255);
        finish_blank_box();
        //PROMPT
        print_small_text(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 50, "DELETE SAVE", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_PLAIN);
        print_small_text(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 35, "Are you sure?", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_PLAIN);

        //YES
        if(sDeleteMenuSelected == DELETE_YES) {
            print_set_envcolour(0xFF, 0x33, 0x00, 0xFF);
        }
        print_small_text((SCREEN_WIDTH / 2) - 25, SCREEN_HEIGHT / 2, "YES", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_PLAIN);

        //NO
        if(sDeleteMenuSelected == DELETE_NO) {
            print_set_envcolour(0xFF, 0x33, 0x00, 0xFF);
        }
        print_small_text((SCREEN_WIDTH / 2) + 25, SCREEN_HEIGHT / 2, "NO", PRINT_TEXT_ALIGN_CENTER, PRINT_ALL, FONT_PLAIN);
    }
}

s32 lvl_select_update_and_select_level(UNUSED s32 arg, UNUSED s32 unused) {
    area_update_objects();

    switch(sMenuState) {
        case STATE_DEFAULT:
            if(gPlayer1Controller->buttonPressed & A_BUTTON) {
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                gLastSelectedSlideIndex = sSelectedSlide;
                return sValidSlides[sSelectedSlide];
            } else if (gPlayer1Controller->buttonPressed & START_BUTTON && gPlayer1Controller->buttonDown & Z_TRIG){
                play_sound(SOUND_MENU_HAND_APPEAR, gGlobalSoundSource);
                sDeleteMenuSelected = DELETE_NO; //Default to no
                sMenuState = STATE_ASK_ERASE;
            }
            break;
        case STATE_MOVING:
            break;
        case STATE_ASK_ERASE:
            ask_erase();
            break; 
        case STATE_ERASED:
            if(++sLevelSelectMenuTimer > 30) {
                delete_save();
                return LEVEL_RESTART_GAME;
            }
            break;
    }

    return 0;
}

void beh_level_selector_init(void) {
    if(save_file_exists(0)){
        //Ending appear if collected all stars
        if(save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 6){
            sAvailableSlides = MAX_SLIDES;
        }
        else{
            sAvailableSlides = MAX_SLIDES - 1;
        }
    }
    //Lock to tutorial only if file is new
    else{
        sAvailableSlides = 1;
    }
    
    sMenuState = STATE_DEFAULT;
    
    s32 slideModelIDs[MAX_SLIDES] = {
        MODEL_MINI_TUTORIAL,
        MODEL_MINI_BIG_BOUNCE,
        MODEL_MINI_MARIOKART,
        MODEL_MINI_SNOW,
        MODEL_MINI_RETRO,
        MODEL_MINI_LAVA,
        MODEL_MINI_PINBALL,
        MODEL_MINI_ETHAN
    };
    sDistanceFromCenter = 400;
    sGap = DEGREES(360) / sAvailableSlides;
    sMenuSpeed = sGap / 16;
    sMenuRotation = DEGREES(90);
    sTargetRotation = sMenuRotation;
    gCurrentObject->oFaceAngleYaw = sMenuRotation;
    sBobAngle = 0;
    sSelectedSlide = gLastSelectedSlideIndex;
    sRank = '-';
    for (s16 i = 0; i < sAvailableSlides; i++){
        //-sGap so it loads counter-clockwise
        sSlideModels[i] = spawn_object_relative_with_scale(0, sDistanceFromCenter * coss(-sGap * i), -20, sDistanceFromCenter * sins(-sGap * i),
                            1.5f, gCurrentObject, slideModelIDs[i], bhvSlideSelectorModel);
        orbit_center(gCurrentObject, sSlideModels[i], (i - gLastSelectedSlideIndex) * sGap);
    }
    updateSlideBestTime();
}

void beh_level_selector_loop(void) {
    //Bob selected slide up and down
    sSlideModels[sSelectedSlide]->oPosY += sins(sBobAngle);
    sBobAngle += 0x300;

    if(sMenuState == STATE_DEFAULT){
        if ((gPlayer1Controller->buttonDown & R_JPAD
            || gPlayer1Controller->rawStickX > 60)
            && sAvailableSlides > 1) {
            sMenuState = STATE_MOVING;
            sTargetRotation = sMenuRotation + sGap;
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            sSlideModels[sSelectedSlide]->oPosY = o->oPosY - 20;

            if(sSelectedSlide < sAvailableSlides - 1){
                sSelectedSlide++;
            }else{
                //"Overflow" to beginning of list
                sSelectedSlide = 0;
            }
            
            updateSlideBestTime();
        }
        else if ((gPlayer1Controller->buttonDown & L_JPAD
            || gPlayer1Controller->rawStickX < -60)
            && sAvailableSlides > 1) {
            sMenuState = STATE_MOVING;
            sTargetRotation = sMenuRotation - sGap;
            play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
            sSlideModels[sSelectedSlide]->oPosY = o->oPosY - 20;

            if(sSelectedSlide > 0){
                sSelectedSlide--;
            }else{
                //"Underflow" to end of list
                sSelectedSlide = sAvailableSlides - 1;
            }
            
            updateSlideBestTime();
        }
    }
    else if (sMenuState == STATE_MOVING){
        //Reset bob
        sBobAngle = 0;
        sMenuRotation = approach_angle(sMenuRotation, sTargetRotation, sMenuSpeed);
        gCurrentObject->oFaceAngleYaw = sMenuRotation;
        for(s16 i = 0; i < sAvailableSlides; i++){
            orbit_center(gCurrentObject, sSlideModels[i], (i - gLastSelectedSlideIndex) * sGap);
        }
        if(sMenuRotation == sTargetRotation){
            sMenuState = STATE_DEFAULT;
        }
    }
}

void bhv_slide_selector_model_loop(void) {
    gCurrentObject->oFaceAngleYaw += 0xAF;
}

Gfx *geo_lvl_select_strings_and_glyphs(s32 callContext, UNUSED struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        printMenuText();
    }
    return NULL;
}