#pragma once

#ifdef MYDLL_EXPORTS  
#define MYDLL_API __declspec(dllexport)
#else  
#define MYDLL_API __declspec(dllimport)
#endif  


// extern "C" tells compiler to use C-style function naming 
// (prevents C++ style name mangling) so function can be 
// called from C and other languages.
extern "C" MYDLL_API int Add(int a, int b);

