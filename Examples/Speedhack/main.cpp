// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "../../il2cpp/il2cpp-utils.hpp"
#include "helpers.h"
#include <iostream>

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

// Injected code entry point
void Run()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    std::cout << "Initializing..." << std::endl;

    size_t size = 0;
    const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(nullptr, &size);

    const Il2CppAssembly* assembly = BTD6API::Assembly::init(assemblies, size);

    if (assembly == nullptr)
    {
        std::cout << "Error: Assembly-CSharp not found." << std::endl;
        return;
    }
	
	int speed = 10;
	float speedF = static_cast<float>(speed);

	while (true)
	{
		Il2CppClass* timeClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Utils", "TimeManager");
		if (timeClass != NULL)
		{
			FieldInfo* fastForwardInfo = il2cpp_class_get_field_from_name(timeClass, "compromisedFastFowardRate");
			int compromisedFastForwardRate = 0;
			il2cpp_field_static_get_value(fastForwardInfo, &compromisedFastForwardRate);
			if (compromisedFastForwardRate != speed)
			{
				FieldInfo* maxStepsInfo = il2cpp_class_get_field_from_name(timeClass, "maxSimulationStepsPerUpdate");
				il2cpp_field_static_set_value(fastForwardInfo, &speed);
				il2cpp_field_static_set_value(maxStepsInfo, &speedF);
				std::cout << "Game speed set from 3 -> " << std::to_string(speed) << std::endl;
			} // if compromisedFastFowardRate is not 10, that means it is likely unchanged, so patch
		}
		else
		{
			std::cout << "Could not find TimeManager! That's odd. Should've been able to." << std::endl;
		}
		Sleep(500);
	} // wanna do this every 0.5 second, that should be good enough. i'm too lazy to do events
}