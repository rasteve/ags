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
//
// Functions related to finding and opening game assets.
//
//=============================================================================
#ifndef __AGS_EE_AC__ASSETHELPER_H
#define __AGS_EE_AC__ASSETHELPER_H
#include <memory>
#include <utility>
#include "core/assetmanager.h"

namespace AGS { namespace Common {class Stream;} }
using AGS::Common::AssetPath;
using AGS::Common::Stream;
using AGS::Common::String;

// Looks for valid asset library everywhere and returns path, or empty string if failed
String  find_assetlib(const String &filename);

extern "C" {
    struct PACKFILE; // Allegro 4's own stream type
}

// Returns the path to the audio asset, considering the given bundling type
AssetPath get_audio_clip_assetpath(int bundling_type, const String &filename);
// Returns the path to the voice-over asset
AssetPath get_voice_over_assetpath(const String &filename);

// Custom AGS PACKFILE user object
// TODO: it is preferrable to let our Stream define custom readable window instead,
// keeping this as simple as possible for now (we may require a stream classes overhaul).
struct AGS_PACKFILE_OBJ
{
    std::unique_ptr<Stream> stream;
    size_t asset_size = 0u;
    size_t remains = 0u;
};
// Creates PACKFILE stream from AGS stream.
// This function is supposed to be used only when you have to create Allegro
// object, passing PACKFILE stream to constructor.
PACKFILE *PackfileFromStream(std::unique_ptr<Stream> stream);

#endif // __AGS_EE_AC__ASSETHELPER_H
