// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// IL2CPP application initializer

#pragma once

#include <cstdint>

// Application-specific types
#include "il2cpp-types.h"

// IL2CPP API function pointers
#include "il2cpp-function-ptr.h"

// IL2CPP APIs
#define DO_API(r, n, p) r (*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Application-specific functions
#define DO_APP_FUNC(a, r, n, p) r (*n) p
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

// TypeInfo pointers
#define DO_TYPEDEF(a, n) n ## __Class* n ## __TypeInfo
#include "il2cpp-type-ptr.h"
#undef DO_TYPEDEF

// Try not to include any Windows symbosl that might cause a naming conflict
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOIME
#define NOWINRES
#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOUSER
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NOIME
#define NOPROXYSTUB
#define NOIMAGE
#define NO
#define NOTAPE
#define ANSI_ONLY
#include "windows.h"

// Initialize everything
void init_il2cpp() {
	// Get base address of IL2CPP module
	uintptr_t baseAddress = (uintptr_t) GetModuleHandleW(L"GameAssembly.dll");

	// Define IL2CPP API function addresses
	#define DO_API(r, n, p) n = (r (*) p)(baseAddress + n ## _ptr)
	#include "il2cpp-api-functions.h"
	#undef DO_API

	// Define function addresses
	#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC

	// Define TypeInfo variables
	#define DO_TYPEDEF(a, n) n ## __TypeInfo = *(n ## __Class**) (baseAddress + a);
	#include "il2cpp-type-ptr.h"
	#undef DO_TYPEDEF
}