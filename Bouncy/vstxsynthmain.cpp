#include <stddef.h>
#include "vstxsynth.h"

static AudioEffect *effect = 0;
bool oome = false;

#if MAC
#pragma export on
#endif

//------------------------------------------------------------------------
// prototype of the export function main
#if BEOS
#define main main_plugin
extern "C" __declspec(dllexport) AEffect *main_plugin (audioMasterCallback audioMaster);

#else
AEffect *main (audioMasterCallback audioMaster);
#endif

#if WIN32
#include <windows.h>
#endif

AEffect *main (audioMasterCallback audioMaster)
{
	// get vst version
	if(!audioMaster (0, audioMasterVersion, 0, 0, 0, 0))
		return 0;  // old version

	effect = new VstXSynth (audioMaster);

	if (!effect)
		return 0;
	if (oome)
	{
		delete effect;
		return 0;
	}
	return effect->getAeffect ();
}

#if MAC
#pragma export off
#endif

#if WIN32
void* hInstance;
BOOL WINAPI DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpvReserved)
{
	hInstance = hInst;
	return 1;
}
#endif
