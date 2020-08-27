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

    const Il2CppAssembly* assembly = BTD6API::Assembly::get(assemblies, "Assembly-CSharp", size);

    if (assembly == nullptr)
    {
        std::cout << "Error: Assembly-CSharp not found." << std::endl;
        return;
    }

    Il2CppClass* gameClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity", "Game");
    FieldInfo* instance = il2cpp_class_get_field_from_name(gameClass, "instance");
    Game* gameInstAddr = 0;
    il2cpp_field_static_get_value(instance, &gameInstAddr);

    if (gameInstAddr == NULL)
    {
        std::cout << "Some error occurred when trying to access the game model." << std::endl;
        return;
    }

    Game* gameInstance = (Game*)(gameInstAddr);

    BloonModel__Array* bloonModelArr = gameInstance->fields.model->fields.bloons;
    BloonModel** bloonModels = bloonModelArr->vector;

    for (int i = 0; i < bloonModelArr->max_length; ++i)
    {
        if (bloonModels[i] != NULL)
        {
            float speed = 1 * (rand() % 100);

            if (bloonModels[i]->fields.display != NULL) {
                std::wstring display = BTD6API::StringUtils::toWideString(bloonModels[i]->fields.display);
                std::wcout << L"Bloon: " << display << L", Speed was: " << L"/" << bloonModels[i]->fields.speed << ", Speed now is: " << speed << '\n';
            }

            bloonModels[i]->fields.speed = speed;
        }
    }
}