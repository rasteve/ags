//=============================================================================
//
// Adventure Game Studio (AGS)
//
// Copyright (C) 1999-2011 Chris Jones and 2011-2024 various contributors
// The full list of copyright holders can be found in the Copyright.txt
// file, which is part of this source code distribution.
//
// The AGS source code is provided under the Artistic License 2.0.
// A copy of this license can be found in the file License.txt and at
// https://opensource.org/license/artistic-2-0/
//
//=============================================================================
//
//
//
//=============================================================================
#ifndef __AGS_EE_SCRIPT__NONBLOCKINGSCRIPTFUNCTION_H
#define __AGS_EE_SCRIPT__NONBLOCKINGSCRIPTFUNCTION_H

#include "ac/runtime_defines.h"
#include "script/runtimescriptvalue.h"

#include <vector>

struct NonBlockingScriptFunction
{
    const char* functionName;
    int numParameters;
    RuntimeScriptValue params[4];
    bool roomHasFunction;
    bool globalScriptHasFunction;
    std::vector<bool> moduleHasFunction;
    bool atLeastOneImplementationExists;

    NonBlockingScriptFunction(const char*funcName, int numParams)
    {
        this->functionName = funcName;
        this->numParameters = numParams;
        atLeastOneImplementationExists = false;
        roomHasFunction = true;
        globalScriptHasFunction = true;
    }
};

#endif // __AGS_EE_SCRIPT__NONBLOCKINGSCRIPTFUNCTION_H
