// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "stdafx.h"
#include "resource.h"
#include "dllmain.h"

#include "Common.h"
#include "EED.h"

#include <crtdbg.h>

CMagoNatEEModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE /*hInstance*/, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _DEBUG
    if (dwReason == DLL_PROCESS_ATTACH)
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    BOOL rc = _AtlModule.DllMain(dwReason, lpReserved);

    switch ( dwReason )
    {
    case DLL_PROCESS_ATTACH:
        MagoEE::Init();
        break;

    case DLL_PROCESS_DETACH:
        MagoEE::Uninit();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }

    return rc;
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
