// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// It is not necessary to include this method. 
// Explanation:
// "Run-Time Library Behavior" (MSDN) [https://msdn.microsoft.com/en-us/library
// "_DllMainCRTStartup calls a function called DllMain. Depending on the kind of DLL you are building, Visual C++ provides DllMain for you and it gets linked in so that _DllMainCRTStartup always has something to call."

/*
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
*/

// If we opt to ignore all default libraries (/NODEFAULTLIB) linker will report the following errors:
//    Error	LNK2001	unresolved external symbol __DllMainCRTStartup@12
//    Error	LNK2001	unresolved external symbol __RTC_InitBase
//    Error	LNK2001	unresolved external symbol __RTC_Shutdown

// Explanation:
// "Run-Time Library Behavior" (MSDN) [https://msdn.microsoft.com/en-us/library/988ye33t.aspx] 
// "Included in the C/C++ run-time library code is the DLL entry-point function called _DllMainCRTStartup."
// "When building DLLs in Visual C++, _DllMainCRTStartup is linked in automatically"
//
// Initializing a DLL (MSDN) [https://msdn.microsoft.com/en-us/library/7h0a8139.aspx]
// "The C run-time library provides an entry-point function called _DllMainCRTStartup, and it calls DllMain."
//
// 
// So, if we don't link against CRT library _DllMainCRTStartup implementation will be missing and therefore
// linker reports an error. _DllMainCRTStartup for DLLs is like a main() for EXEs but in case of EXEs we have to
// implement main() ourselves and in case of DLL _DllMainCRTStartup is in CRT as it has to perform some extra
// work (e.g. CRT initialization...). If we want to add custom DLL initialization, we can implement DllMain as
// _DllMainCRTStartup calls DllMain automatically. If main() implementation is missing in EXE project, linker 
// complaints. In the same way it complaints when _DllMainCRTStartup is missing in DLL project (or libraries
// it includes).

