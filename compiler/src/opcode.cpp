#include <map>
#include <ostream>
#include <ranges>
#include <b2b/opcode.hpp>

static const std::map<b2b::OpcodeE, b2b::OpcodeRef> INDEX
{
    {
        b2b::undefined,
        { b2b::undefined, false, "undefined", {} },
    },

    {
        b2b::coreExample_exampleOpcode,
        { b2b::coreExample_exampleOpcode, false, "coreExample_exampleOpcode", {} },
    },
    {
        b2b::coreExample_exampleWithInlineImage,
        { b2b::coreExample_exampleWithInlineImage, false, "coreExample_exampleWithInlineImage", {} },
    },

    {
        b2b::motion_movesteps,
        { b2b::motion_movesteps, false, "motion_movesteps", { "" } },
    },
    {
        b2b::motion_turnright,
        { b2b::motion_turnright, false, "motion_turnright", { "" } },
    },
    {
        b2b::motion_turnleft,
        { b2b::motion_turnleft, false, "motion_turnleft", { "" } },
    },
    {
        b2b::motion_goto,
        { b2b::motion_goto, false, "motion_goto", { "" } },
    },
    {
        b2b::motion_gotoxy,
        { b2b::motion_gotoxy, false, "motion_gotoxy", { "", "" } },
    },
    {
        b2b::motion_glideto,
        { b2b::motion_glideto, false, "motion_glideto", { "", "" } },
    },
    {
        b2b::motion_glidesecstoxy,
        { b2b::motion_glidesecstoxy, false, "motion_glidesecstoxy", { "", "", "" } },
    },
    {
        b2b::motion_pointindirection,
        { b2b::motion_pointindirection, false, "motion_pointindirection", { "" } },
    },
    {
        b2b::motion_pointtowards,
        { b2b::motion_pointtowards, false, "motion_pointtowards", { "" } },
    },
    {
        b2b::motion_changexby,
        { b2b::motion_changexby, false, "motion_changexby", { "" } },
    },
    {
        b2b::motion_setx,
        { b2b::motion_setx, false, "motion_setx", { "" } },
    },
    {
        b2b::motion_changeyby,
        { b2b::motion_changeyby, false, "motion_changeyby", { "" } },
    },
    {
        b2b::motion_sety,
        { b2b::motion_sety, false, "motion_sety", { "" } },
    },
    {
        b2b::motion_ifonedgebounce,
        { b2b::motion_ifonedgebounce, false, "motion_ifonedgebounce", {} },
    },
    {
        b2b::motion_setrotationstyle,
        { b2b::motion_setrotationstyle, false, "motion_setrotationstyle", { "" } },
    },
    {
        b2b::motion_xposition,
        { b2b::motion_xposition, false, "motion_xposition", {} },
    },
    {
        b2b::motion_yposition,
        { b2b::motion_yposition, false, "motion_yposition", {} },
    },
    {
        b2b::motion_direction,
        { b2b::motion_direction, false, "motion_direction", {} },
    },
    {
        b2b::motion_scroll_right,
        { b2b::motion_scroll_right, false, "motion_scroll_right", { "" } },
    },
    {
        b2b::motion_scroll_up,
        { b2b::motion_scroll_up, false, "motion_scroll_up", { "" } },
    },
    {
        b2b::motion_align_scene,
        { b2b::motion_align_scene, false, "motion_align_scene", { "" } },
    },
    {
        b2b::motion_xscroll,
        { b2b::motion_xscroll, false, "motion_xscroll", {} },
    },
    {
        b2b::motion_yscroll,
        { b2b::motion_yscroll, false, "motion_yscroll", {} },
    },

    {
        b2b::looks_sayforsecs,
        { b2b::looks_sayforsecs, false, "looks_sayforsecs", { "", "" } },
    },
    {
        b2b::looks_say,
        { b2b::looks_say, false, "looks_say", { "" } },
    },
    {
        b2b::looks_thinkforsecs,
        { b2b::looks_thinkforsecs, false, "looks_thinkforsecs", { "", "" } },
    },
    {
        b2b::looks_think,
        { b2b::looks_think, false, "looks_think", { "" } },
    },
    {
        b2b::looks_switchcostumeto,
        { b2b::looks_switchcostumeto, false, "looks_switchcostumeto", { "" } },
    },
    {
        b2b::looks_nextcostume,
        { b2b::looks_nextcostume, false, "looks_nextcostume", {} },
    },
    {
        b2b::looks_switchbackdropto,
        { b2b::looks_switchbackdropto, false, "looks_switchbackdropto", { "" } },
    },
    {
        b2b::looks_switchbackdroptoandwait,
        { b2b::looks_switchbackdroptoandwait, false, "looks_switchbackdroptoandwait", { "" } },
    },
    {
        b2b::looks_nextbackdrop,
        { b2b::looks_nextbackdrop, false, "looks_nextbackdrop", {} },
    },
    {
        b2b::looks_changesizeby,
        { b2b::looks_changesizeby, false, "looks_changesizeby", { "" } },
    },
    {
        b2b::looks_setsizeto,
        { b2b::looks_setsizeto, false, "looks_setsizeto", { "" } },
    },
    {
        b2b::looks_changeeffectby,
        { b2b::looks_changeeffectby, false, "looks_changeeffectby", { "", "" } },
    },
    {
        b2b::looks_seteffectto,
        { b2b::looks_seteffectto, false, "looks_seteffectto", { "", "" } },
    },
    {
        b2b::looks_cleargraphiceffects,
        { b2b::looks_cleargraphiceffects, false, "looks_cleargraphiceffects", {} },
    },
    {
        b2b::looks_show,
        { b2b::looks_show, false, "looks_show", {} },
    },
    {
        b2b::looks_hide,
        { b2b::looks_hide, false, "looks_hide", {} },
    },
    {
        b2b::looks_gotofrontback,
        { b2b::looks_gotofrontback, false, "looks_gotofrontback", { "" } },
    },
    {
        b2b::looks_goforwardbackwardlayers,
        { b2b::looks_goforwardbackwardlayers, false, "looks_goforwardbackwardlayers", { "", "" } },
    },
    {
        b2b::looks_costumenumbername,
        { b2b::looks_costumenumbername, false, "looks_costumenumbername", { "" } },
    },
    {
        b2b::looks_backdropnumbername,
        { b2b::looks_backdropnumbername, false, "looks_backdropnumbername", { "" } },
    },
    {
        b2b::looks_size,
        { b2b::looks_size, false, "looks_size", {} },
    },
    {
        b2b::looks_hideallsprites,
        { b2b::looks_hideallsprites, false, "looks_hideallsprites", {} },
    },
    {
        b2b::looks_setstretchto,
        { b2b::looks_setstretchto, false, "looks_setstretchto", { "" } },
    },
    {
        b2b::looks_changestretchby,
        { b2b::looks_changestretchby, false, "looks_changestretchby", { "" } },
    },

    {
        b2b::sound_playuntildone,
        { b2b::sound_playuntildone, false, "sound_playuntildone", { "" } },
    },
    {
        b2b::sound_play,
        { b2b::sound_play, false, "sound_play", { "" } },
    },
    {
        b2b::sound_stopallsounds,
        { b2b::sound_stopallsounds, false, "sound_stopallsounds", {} },
    },
    {
        b2b::sound_changeeffectby,
        { b2b::sound_changeeffectby, false, "sound_changeeffectby", { "", "" } },
    },
    {
        b2b::sound_seteffectto,
        { b2b::sound_seteffectto, false, "sound_seteffectto", { "", "" } },
    },
    {
        b2b::sound_cleareffects,
        { b2b::sound_cleareffects, false, "sound_cleareffects", {} },
    },
    {
        b2b::sound_changevolumeby,
        { b2b::sound_changevolumeby, false, "sound_changevolumeby", { "" } },
    },
    {
        b2b::sound_setvolumeto,
        { b2b::sound_setvolumeto, false, "sound_setvolumeto", { "" } },
    },
    {
        b2b::sound_volume,
        { b2b::sound_volume, false, "sound_volume", {} },
    },

    {
        b2b::event_whenflagclicked,
        { b2b::event_whenflagclicked, true, "event_whenflagclicked", {} },
    },
    {
        b2b::event_whenkeypressed,
        { b2b::event_whenkeypressed, true, "event_whenkeypressed", { "" } },
    },
    {
        b2b::event_whenthisspriteclicked,
        { b2b::event_whenthisspriteclicked, true, "event_whenthisspriteclicked", {} },
    },
    {
        b2b::event_whenstageclicked,
        { b2b::event_whenstageclicked, true, "event_whenstageclicked", {} },
    },
    {
        b2b::event_whenbackdropswitchesto,
        { b2b::event_whenbackdropswitchesto, true, "event_whenbackdropswitchesto", { "" } },
    },
    {
        b2b::event_whengreaterthan,
        { b2b::event_whengreaterthan, true, "event_whengreaterthan", { "", "" } },
    },
    {
        b2b::event_whenbroadcastreceived,
        { b2b::event_whenbroadcastreceived, true, "event_whenbroadcastreceived", { "" } },
    },
    {
        b2b::event_broadcast,
        { b2b::event_broadcast, false, "event_broadcast", { "" } },
    },
    {
        b2b::event_broadcastandwait,
        { b2b::event_broadcastandwait, false, "event_broadcastandwait", { "" } },
    },
    {
        b2b::event_whentouchingobject,
        { b2b::event_whentouchingobject, true, "event_whentouchingobject", { "" } },
    },

    {
        b2b::control_wait,
        { b2b::control_wait, false, "control_wait", { "" } },
    },
    {
        b2b::control_repeat,
        { b2b::control_repeat, false, "control_repeat", { "TIMES", "SUBSTACK" } },
    },
    {
        b2b::control_forever,
        { b2b::control_forever, false, "control_forever", { "" } },
    },
    {
        b2b::control_if,
        { b2b::control_if, false, "control_if", { "", "" } },
    },
    {
        b2b::control_if_else,
        { b2b::control_if_else, false, "control_if_else", { "", "", "" } },
    },
    {
        b2b::control_wait_until,
        { b2b::control_wait_until, false, "control_wait_until", { "" } },
    },
    {
        b2b::control_repeat_until,
        { b2b::control_repeat_until, false, "control_repeat_until", { "", "" } },
    },
    {
        b2b::control_stop,
        { b2b::control_stop, false, "control_stop", { "" } },
    },
    {
        b2b::control_start_as_clone,
        { b2b::control_start_as_clone, true, "control_start_as_clone", {} },
    },
    {
        b2b::control_create_clone_of,
        { b2b::control_create_clone_of, false, "control_create_clone_of", { "CLONE_OPTION" } },
    },
    {
        b2b::control_delete_this_clone,
        { b2b::control_delete_this_clone, false, "control_delete_this_clone", {} },
    },
    {
        b2b::control_for_each,
        { b2b::control_for_each, false, "control_for_each", { "", "", "" } },
    },
    {
        b2b::control_while,
        { b2b::control_while, false, "control_while", { "", "" } },
    },
    {
        b2b::control_get_counter,
        { b2b::control_get_counter, false, "control_get_counter", {} },
    },
    {
        b2b::control_incr_counter,
        { b2b::control_incr_counter, false, "control_incr_counter", {} },
    },
    {
        b2b::control_clear_counter,
        { b2b::control_clear_counter, false, "control_clear_counter", {} },
    },
    {
        b2b::control_all_at_once,
        { b2b::control_all_at_once, false, "control_all_at_once", { "" } },
    },

    {
        b2b::sensing_touchingobject,
        { b2b::sensing_touchingobject, false, "sensing_touchingobject", {} },
    },
    {
        b2b::sensing_touchingcolor,
        { b2b::sensing_touchingcolor, false, "sensing_touchingcolor", {} },
    },
    {
        b2b::sensing_coloristouchingcolor,
        { b2b::sensing_coloristouchingcolor, false, "sensing_coloristouchingcolor", {} },
    },
    {
        b2b::sensing_distanceto,
        { b2b::sensing_distanceto, false, "sensing_distanceto", {} },
    },
    {
        b2b::sensing_askandwait,
        { b2b::sensing_askandwait, false, "sensing_askandwait", {} },
    },
    {
        b2b::sensing_answer,
        { b2b::sensing_answer, false, "sensing_answer", {} },
    },
    {
        b2b::sensing_keypressed,
        { b2b::sensing_keypressed, false, "sensing_keypressed", {} },
    },
    {
        b2b::sensing_mousedown,
        { b2b::sensing_mousedown, false, "sensing_mousedown", {} },
    },
    {
        b2b::sensing_mousex,
        { b2b::sensing_mousex, false, "sensing_mousex", {} },
    },
    {
        b2b::sensing_mousey,
        { b2b::sensing_mousey, false, "sensing_mousey", {} },
    },
    {
        b2b::sensing_setdragmode,
        { b2b::sensing_setdragmode, false, "sensing_setdragmode", {} },
    },
    {
        b2b::sensing_loudness,
        { b2b::sensing_loudness, false, "sensing_loudness", {} },
    },
    {
        b2b::sensing_timer,
        { b2b::sensing_timer, false, "sensing_timer", {} },
    },
    {
        b2b::sensing_resettimer,
        { b2b::sensing_resettimer, false, "sensing_resettimer", {} },
    },
    {
        b2b::sensing_of,
        { b2b::sensing_of, false, "sensing_of", {} },
    },
    {
        b2b::sensing_current,
        { b2b::sensing_current, false, "sensing_current", {} },
    },
    {
        b2b::sensing_dayssince2000,
        { b2b::sensing_dayssince2000, false, "sensing_dayssince2000", {} },
    },
    {
        b2b::sensing_username,
        { b2b::sensing_username, false, "sensing_username", {} },
    },
    {
        b2b::sensing_loud,
        { b2b::sensing_loud, false, "sensing_loud", {} },
    },
    {
        b2b::sensing_userid,
        { b2b::sensing_userid, false, "sensing_userid", {} },
    },

    {
        b2b::operator_add,
        { b2b::operator_add, false, "operator_add", {} },
    },
    {
        b2b::operator_subtract,
        { b2b::operator_subtract, false, "operator_subtract", {} },
    },
    {
        b2b::operator_multiply,
        { b2b::operator_multiply, false, "operator_multiply", {} },
    },
    {
        b2b::operator_divide,
        { b2b::operator_divide, false, "operator_divide", {} },
    },
    {
        b2b::operator_random,
        { b2b::operator_random, false, "operator_random", {} },
    },
    {
        b2b::operator_gt,
        { b2b::operator_gt, false, "operator_gt", {} },
    },
    {
        b2b::operator_lt,
        { b2b::operator_lt, false, "operator_lt", {} },
    },
    {
        b2b::operator_equals,
        { b2b::operator_equals, false, "operator_equals", {} },
    },
    {
        b2b::operator_and,
        { b2b::operator_and, false, "operator_and", {} },
    },
    {
        b2b::operator_or,
        { b2b::operator_or, false, "operator_or", {} },
    },
    {
        b2b::operator_not,
        { b2b::operator_not, false, "operator_not", {} },
    },
    {
        b2b::operator_join,
        { b2b::operator_join, false, "operator_join", {} },
    },
    {
        b2b::operator_letter_of,
        { b2b::operator_letter_of, false, "operator_letter_of", {} },
    },
    {
        b2b::operator_length,
        { b2b::operator_length, false, "operator_length", {} },
    },
    {
        b2b::operator_contains,
        { b2b::operator_contains, false, "operator_contains", {} },
    },
    {
        b2b::operator_mod,
        { b2b::operator_mod, false, "operator_mod", {} },
    },
    {
        b2b::operator_round,
        { b2b::operator_round, false, "operator_round", {} },
    },
    {
        b2b::operator_mathop,
        { b2b::operator_mathop, false, "operator_mathop", {} },
    },

    {
        b2b::data_variable,
        { b2b::data_variable, false, "data_variable", {} },
    },
    {
        b2b::data_setvariableto,
        { b2b::data_setvariableto, false, "data_setvariableto", {} },
    },
    {
        b2b::data_changevariableby,
        { b2b::data_changevariableby, false, "data_changevariableby", {} },
    },
    {
        b2b::data_showvariable,
        { b2b::data_showvariable, false, "data_showvariable", {} },
    },
    {
        b2b::data_hidevariable,
        { b2b::data_hidevariable, false, "data_hidevariable", {} },
    },

    {
        b2b::data_listcontents,
        { b2b::data_listcontents, false, "data_listcontents", {} },
    },
    {
        b2b::data_addtolist,
        { b2b::data_addtolist, false, "data_addtolist", {} },
    },
    {
        b2b::data_deleteoflist,
        { b2b::data_deleteoflist, false, "data_deleteoflist", {} },
    },
    {
        b2b::data_deletealloflist,
        { b2b::data_deletealloflist, false, "data_deletealloflist", {} },
    },
    {
        b2b::data_insertatlist,
        { b2b::data_insertatlist, false, "data_insertatlist", {} },
    },
    {
        b2b::data_replaceitemoflist,
        { b2b::data_replaceitemoflist, false, "data_replaceitemoflist", {} },
    },
    {
        b2b::data_itemoflist,
        { b2b::data_itemoflist, false, "data_itemoflist", {} },
    },
    {
        b2b::data_itemnumoflist,
        { b2b::data_itemnumoflist, false, "data_itemnumoflist", {} },
    },
    {
        b2b::data_lengthoflist,
        { b2b::data_lengthoflist, false, "data_lengthoflist", {} },
    },
    {
        b2b::data_listcontainsitem,
        { b2b::data_listcontainsitem, false, "data_listcontainsitem", {} },
    },
    {
        b2b::data_showlist,
        { b2b::data_showlist, false, "data_showlist", {} },
    },
    {
        b2b::data_hidelist,
        { b2b::data_hidelist, false, "data_hidelist", {} },
    },

    {
        b2b::procedures_definition,
        { b2b::procedures_definition, true, "procedures_definition", {} },
    },
    {
        b2b::procedures_call,
        { b2b::procedures_call, false, "procedures_call", {} },
    },
    {
        b2b::procedures_declaration,
        { b2b::procedures_declaration, false, "procedures_declaration", {} },
    },

    {
        b2b::argument_reporter_string_number,
        { b2b::argument_reporter_string_number, false, "argument_reporter_string_number", {} },
    },
    {
        b2b::argument_reporter_boolean,
        { b2b::argument_reporter_boolean, false, "argument_reporter_boolean", {} },
    },

    {
        b2b::music_playDrumForBeats,
        { b2b::music_playDrumForBeats, false, "music_playDrumForBeats", {} },
    },
    {
        b2b::music_restForBeats,
        { b2b::music_restForBeats, false, "music_restForBeats", {} },
    },
    {
        b2b::music_playNoteForBeats,
        { b2b::music_playNoteForBeats, false, "music_playNoteForBeats", {} },
    },
    {
        b2b::music_setInstrument,
        { b2b::music_setInstrument, false, "music_setInstrument", {} },
    },
    {
        b2b::music_setTempo,
        { b2b::music_setTempo, false, "music_setTempo", {} },
    },
    {
        b2b::music_changeTempo,
        { b2b::music_changeTempo, false, "music_changeTempo", {} },
    },
    {
        b2b::music_getTempo,
        { b2b::music_getTempo, false, "music_getTempo", {} },
    },
    {
        b2b::music_midiPlayDrumForBeats,
        { b2b::music_midiPlayDrumForBeats, false, "music_midiPlayDrumForBeats", {} },
    },
    {
        b2b::music_midiSetInstrument,
        { b2b::music_midiSetInstrument, false, "music_midiSetInstrument", {} },
    },

    {
        b2b::pen_clear,
        { b2b::pen_clear, false, "pen_clear", {} },
    },
    {
        b2b::pen_stamp,
        { b2b::pen_stamp, false, "pen_stamp", {} },
    },
    {
        b2b::pen_penDown,
        { b2b::pen_penDown, false, "pen_penDown", {} },
    },
    {
        b2b::pen_penUp,
        { b2b::pen_penUp, false, "pen_penUp", {} },
    },
    {
        b2b::pen_setPenColorToColor,
        { b2b::pen_setPenColorToColor, false, "pen_setPenColorToColor", {} },
    },
    {
        b2b::pen_changePenColorParamBy,
        { b2b::pen_changePenColorParamBy, false, "pen_changePenColorParamBy", {} },
    },
    {
        b2b::pen_setPenColorParamTo,
        { b2b::pen_setPenColorParamTo, false, "pen_setPenColorParamTo", {} },
    },
    {
        b2b::pen_changePenSizeBy,
        { b2b::pen_changePenSizeBy, false, "pen_changePenSizeBy", {} },
    },
    {
        b2b::pen_setPenSizeTo,
        { b2b::pen_setPenSizeTo, false, "pen_setPenSizeTo", {} },
    },
    {
        b2b::pen_setPenHueToNumber,
        { b2b::pen_setPenHueToNumber, false, "pen_setPenHueToNumber", {} },
    },
    {
        b2b::pen_changePenHueBy,
        { b2b::pen_changePenHueBy, false, "pen_changePenHueBy", {} },
    },
    {
        b2b::pen_setPenShadeToNumber,
        { b2b::pen_setPenShadeToNumber, false, "pen_setPenShadeToNumber", {} },
    },
    {
        b2b::pen_changePenShadeBy,
        { b2b::pen_changePenShadeBy, false, "pen_changePenShadeBy", {} },
    },

    {
        b2b::videoSensing_whenMotionGreaterThan,
        { b2b::videoSensing_whenMotionGreaterThan, true, "videoSensing_whenMotionGreaterThan", {} },
    },
    {
        b2b::videoSensing_videoOn,
        { b2b::videoSensing_videoOn, false, "videoSensing_videoOn", {} },
    },
    {
        b2b::videoSensing_videoToggle,
        { b2b::videoSensing_videoToggle, false, "videoSensing_videoToggle", {} },
    },
    {
        b2b::videoSensing_setVideoTransparency,
        { b2b::videoSensing_setVideoTransparency, false, "videoSensing_setVideoTransparency", {} },
    },

    {
        b2b::text2speech_speakAndWait,
        { b2b::text2speech_speakAndWait, false, "text2speech_speakAndWait", {} },
    },
    {
        b2b::text2speech_setVoice,
        { b2b::text2speech_setVoice, false, "text2speech_setVoice", {} },
    },
    {
        b2b::text2speech_setLanguage,
        { b2b::text2speech_setLanguage, false, "text2speech_setLanguage", {} },
    },

    {
        b2b::translate_getTranslate,
        { b2b::translate_getTranslate, false, "translate_getTranslate", {} },
    },
    {
        b2b::translate_getViewerLanguage,
        { b2b::translate_getViewerLanguage, false, "translate_getViewerLanguage", {} },
    },

    {
        b2b::makeymakey_whenMakeyKeyPressed,
        { b2b::makeymakey_whenMakeyKeyPressed, true, "makeymakey_whenMakeyKeyPressed", {} },
    },
    {
        b2b::makeymakey_whenCodePressed,
        { b2b::makeymakey_whenCodePressed, true, "makeymakey_whenCodePressed", {} },
    },

    {
        b2b::microbit_whenButtonPressed,
        { b2b::microbit_whenButtonPressed, true, "microbit_whenButtonPressed", {} },
    },
    {
        b2b::microbit_isButtonPressed,
        { b2b::microbit_isButtonPressed, false, "microbit_isButtonPressed", {} },
    },
    {
        b2b::microbit_whenGesture,
        { b2b::microbit_whenGesture, true, "microbit_whenGesture", {} },
    },
    {
        b2b::microbit_displaySymbol,
        { b2b::microbit_displaySymbol, false, "microbit_displaySymbol", {} },
    },
    {
        b2b::microbit_displayText,
        { b2b::microbit_displayText, false, "microbit_displayText", {} },
    },
    {
        b2b::microbit_displayClear,
        { b2b::microbit_displayClear, false, "microbit_displayClear", {} },
    },
    {
        b2b::microbit_whenTilted,
        { b2b::microbit_whenTilted, true, "microbit_whenTilted", {} },
    },
    {
        b2b::microbit_isTilted,
        { b2b::microbit_isTilted, false, "microbit_isTilted", {} },
    },
    {
        b2b::microbit_getTiltAngle,
        { b2b::microbit_getTiltAngle, false, "microbit_getTiltAngle", {} },
    },
    {
        b2b::microbit_whenPinConnected,
        { b2b::microbit_whenPinConnected, true, "microbit_whenPinConnected", {} },
    },

    {
        b2b::ev3_motorTurnClockwise,
        { b2b::ev3_motorTurnClockwise, false, "ev3_motorTurnClockwise", {} },
    },
    {
        b2b::ev3_motorTurnCounterClockwise,
        { b2b::ev3_motorTurnCounterClockwise, false, "ev3_motorTurnCounterClockwise", {} },
    },
    {
        b2b::ev3_motorSetPower,
        { b2b::ev3_motorSetPower, false, "ev3_motorSetPower", {} },
    },
    {
        b2b::ev3_getMotorPosition,
        { b2b::ev3_getMotorPosition, false, "ev3_getMotorPosition", {} },
    },
    {
        b2b::ev3_whenButtonPressed,
        { b2b::ev3_whenButtonPressed, true, "ev3_whenButtonPressed", {} },
    },
    {
        b2b::ev3_whenDistanceLessThan,
        { b2b::ev3_whenDistanceLessThan, true, "ev3_whenDistanceLessThan", {} },
    },
    {
        b2b::ev3_whenBrightnessLessThan,
        { b2b::ev3_whenBrightnessLessThan, true, "ev3_whenBrightnessLessThan", {} },
    },
    {
        b2b::ev3_buttonPressed,
        { b2b::ev3_buttonPressed, false, "ev3_buttonPressed", {} },
    },
    {
        b2b::ev3_getDistance,
        { b2b::ev3_getDistance, false, "ev3_getDistance", {} },
    },
    {
        b2b::ev3_getBrightness,
        { b2b::ev3_getBrightness, false, "ev3_getBrightness", {} },
    },
    {
        b2b::ev3_beep,
        { b2b::ev3_beep, false, "ev3_beep", {} },
    },

    {
        b2b::boost_motorOnFor,
        { b2b::boost_motorOnFor, false, "boost_motorOnFor", {} },
    },
    {
        b2b::boost_motorOnForRotation,
        { b2b::boost_motorOnForRotation, false, "boost_motorOnForRotation", {} },
    },
    {
        b2b::boost_motorOn,
        { b2b::boost_motorOn, false, "boost_motorOn", {} },
    },
    {
        b2b::boost_motorOff,
        { b2b::boost_motorOff, false, "boost_motorOff", {} },
    },
    {
        b2b::boost_setMotorPower,
        { b2b::boost_setMotorPower, false, "boost_setMotorPower", {} },
    },
    {
        b2b::boost_setMotorDirection,
        { b2b::boost_setMotorDirection, false, "boost_setMotorDirection", {} },
    },
    {
        b2b::boost_getMotorPosition,
        { b2b::boost_getMotorPosition, false, "boost_getMotorPosition", {} },
    },
    {
        b2b::boost_whenColor,
        { b2b::boost_whenColor, true, "boost_whenColor", {} },
    },
    {
        b2b::boost_seeingColor,
        { b2b::boost_seeingColor, false, "boost_seeingColor", {} },
    },
    {
        b2b::boost_whenTilted,
        { b2b::boost_whenTilted, true, "boost_whenTilted", {} },
    },
    {
        b2b::boost_getTiltAngle,
        { b2b::boost_getTiltAngle, false, "boost_getTiltAngle", {} },
    },
    {
        b2b::boost_setLightHue,
        { b2b::boost_setLightHue, false, "boost_setLightHue", {} },
    },

    {
        b2b::wedo2_motorOnFor,
        { b2b::wedo2_motorOnFor, false, "wedo2_motorOnFor", {} },
    },
    {
        b2b::wedo2_motorOn,
        { b2b::wedo2_motorOn, false, "wedo2_motorOn", {} },
    },
    {
        b2b::wedo2_motorOff,
        { b2b::wedo2_motorOff, false, "wedo2_motorOff", {} },
    },
    {
        b2b::wedo2_startMotorPower,
        { b2b::wedo2_startMotorPower, false, "wedo2_startMotorPower", {} },
    },
    {
        b2b::wedo2_setMotorDirection,
        { b2b::wedo2_setMotorDirection, false, "wedo2_setMotorDirection", {} },
    },
    {
        b2b::wedo2_setLightHue,
        { b2b::wedo2_setLightHue, false, "wedo2_setLightHue", {} },
    },
    {
        b2b::wedo2_whenDistance,
        { b2b::wedo2_whenDistance, true, "wedo2_whenDistance", {} },
    },
    {
        b2b::wedo2_whenTilted,
        { b2b::wedo2_whenTilted, true, "wedo2_whenTilted", {} },
    },
    {
        b2b::wedo2_getDistance,
        { b2b::wedo2_getDistance, false, "wedo2_getDistance", {} },
    },
    {
        b2b::wedo2_isTilted,
        { b2b::wedo2_isTilted, false, "wedo2_isTilted", {} },
    },
    {
        b2b::wedo2_getTiltAngle,
        { b2b::wedo2_getTiltAngle, false, "wedo2_getTiltAngle", {} },
    },
    {
        b2b::wedo2_playNoteFor,
        { b2b::wedo2_playNoteFor, false, "wedo2_playNoteFor", {} },
    },

    {
        b2b::gdxfor_whenGesture,
        { b2b::gdxfor_whenGesture, true, "gdxfor_whenGesture", {} },
    },
    {
        b2b::gdxfor_whenForcePushedOrPulled,
        { b2b::gdxfor_whenForcePushedOrPulled, true, "gdxfor_whenForcePushedOrPulled", {} },
    },
    {
        b2b::gdxfor_getForce,
        { b2b::gdxfor_getForce, false, "gdxfor_getForce", {} },
    },
    {
        b2b::gdxfor_whenTilted,
        { b2b::gdxfor_whenTilted, true, "gdxfor_whenTilted", {} },
    },
    {
        b2b::gdxfor_isTilted,
        { b2b::gdxfor_isTilted, false, "gdxfor_isTilted", {} },
    },
    {
        b2b::gdxfor_getTilt,
        { b2b::gdxfor_getTilt, false, "gdxfor_getTilt", {} },
    },
    {
        b2b::gdxfor_isFreeFalling,
        { b2b::gdxfor_isFreeFalling, false, "gdxfor_isFreeFalling", {} },
    },
    {
        b2b::gdxfor_getSpinSpeed,
        { b2b::gdxfor_getSpinSpeed, false, "gdxfor_getSpinSpeed", {} },
    },
    {
        b2b::gdxfor_getAcceleration,
        { b2b::gdxfor_getAcceleration, false, "gdxfor_getAcceleration", {} },
    },

    /* MENU BLOCKS */

    {
        b2b::motion_goto_menu,
        { b2b::motion_goto_menu, false, "motion_goto_menu", {} },
    },
    {
        b2b::motion_glideto_menu,
        { b2b::motion_glideto_menu, false, "motion_glideto_menu", {} },
    },
    {
        b2b::motion_pointtowards_menu,
        { b2b::motion_pointtowards_menu, false, "motion_pointtowards_menu", {} },
    },

    {
        b2b::looks_costume,
        { b2b::looks_costume, false, "looks_costume", {} },
    },
    {
        b2b::looks_backdrops,
        { b2b::looks_backdrops, false, "looks_backdrops", {} },
    },

    {
        b2b::sound_sounds_menu,
        { b2b::sound_sounds_menu, false, "sound_sounds_menu", {} },
    },

    {
        b2b::event_broadcast_menu,
        { b2b::event_broadcast_menu, false, "event_broadcast_menu", {} },
    },
    {
        b2b::event_touchingobjectmenu,
        { b2b::event_touchingobjectmenu, false, "event_touchingobjectmenu", {} },
    },

    {
        b2b::control_create_clone_of_menu,
        { b2b::control_create_clone_of_menu, false, "control_create_clone_of_menu", {} },
    },

    {
        b2b::sensing_touchingobjectmenu,
        { b2b::sensing_touchingobjectmenu, false, "sensing_touchingobjectmenu", {} },
    },
    {
        b2b::sensing_distancetomenu,
        { b2b::sensing_distancetomenu, false, "sensing_distancetomenu", {} },
    },
    {
        b2b::sensing_keyoptions,
        { b2b::sensing_keyoptions, false, "sensing_keyoptions", {} },
    },
    {
        b2b::sensing_of_object_menu,
        { b2b::sensing_of_object_menu, false, "sensing_of_object_menu", {} },
    },

    {
        b2b::data_listindexall,
        { b2b::data_listindexall, false, "data_listindexall", {} },
    },
    {
        b2b::data_listindexrandom,
        { b2b::data_listindexrandom, false, "data_listindexrandom", {} },
    },

    {
        b2b::music_menu_DRUM,
        { b2b::music_menu_DRUM, false, "music_menu_DRUM", {} },
    },
    {
        b2b::music_menu_INSTRUMENT,
        { b2b::music_menu_INSTRUMENT, false, "music_menu_INSTRUMENT", {} },
    },

    {
        b2b::pen_menu_colorParam,
        { b2b::pen_menu_colorParam, false, "pen_menu_colorParam", {} },
    },

    {
        b2b::videoSensing_menu_ATTRIBUTE,
        { b2b::videoSensing_menu_ATTRIBUTE, false, "videoSensing_menu_ATTRIBUTE", {} },
    },
    {
        b2b::videoSensing_menu_SUBJECT,
        { b2b::videoSensing_menu_SUBJECT, false, "videoSensing_menu_SUBJECT", {} },
    },
    {
        b2b::videoSensing_menu_VIDEO_STATE,
        { b2b::videoSensing_menu_VIDEO_STATE, false, "videoSensing_menu_VIDEO_STATE", {} },
    },

    {
        b2b::text2speech_menu_voices,
        { b2b::text2speech_menu_voices, false, "text2speech_menu_voices", {} },
    },
    {
        b2b::text2speech_menu_languages,
        { b2b::text2speech_menu_languages, false, "text2speech_menu_languages", {} },
    },

    {
        b2b::translate_menu_languages,
        { b2b::translate_menu_languages, false, "translate_menu_languages", {} },
    },

    {
        b2b::makeymakey_menu_KEY,
        { b2b::makeymakey_menu_KEY, false, "makeymakey_menu_KEY", {} },
    },
    {
        b2b::makeymakey_menu_SEQUENCE,
        { b2b::makeymakey_menu_SEQUENCE, false, "makeymakey_menu_SEQUENCE", {} },
    },

    {
        b2b::microbit_menu_buttons,
        { b2b::microbit_menu_buttons, false, "microbit_menu_buttons", {} },
    },
    {
        b2b::microbit_menu_gestures,
        { b2b::microbit_menu_gestures, false, "microbit_menu_gestures", {} },
    },
    {
        b2b::microbit_menu_tiltDirectionAny,
        { b2b::microbit_menu_tiltDirectionAny, false, "microbit_menu_tiltDirectionAny", {} },
    },
    {
        b2b::microbit_menu_tiltDirection,
        { b2b::microbit_menu_tiltDirection, false, "microbit_menu_tiltDirection", {} },
    },
    {
        b2b::microbit_menu_touchPins,
        { b2b::microbit_menu_touchPins, false, "microbit_menu_touchPins", {} },
    },
    {
        b2b::microbit_menu_pinState,
        { b2b::microbit_menu_pinState, false, "microbit_menu_pinState", {} },
    },

    {
        b2b::ev3_menu_motorPorts,
        { b2b::ev3_menu_motorPorts, false, "ev3_menu_motorPorts", {} },
    },
    {
        b2b::ev3_menu_sensorPorts,
        { b2b::ev3_menu_sensorPorts, false, "ev3_menu_sensorPorts", {} },
    },

    {
        b2b::boost_menu_MOTOR_ID,
        { b2b::boost_menu_MOTOR_ID, false, "boost_menu_MOTOR_ID", {} },
    },
    {
        b2b::boost_menu_MOTOR_DIRECTION,
        { b2b::boost_menu_MOTOR_DIRECTION, false, "boost_menu_MOTOR_DIRECTION", {} },
    },
    {
        b2b::boost_menu_MOTOR_REPORTER_ID,
        { b2b::boost_menu_MOTOR_REPORTER_ID, false, "boost_menu_MOTOR_REPORTER_ID", {} },
    },
    {
        b2b::boost_menu_COLOR,
        { b2b::boost_menu_COLOR, false, "boost_menu_COLOR", {} },
    },
    {
        b2b::boost_menu_TILT_DIRECTION_ANY,
        { b2b::boost_menu_TILT_DIRECTION_ANY, false, "boost_menu_TILT_DIRECTION_ANY", {} },
    },
    {
        b2b::boost_menu_TILT_DIRECTION,
        { b2b::boost_menu_TILT_DIRECTION, false, "boost_menu_TILT_DIRECTION", {} },
    },

    {
        b2b::wedo2_menu_MOTOR_ID,
        { b2b::wedo2_menu_MOTOR_ID, false, "wedo2_menu_MOTOR_ID", {} },
    },
    {
        b2b::wedo2_menu_MOTOR_DIRECTION,
        { b2b::wedo2_menu_MOTOR_DIRECTION, false, "wedo2_menu_MOTOR_DIRECTION", {} },
    },
    {
        b2b::wedo2_menu_OP,
        { b2b::wedo2_menu_OP, false, "wedo2_menu_OP", {} },
    },
    {
        b2b::wedo2_menu_TILT_DIRECTION_ANY,
        { b2b::wedo2_menu_TILT_DIRECTION_ANY, false, "wedo2_menu_TILT_DIRECTION_ANY", {} },
    },
    {
        b2b::wedo2_menu_TILT_DIRECTION,
        { b2b::wedo2_menu_TILT_DIRECTION, false, "wedo2_menu_TILT_DIRECTION", {} },
    },

    {
        b2b::gdxfor_menu_gestureOptions,
        { b2b::gdxfor_menu_gestureOptions, false, "gdxfor_menu_gestureOptions", {} },
    },
    {
        b2b::gdxfor_menu_pushPullOptions,
        { b2b::gdxfor_menu_pushPullOptions, false, "gdxfor_menu_pushPullOptions", {} },
    },
    {
        b2b::gdxfor_menu_tiltAnyOptions,
        { b2b::gdxfor_menu_tiltAnyOptions, false, "gdxfor_menu_tiltAnyOptions", {} },
    },
    {
        b2b::gdxfor_menu_tiltOptions,
        { b2b::gdxfor_menu_tiltOptions, false, "gdxfor_menu_tiltOptions", {} },
    },
    {
        b2b::gdxfor_menu_axisOptions,
        { b2b::gdxfor_menu_axisOptions, false, "gdxfor_menu_axisOptions", {} },
    },

    {
        b2b::procedures_prototype,
        { b2b::procedures_prototype, false, "procedures_prototype", {} },
    },

    {
        b2b::argument_editor_boolean,
        { b2b::argument_editor_boolean, false, "argument_editor_boolean", {} },
    },
    {
        b2b::argument_editor_string_number,
        { b2b::argument_editor_string_number, false, "argument_editor_string_number", {} },
    },

    {
        b2b::note,
        { b2b::note, false, "note", {} },
    },

    {
        b2b::matrix,
        { b2b::matrix, false, "matrix", {} },
    },

    {
        b2b::math_number,
        { b2b::math_number, false, "math_number", {} },
    },
    {
        b2b::math_positive_number,
        { b2b::math_positive_number, false, "math_positive_number", {} },
    },
    {
        b2b::math_whole_number,
        { b2b::math_whole_number, false, "math_whole_number", {} },
    },
    {
        b2b::math_integer,
        { b2b::math_integer, false, "math_integer", {} },
    },
    {
        b2b::math_angle,
        { b2b::math_angle, false, "math_angle", {} },
    },

    {
        b2b::colour_picker,
        { b2b::colour_picker, false, "colour_picker", {} },
    },

    {
        b2b::text,
        { b2b::text, false, "text", {} },
    },
};

b2b::OpcodeE b2b::ToOpcode(const std::string &string)
{
    for (auto &value : INDEX | std::views::values)
    {
        if (value.Name == string)
        {
            return value.Opcode;
        }
    }
    throw std::runtime_error("undefined opcode name");
}

bool b2b::IsEntry(const OpcodeE opcode)
{
    return INDEX.at(opcode).IsEntry;
}

const char *b2b::GetName(const OpcodeE opcode)
{
    return INDEX.at(opcode).Name;
}

unsigned b2b::GetOperandCount(const OpcodeE opcode)
{
    return INDEX.at(opcode).Operands.size();
}

const char *b2b::GetOperandName(const OpcodeE opcode, const unsigned index)
{
    return INDEX.at(opcode).Operands.at(index);
}

std::ostream &b2b::operator<<(std::ostream &stream, const OpcodeE opcode)
{
    return stream << INDEX.at(opcode).Name;
}
