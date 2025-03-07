//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-2025 various contributors
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// https://opensource.org/license/artistic-2-0/
//
//=============================================================================
#include "ac/dynobj/cc_hotspot.h"
#include "ac/common.h"
#include "ac/hotspot.h"
#include "ac/gamestate.h"
#include "ac/global_hotspot.h"
#include "ac/global_translation.h"
#include "ac/gui.h"
#include "ac/properties.h"
#include "ac/room.h"
#include "ac/roomstatus.h"
#include "ac/string.h"
#include "debug/debug_log.h"
#include "game/roomstruct.h"
#include "gfx/bitmap.h"
#include "script/runtimescriptvalue.h"

using namespace AGS::Common;
using namespace AGS::Engine;

extern RoomStruct thisroom;
extern RoomStatus*croom;
extern ScriptHotspot scrHotspot[MAX_ROOM_HOTSPOTS];
extern CCHotspot ccDynamicHotspot;

bool AssertHotspot(const char *apiname, int hot_id)
{
    if ((hot_id >= 0) && (static_cast<uint32_t>(hot_id) < thisroom.HotspotCount))
        return true;
    debug_script_warn("%s: invalid hotspot id %d (range is 0..%d)", apiname, hot_id, thisroom.HotspotCount - 1);
    return false;
}

void Hotspot_SetEnabled(ScriptHotspot *hss, int newval) {
    if (newval)
        EnableHotspot(hss->id);
    else
        DisableHotspot(hss->id);
}

int Hotspot_GetEnabled(ScriptHotspot *hss) {
    return croom->hotspot[hss->id].Enabled ? 1 : 0;
}

int Hotspot_GetID(ScriptHotspot *hss) {
    return hss->id;
}

const char *Hotspot_GetScriptName(ScriptHotspot *hss)
{
    return CreateNewScriptString(thisroom.Hotspots[hss->id].ScriptName);
}

int Hotspot_GetWalkToX(ScriptHotspot *hss) {
    return GetHotspotPointX(hss->id);
}

int Hotspot_GetWalkToY(ScriptHotspot *hss) {
    return GetHotspotPointY(hss->id);
}

ScriptHotspot *GetHotspotAtScreen(int xx, int yy) {
    return &scrHotspot[GetHotspotIDAtScreen(xx, yy)];
}

ScriptHotspot *GetHotspotAtRoom(int x, int y) {
    return &scrHotspot[get_hotspot_at(x, y)];
}

void Hotspot_GetName(ScriptHotspot *hss, char *buffer) {
    GetHotspotName(hss->id, buffer);
}

const char* Hotspot_GetName_New(ScriptHotspot *hss) {
    if ((hss->id < 0) || (hss->id >= MAX_ROOM_HOTSPOTS))
        quit("!Hotspot.Name: invalid hotspot number");
    return CreateNewScriptString(get_translation(croom->hotspot[hss->id].Name.GetCStr()));
}

void Hotspot_SetName(ScriptHotspot *hss, const char *newName) {
    if ((hss->id < 0) || (hss->id >= MAX_ROOM_HOTSPOTS))
        quit("!Hotspot.Name: invalid hotspot number");
    croom->hotspot[hss->id].Name = newName;
    GUIE::MarkSpecialLabelsForUpdate(kLabelMacro_Overhotspot);
}

bool Hotspot_IsInteractionAvailable(ScriptHotspot *hhot, int mood) {

    play.check_interaction_only = 1;
    RunHotspotInteraction(hhot->id, mood);
    int ciwas = play.check_interaction_only;
    play.check_interaction_only = 0;
    return (ciwas == 2);
}

void Hotspot_RunInteraction (ScriptHotspot *hss, int mood) {
    RunHotspotInteraction(hss->id, mood);
}

int Hotspot_GetProperty (ScriptHotspot *hss, const char *property)
{
    return get_int_property(thisroom.Hotspots[hss->id].Properties, croom->hsProps[hss->id], property);
}

void Hotspot_GetPropertyText (ScriptHotspot *hss, const char *property, char *bufer)
{
    get_text_property(thisroom.Hotspots[hss->id].Properties, croom->hsProps[hss->id], property, bufer);

}

const char* Hotspot_GetTextProperty(ScriptHotspot *hss, const char *property)
{
    return get_text_property_dynamic_string(thisroom.Hotspots[hss->id].Properties, croom->hsProps[hss->id], property);
}

bool Hotspot_SetProperty(ScriptHotspot *hss, const char *property, int value)
{
    return set_int_property(croom->hsProps[hss->id], property, value);
}

bool Hotspot_SetTextProperty(ScriptHotspot *hss, const char *property, const char *value)
{
    return set_text_property(croom->hsProps[hss->id], property, value);
}

int get_hotspot_at(int xpp,int ypp) {
    int onhs=thisroom.HotspotMask->GetPixel(room_to_mask_coord(xpp), room_to_mask_coord(ypp));
    if (onhs <= 0 || onhs >= MAX_ROOM_HOTSPOTS) return 0;
    if (!croom->hotspot[onhs].Enabled) return 0;
    return onhs;
}

//=============================================================================
//
// Script API Functions
//
//=============================================================================

#include "debug/out.h"
#include "script/script_api.h"
#include "script/script_runtime.h"
#include "ac/dynobj/scriptstring.h"


ScriptHotspot *Hotspot_GetByName(const char *name)
{
    return static_cast<ScriptHotspot*>(ccGetScriptObjectAddress(name, ccDynamicHotspot.GetType()));
}


RuntimeScriptValue Sc_Hotspot_GetByName(const RuntimeScriptValue *params, int32_t param_count)
{
    API_SCALL_OBJ_POBJ(ScriptHotspot, ccDynamicHotspot, Hotspot_GetByName, const char);
}

RuntimeScriptValue Sc_GetHotspotAtRoom(const RuntimeScriptValue *params, int32_t param_count)
{
    API_SCALL_OBJ_PINT2(ScriptHotspot, ccDynamicHotspot, GetHotspotAtRoom);
}

// ScriptHotspot *(int xx, int yy)
RuntimeScriptValue Sc_GetHotspotAtScreen(const RuntimeScriptValue *params, int32_t param_count)
{
    API_SCALL_OBJ_PINT2(ScriptHotspot, ccDynamicHotspot, GetHotspotAtScreen);
}

RuntimeScriptValue Sc_Hotspot_GetDrawingSurface(const RuntimeScriptValue *params, int32_t param_count)
{
    API_SCALL_OBJAUTO(ScriptDrawingSurface, Hotspot_GetDrawingSurface);
}

// void (ScriptHotspot *hss, char *buffer)
RuntimeScriptValue Sc_Hotspot_GetName(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_VOID_POBJ(ScriptHotspot, Hotspot_GetName, char);
}

// int  (ScriptHotspot *hss, const char *property)
RuntimeScriptValue Sc_Hotspot_GetProperty(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_INT_POBJ(ScriptHotspot, Hotspot_GetProperty, const char);
}

// void  (ScriptHotspot *hss, const char *property, char *bufer)
RuntimeScriptValue Sc_Hotspot_GetPropertyText(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_VOID_POBJ2(ScriptHotspot, Hotspot_GetPropertyText, const char, char);
}

// const char* (ScriptHotspot *hss, const char *property)
RuntimeScriptValue Sc_Hotspot_GetTextProperty(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_OBJ_POBJ(ScriptHotspot, const char, myScriptStringImpl, Hotspot_GetTextProperty, const char);
}

RuntimeScriptValue Sc_Hotspot_SetProperty(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_BOOL_POBJ_PINT(ScriptHotspot, Hotspot_SetProperty, const char);
}

RuntimeScriptValue Sc_Hotspot_SetTextProperty(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_BOOL_POBJ2(ScriptHotspot, Hotspot_SetTextProperty, const char, const char);
}

RuntimeScriptValue Sc_Hotspot_IsInteractionAvailable(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_BOOL_PINT(ScriptHotspot, Hotspot_IsInteractionAvailable);
}

// void  (ScriptHotspot *hss, int mood)
RuntimeScriptValue Sc_Hotspot_RunInteraction(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_VOID_PINT(ScriptHotspot, Hotspot_RunInteraction);
}

// int (ScriptHotspot *hss)
RuntimeScriptValue Sc_Hotspot_GetEnabled(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_INT(ScriptHotspot, Hotspot_GetEnabled);
}

// void (ScriptHotspot *hss, int newval)
RuntimeScriptValue Sc_Hotspot_SetEnabled(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_VOID_PINT(ScriptHotspot, Hotspot_SetEnabled);
}

// int (ScriptHotspot *hss)
RuntimeScriptValue Sc_Hotspot_GetID(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_INT(ScriptHotspot, Hotspot_GetID);
}

RuntimeScriptValue Sc_Hotspot_GetScriptName(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_OBJ(ScriptHotspot, const char, myScriptStringImpl, Hotspot_GetScriptName);
}

// const char* (ScriptHotspot *hss)
RuntimeScriptValue Sc_Hotspot_GetName_New(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_OBJ(ScriptHotspot, const char, myScriptStringImpl, Hotspot_GetName_New);
}

RuntimeScriptValue Sc_Hotspot_SetName(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_VOID_POBJ(ScriptHotspot, Hotspot_SetName, const char);
}

// int (ScriptHotspot *hss)
RuntimeScriptValue Sc_Hotspot_GetWalkToX(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_INT(ScriptHotspot, Hotspot_GetWalkToX);
}

// int (ScriptHotspot *hss)
RuntimeScriptValue Sc_Hotspot_GetWalkToY(void *self, const RuntimeScriptValue *params, int32_t param_count)
{
    API_OBJCALL_INT(ScriptHotspot, Hotspot_GetWalkToY);
}



void RegisterHotspotAPI()
{
    ScFnRegister hotspot_api[] = {
        { "Hotspot::GetAtRoomXY^2",       API_FN_PAIR(GetHotspotAtRoom) },
        { "Hotspot::GetAtScreenXY^2",     API_FN_PAIR(GetHotspotAtScreen) },
        { "Hotspot::GetByName",           API_FN_PAIR(Hotspot_GetByName) },
        { "Hotspot::GetDrawingSurface",   API_FN_PAIR(Hotspot_GetDrawingSurface) },

        { "Hotspot::GetName^1",           API_FN_PAIR(Hotspot_GetName) },
        { "Hotspot::GetProperty^1",       API_FN_PAIR(Hotspot_GetProperty) },
        { "Hotspot::GetPropertyText^2",   API_FN_PAIR(Hotspot_GetPropertyText) },
        { "Hotspot::GetTextProperty^1",   API_FN_PAIR(Hotspot_GetTextProperty) },
        { "Hotspot::SetProperty^2",       API_FN_PAIR(Hotspot_SetProperty) },
        { "Hotspot::SetTextProperty^2",   API_FN_PAIR(Hotspot_SetTextProperty) },
        { "Hotspot::IsInteractionAvailable^1", API_FN_PAIR(Hotspot_IsInteractionAvailable) },
        { "Hotspot::RunInteraction^1",    API_FN_PAIR(Hotspot_RunInteraction) },
        { "Hotspot::get_Enabled",         API_FN_PAIR(Hotspot_GetEnabled) },
        { "Hotspot::set_Enabled",         API_FN_PAIR(Hotspot_SetEnabled) },
        { "Hotspot::get_ID",              API_FN_PAIR(Hotspot_GetID) },
        { "Hotspot::get_Name",            API_FN_PAIR(Hotspot_GetName_New) },
        { "Hotspot::set_Name",            API_FN_PAIR(Hotspot_SetName) },
        { "Hotspot::get_ScriptName",      API_FN_PAIR(Hotspot_GetScriptName) },
        { "Hotspot::get_WalkToX",         API_FN_PAIR(Hotspot_GetWalkToX) },
        { "Hotspot::get_WalkToY",         API_FN_PAIR(Hotspot_GetWalkToY) },
    };

    ccAddExternalFunctions(hotspot_api);
}
