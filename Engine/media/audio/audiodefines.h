//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-20xx others
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// http://www.opensource.org/licenses/artistic-license-2.0.php
//
//=============================================================================

#ifndef __AC_AUDIODEFINES_H
#define __AC_AUDIODEFINES_H

#define MUS_MIDI 1
#define MUS_MP3  2
#define MUS_WAVE 3
#define MUS_MOD  4
#define MUS_OGG  5

// Max channels that are distributed among game's audio types
#define MAX_GAME_CHANNELS         8
#define SPECIAL_CROSSFADE_CHANNEL (MAX_GAME_CHANNELS)
// Total number of channels: game chans + utility chans
#define TOTAL_AUDIO_CHANNELS      (MAX_GAME_CHANNELS + 1)
// Number of game channels reserved for speech voice-over
#define NUM_SPEECH_CHANS          1

#define SCHAN_SPEECH  0
#define SCHAN_AMBIENT 1
#define SCHAN_MUSIC   2
#define SCHAN_NORMAL  3
#define AUDIOTYPE_LEGACY_AMBIENT_SOUND 1
#define AUDIOTYPE_LEGACY_MUSIC 2
#define AUDIOTYPE_LEGACY_SOUND 3

#endif // __AC_AUDIODEFINES_H