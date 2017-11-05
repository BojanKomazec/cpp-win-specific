#include <Windows.h>
#include <iostream>

// When DLL is published, its bundle usually contains import library (.lib) and a header file.
// Client application can then include that header file to get signatures of exported functions
// and also use .lib in order to facilitate so called load-time dynamic linking (implicit linking)
// where DLL is loaded implicitly when application loads. This can slow down application launch time.
// If USE_IMPORT_LIB is defined, application will use this type of linking.
//
// Otherwise, application will use run-time linking (explicit linking) where applicaton explicitly
// loads DLL in run-time, on demand. In this case import library is not used, dll is loaded explicitly
// and caller is responsible for obtaining the addresses of exported functions. Function pointers
// are declared in line with function signatures from the header file (which is not included in the
// source files ih this case).
//
// Uncomment to test explicit linking.
//#define USE_IMPORT_LIB

#ifdef USE_IMPORT_LIB
#include "..\MyDll\MyDll.h"
#else

// Calling convention in the function declaration here must
// match the one in the DLL. In our example MyDll.dll uses 
// default (__cdecl) calling convention so if we put here:
//    typedef int(__stdcall *AddFunctionType)(int a, int b);
// this would make call
//    Add(1, 2)
// throwing the exception:
//    Run-Time Check Failure #0 - The value of ESP was not properly saved across a function call.  
//    This is usually a result of calling a function declared with one calling convention with a 
//    function pointer declared with a different calling convention.
//
// __cdecl is the default calling convention for C and C++
// so the declaration below is the same as:
//    typedef int(__cdecl *AddFunctionType)(int a, int b);
typedef int(*AddFunctionType)(int a, int b);
#endif

int main()
{
   int error_code = 0;

#ifdef USE_IMPORT_LIB // load-time (implicit) DLL linking

   int res = Add(1, 2);
   std::cout << "Add(1, 2) = " << res;

#else // run-time (explicit) DLL linking

   const char* module_name = "MyDll.dll";

   HMODULE hDll = LoadLibrary(module_name);
   if (hDll)
   {
      AddFunctionType Add = (AddFunctionType) GetProcAddress(hDll, "Add");

      if (Add)
      {
         int res = Add(1, 2);
         std::cout << "Add(1, 2) = " << res;
      }
      else
      {
         std::cout << "GetProcAddress() failed to obtain address of \"Add\" function. Error code: " << GetLastError();
         error_code = 2;
      }

      if (!FreeLibrary(hDll))
      {
         std::cout << "FreeLibrary() failed to unload \"" << module_name << "\". Error code: " << GetLastError();
      }
   }
   else
   {
      std::cout << "LoadLibrary() failed to obtain handle to \"" << module_name << "\". Error code: " << GetLastError();
      error_code = 1;
   }

#endif

   return error_code;
}
