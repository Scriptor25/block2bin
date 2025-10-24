#include <map>
#include <ranges>
#include <b2b/opcode.hpp>

b2b::OpcodeE b2b::ToOpcode(const std::string &string)
{
    static const std::map<std::string_view, OpcodeE> map
    {
        { "undefined", undefined },

        { "coreExample_exampleOpcode", coreExample_exampleOpcode },
        { "coreExample_exampleWithInlineImage", coreExample_exampleWithInlineImage },

        { "motion_movesteps", motion_movesteps },
        { "motion_turnright", motion_turnright },
        { "motion_turnleft", motion_turnleft },
        { "motion_goto", motion_goto },
        { "motion_gotoxy", motion_gotoxy },
        { "motion_glideto", motion_glideto },
        { "motion_glidesecstoxy", motion_glidesecstoxy },
        { "motion_pointindirection", motion_pointindirection },
        { "motion_pointtowards", motion_pointtowards },
        { "motion_changexby", motion_changexby },
        { "motion_setx", motion_setx },
        { "motion_changeyby", motion_changeyby },
        { "motion_sety", motion_sety },
        { "motion_ifonedgebounce", motion_ifonedgebounce },
        { "motion_setrotationstyle", motion_setrotationstyle },
        { "motion_xposition", motion_xposition },
        { "motion_yposition", motion_yposition },
        { "motion_direction", motion_direction },
        { "motion_scroll_right", motion_scroll_right },
        { "motion_scroll_up", motion_scroll_up },
        { "motion_align_scene", motion_align_scene },
        { "motion_xscroll", motion_xscroll },
        { "motion_yscroll", motion_yscroll },

        { "looks_sayforsecs", looks_sayforsecs },
        { "looks_say", looks_say },
        { "looks_thinkforsecs", looks_thinkforsecs },
        { "looks_think", looks_think },
        { "looks_switchcostumeto", looks_switchcostumeto },
        { "looks_nextcostume", looks_nextcostume },
        { "looks_switchbackdropto", looks_switchbackdropto },
        { "looks_switchbackdroptoandwait", looks_switchbackdroptoandwait },
        { "looks_nextbackdrop", looks_nextbackdrop },
        { "looks_changesizeby", looks_changesizeby },
        { "looks_setsizeto", looks_setsizeto },
        { "looks_changeeffectby", looks_changeeffectby },
        { "looks_seteffectto", looks_seteffectto },
        { "looks_cleargraphiceffects", looks_cleargraphiceffects },
        { "looks_show", looks_show },
        { "looks_hide", looks_hide },
        { "looks_gotofrontback", looks_gotofrontback },
        { "looks_goforwardbackwardlayers", looks_goforwardbackwardlayers },
        { "looks_costumenumbername", looks_costumenumbername },
        { "looks_backdropnumbername", looks_backdropnumbername },
        { "looks_size", looks_size },
        { "looks_hideallsprites", looks_hideallsprites },
        { "looks_setstretchto", looks_setstretchto },
        { "looks_changestretchby", looks_changestretchby },

        { "sound_playuntildone", sound_playuntildone },
        { "sound_play", sound_play },
        { "sound_stopallsounds", sound_stopallsounds },
        { "sound_changeeffectby", sound_changeeffectby },
        { "sound_seteffectto", sound_seteffectto },
        { "sound_cleareffects", sound_cleareffects },
        { "sound_changevolumeby", sound_changevolumeby },
        { "sound_setvolumeto", sound_setvolumeto },
        { "sound_volume", sound_volume },

        { "event_whenflagclicked", event_whenflagclicked },
        { "event_whenkeypressed", event_whenkeypressed },
        { "event_whenthisspriteclicked", event_whenthisspriteclicked },
        { "event_whenstageclicked", event_whenstageclicked },
        { "event_whenbackdropswitchesto", event_whenbackdropswitchesto },
        { "event_whengreaterthan", event_whengreaterthan },
        { "event_whenbroadcastreceived", event_whenbroadcastreceived },
        { "event_broadcast", event_broadcast },
        { "event_broadcastandwait", event_broadcastandwait },
        { "event_whentouchingobject", event_whentouchingobject },

        { "control_wait", control_wait },
        { "control_repeat", control_repeat },
        { "control_forever", control_forever },
        { "control_if", control_if },
        { "control_if_else", control_if_else },
        { "control_wait_until", control_wait_until },
        { "control_repeat_until", control_repeat_until },
        { "control_stop", control_stop },
        { "control_start_as_clone", control_start_as_clone },
        { "control_create_clone_of", control_create_clone_of },
        { "control_delete_this_clone", control_delete_this_clone },
        { "control_for_each", control_for_each },
        { "control_while", control_while },
        { "control_get_counter", control_get_counter },
        { "control_incr_counter", control_incr_counter },
        { "control_clear_counter", control_clear_counter },
        { "control_all_at_once", control_all_at_once },

        { "sensing_touchingobject", sensing_touchingobject },
        { "sensing_touchingcolor", sensing_touchingcolor },
        { "sensing_coloristouchingcolor", sensing_coloristouchingcolor },
        { "sensing_distanceto", sensing_distanceto },
        { "sensing_askandwait", sensing_askandwait },
        { "sensing_answer", sensing_answer },
        { "sensing_keypressed", sensing_keypressed },
        { "sensing_mousedown", sensing_mousedown },
        { "sensing_mousex", sensing_mousex },
        { "sensing_mousey", sensing_mousey },
        { "sensing_setdragmode", sensing_setdragmode },
        { "sensing_loudness", sensing_loudness },
        { "sensing_timer", sensing_timer },
        { "sensing_resettimer", sensing_resettimer },
        { "sensing_of", sensing_of },
        { "sensing_current", sensing_current },
        { "sensing_dayssince2000", sensing_dayssince2000 },
        { "sensing_username", sensing_username },
        { "sensing_loud", sensing_loud },
        { "sensing_userid", sensing_userid },

        { "operator_add", operator_add },
        { "operator_subtract", operator_subtract },
        { "operator_multiply", operator_multiply },
        { "operator_divide", operator_divide },
        { "operator_random", operator_random },
        { "operator_gt", operator_gt },
        { "operator_lt", operator_lt },
        { "operator_equals", operator_equals },
        { "operator_and", operator_and },
        { "operator_or", operator_or },
        { "operator_not", operator_not },
        { "operator_join", operator_join },
        { "operator_letter_of", operator_letter_of },
        { "operator_length", operator_length },
        { "operator_contains", operator_contains },
        { "operator_mod", operator_mod },
        { "operator_round", operator_round },
        { "operator_mathop", operator_mathop },

        { "data_variable", data_variable },
        { "data_setvariableto", data_setvariableto },
        { "data_changevariableby", data_changevariableby },
        { "data_showvariable", data_showvariable },
        { "data_hidevariable", data_hidevariable },

        { "data_listcontents", data_listcontents },
        { "data_addtolist", data_addtolist },
        { "data_deleteoflist", data_deleteoflist },
        { "data_deletealloflist", data_deletealloflist },
        { "data_insertatlist", data_insertatlist },
        { "data_replaceitemoflist", data_replaceitemoflist },
        { "data_itemoflist", data_itemoflist },
        { "data_itemnumoflist", data_itemnumoflist },
        { "data_lengthoflist", data_lengthoflist },
        { "data_listcontainsitem", data_listcontainsitem },
        { "data_showlist", data_showlist },
        { "data_hidelist", data_hidelist },

        { "procedures_definition", procedures_definition },
        { "procedures_call", procedures_call },
        { "procedures_declaration", procedures_declaration },

        { "argument_reporter_string_number", argument_reporter_string_number },
        { "argument_reporter_boolean", argument_reporter_boolean },

        { "music_playDrumForBeats", music_playDrumForBeats },
        { "music_restForBeats", music_restForBeats },
        { "music_playNoteForBeats", music_playNoteForBeats },
        { "music_setInstrument", music_setInstrument },
        { "music_setTempo", music_setTempo },
        { "music_changeTempo", music_changeTempo },
        { "music_getTempo", music_getTempo },
        { "music_midiPlayDrumForBeats", music_midiPlayDrumForBeats },
        { "music_midiSetInstrument", music_midiSetInstrument },

        { "pen_clear", pen_clear },
        { "pen_stamp", pen_stamp },
        { "pen_penDown", pen_penDown },
        { "pen_penUp", pen_penUp },
        { "pen_setPenColorToColor", pen_setPenColorToColor },
        { "pen_changePenColorParamBy", pen_changePenColorParamBy },
        { "pen_setPenColorParamTo", pen_setPenColorParamTo },
        { "pen_changePenSizeBy", pen_changePenSizeBy },
        { "pen_setPenSizeTo", pen_setPenSizeTo },
        { "pen_setPenHueToNumber", pen_setPenHueToNumber },
        { "pen_changePenHueBy", pen_changePenHueBy },
        { "pen_setPenShadeToNumber", pen_setPenShadeToNumber },
        { "pen_changePenShadeBy", pen_changePenShadeBy },

        { "videoSensing_whenMotionGreaterThan", videoSensing_whenMotionGreaterThan },
        { "videoSensing_videoOn", videoSensing_videoOn },
        { "videoSensing_videoToggle", videoSensing_videoToggle },
        { "videoSensing_setVideoTransparency", videoSensing_setVideoTransparency },

        { "text2speech_speakAndWait", text2speech_speakAndWait },
        { "text2speech_setVoice", text2speech_setVoice },
        { "text2speech_setLanguage", text2speech_setLanguage },

        { "translate_getTranslate", translate_getTranslate },
        { "translate_getViewerLanguage", translate_getViewerLanguage },

        { "makeymakey_whenMakeyKeyPressed", makeymakey_whenMakeyKeyPressed },
        { "makeymakey_whenCodePressed", makeymakey_whenCodePressed },

        { "microbit_whenButtonPressed", microbit_whenButtonPressed },
        { "microbit_isButtonPressed", microbit_isButtonPressed },
        { "microbit_whenGesture", microbit_whenGesture },
        { "microbit_displaySymbol", microbit_displaySymbol },
        { "microbit_displayText", microbit_displayText },
        { "microbit_displayClear", microbit_displayClear },
        { "microbit_whenTilted", microbit_whenTilted },
        { "microbit_isTilted", microbit_isTilted },
        { "microbit_getTiltAngle", microbit_getTiltAngle },
        { "microbit_whenPinConnected", microbit_whenPinConnected },

        { "ev3_motorTurnClockwise", ev3_motorTurnClockwise },
        { "ev3_motorTurnCounterClockwise", ev3_motorTurnCounterClockwise },
        { "ev3_motorSetPower", ev3_motorSetPower },
        { "ev3_getMotorPosition", ev3_getMotorPosition },
        { "ev3_whenButtonPressed", ev3_whenButtonPressed },
        { "ev3_whenDistanceLessThan", ev3_whenDistanceLessThan },
        { "ev3_whenBrightnessLessThan", ev3_whenBrightnessLessThan },
        { "ev3_buttonPressed", ev3_buttonPressed },
        { "ev3_getDistance", ev3_getDistance },
        { "ev3_getBrightness", ev3_getBrightness },
        { "ev3_beep", ev3_beep },

        { "boost_motorOnFor", boost_motorOnFor },
        { "boost_motorOnForRotation", boost_motorOnForRotation },
        { "boost_motorOn", boost_motorOn },
        { "boost_motorOff", boost_motorOff },
        { "boost_setMotorPower", boost_setMotorPower },
        { "boost_setMotorDirection", boost_setMotorDirection },
        { "boost_getMotorPosition", boost_getMotorPosition },
        { "boost_whenColor", boost_whenColor },
        { "boost_seeingColor", boost_seeingColor },
        { "boost_whenTilted", boost_whenTilted },
        { "boost_getTiltAngle", boost_getTiltAngle },
        { "boost_setLightHue", boost_setLightHue },

        { "wedo2_motorOnFor", wedo2_motorOnFor },
        { "wedo2_motorOn", wedo2_motorOn },
        { "wedo2_motorOff", wedo2_motorOff },
        { "wedo2_startMotorPower", wedo2_startMotorPower },
        { "wedo2_setMotorDirection", wedo2_setMotorDirection },
        { "wedo2_setLightHue", wedo2_setLightHue },
        { "wedo2_whenDistance", wedo2_whenDistance },
        { "wedo2_whenTilted", wedo2_whenTilted },
        { "wedo2_getDistance", wedo2_getDistance },
        { "wedo2_isTilted", wedo2_isTilted },
        { "wedo2_getTiltAngle", wedo2_getTiltAngle },
        { "wedo2_playNoteFor", wedo2_playNoteFor },

        { "gdxfor_whenGesture", gdxfor_whenGesture },
        { "gdxfor_whenForcePushedOrPulled", gdxfor_whenForcePushedOrPulled },
        { "gdxfor_getForce", gdxfor_getForce },
        { "gdxfor_whenTilted", gdxfor_whenTilted },
        { "gdxfor_isTilted", gdxfor_isTilted },
        { "gdxfor_getTilt", gdxfor_getTilt },
        { "gdxfor_isFreeFalling", gdxfor_isFreeFalling },
        { "gdxfor_getSpinSpeed", gdxfor_getSpinSpeed },
        { "gdxfor_getAcceleration", gdxfor_getAcceleration },

        /* MENU BLOCKS */

        { "motion_goto_menu", motion_goto_menu },
        { "motion_glideto_menu", motion_glideto_menu },
        { "motion_pointtowards_menu", motion_pointtowards_menu },

        { "looks_costume", looks_costume },
        { "looks_backdrops", looks_backdrops },

        { "sound_sounds_menu", sound_sounds_menu },

        { "event_broadcast_menu", event_broadcast_menu },
        { "event_touchingobjectmenu", event_touchingobjectmenu },

        { "control_create_clone_of_menu", control_create_clone_of_menu },

        { "sensing_touchingobjectmenu", sensing_touchingobjectmenu },
        { "sensing_distancetomenu", sensing_distancetomenu },
        { "sensing_keyoptions", sensing_keyoptions },
        { "sensing_of_object_menu", sensing_of_object_menu },

        { "data_listindexall", data_listindexall },
        { "data_listindexrandom", data_listindexrandom },

        { "music_menu_DRUM", music_menu_DRUM },
        { "music_menu_INSTRUMENT", music_menu_INSTRUMENT },

        { "pen_menu_colorParam", pen_menu_colorParam },

        { "videoSensing_menu_ATTRIBUTE", videoSensing_menu_ATTRIBUTE },
        { "videoSensing_menu_SUBJECT", videoSensing_menu_SUBJECT },
        { "videoSensing_menu_VIDEO_STATE", videoSensing_menu_VIDEO_STATE },

        { "text2speech_menu_voices", text2speech_menu_voices },
        { "text2speech_menu_languages", text2speech_menu_languages },

        { "translate_menu_languages", translate_menu_languages },

        { "makeymakey_menu_KEY", makeymakey_menu_KEY },
        { "makeymakey_menu_SEQUENCE", makeymakey_menu_SEQUENCE },

        { "microbit_menu_buttons", microbit_menu_buttons },
        { "microbit_menu_gestures", microbit_menu_gestures },
        { "microbit_menu_tiltDirectionAny", microbit_menu_tiltDirectionAny },
        { "microbit_menu_tiltDirection", microbit_menu_tiltDirection },
        { "microbit_menu_touchPins", microbit_menu_touchPins },
        { "microbit_menu_pinState", microbit_menu_pinState },

        { "ev3_menu_motorPorts", ev3_menu_motorPorts },
        { "ev3_menu_sensorPorts", ev3_menu_sensorPorts },

        { "boost_menu_MOTOR_ID", boost_menu_MOTOR_ID },
        { "boost_menu_MOTOR_DIRECTION", boost_menu_MOTOR_DIRECTION },
        { "boost_menu_MOTOR_REPORTER_ID", boost_menu_MOTOR_REPORTER_ID },
        { "boost_menu_COLOR", boost_menu_COLOR },
        { "boost_menu_TILT_DIRECTION_ANY", boost_menu_TILT_DIRECTION_ANY },
        { "boost_menu_TILT_DIRECTION", boost_menu_TILT_DIRECTION },

        { "wedo2_menu_MOTOR_ID", wedo2_menu_MOTOR_ID },
        { "wedo2_menu_MOTOR_DIRECTION", wedo2_menu_MOTOR_DIRECTION },
        { "wedo2_menu_OP", wedo2_menu_OP },
        { "wedo2_menu_TILT_DIRECTION_ANY", wedo2_menu_TILT_DIRECTION_ANY },
        { "wedo2_menu_TILT_DIRECTION", wedo2_menu_TILT_DIRECTION },

        { "gdxfor_menu_gestureOptions", gdxfor_menu_gestureOptions },
        { "gdxfor_menu_pushPullOptions", gdxfor_menu_pushPullOptions },
        { "gdxfor_menu_tiltAnyOptions", gdxfor_menu_tiltAnyOptions },
        { "gdxfor_menu_tiltOptions", gdxfor_menu_tiltOptions },
        { "gdxfor_menu_axisOptions", gdxfor_menu_axisOptions },

        { "procedures_prototype", procedures_prototype },

        { "argument_editor_boolean", argument_editor_boolean },
        { "argument_editor_string_number", argument_editor_string_number },

        { "note", note },

        { "matrix", matrix },

        { "math_number", math_number },
        { "math_positive_number", math_positive_number },
        { "math_whole_number", math_whole_number },
        { "math_integer", math_integer },
        { "math_angle", math_angle },

        { "colour_picker", colour_picker },

        { "text", text },
    };

    return map.at(string);
}

static std::map<b2b::OpcodeE, b2b::OpcodeT> dictionary;

void b2b::ReadDictionary(std::istream &stream)
{
    nlohmann::json json;
    stream >> json;

    for (auto map = json.get<std::map<std::string, OpcodeT>>(); auto &[key, value] : map)
    {
        dictionary.emplace(ToOpcode(key), std::move(value));
    }
}

bool b2b::IsEntry(const OpcodeE opcode)
{
    return dictionary.at(opcode).IsEntry;
}

std::string b2b::GetName(const OpcodeE opcode)
{
    return dictionary.at(opcode).Name;
}

unsigned b2b::GetInputCount(const OpcodeE opcode)
{
    return dictionary.at(opcode).Inputs.size();
}

std::string b2b::GetInputName(const OpcodeE opcode, const unsigned index)
{
    return dictionary.at(opcode).Inputs.at(index);
}

unsigned b2b::GetFieldCount(const OpcodeE opcode)
{
    return dictionary.at(opcode).Fields.size();
}

std::string b2b::GetFieldName(const OpcodeE opcode, const unsigned index)
{
    return dictionary.at(opcode).Fields.at(index).Name;
}

std::ostream &b2b::operator<<(std::ostream &stream, const OpcodeE opcode)
{
    return stream << dictionary.at(opcode).Name;
}

void b2b::from_json(const nlohmann::json &json, OpcodeE &reference)
{
    const auto string = json.get<std::string>();
    reference = ToOpcode(string);
}

void b2b::from_json(const nlohmann::json &json, OpcodeT &reference)
{
    reference = {
        .IsEntry = json["entry"],
        .Name = json["name"],
        .Inputs = json["inputs"],
        .Fields = json["fields"],
    };
}

void b2b::from_json(const nlohmann::json &json, OpcodeFieldT &reference)
{
    if (json.is_string())
    {
        reference = {
            .IsEnum = false,
            .Name = json.get<std::string>(),
            .Values = {},
        };
        return;
    }

    reference = {
        .IsEnum = true,
        .Name = json["name"],
        .Values = json["values"],
    };
}
