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

	auto towerModelsArr = gameInstance->fields.model->fields.towers;
	TowerModel** towerModels = towerModelsArr->vector;

    for (int i = 0; i < towerModelsArr->max_length; ++i)
    {
        if (towerModels[i]->fields.display != NULL)
        {
            auto modelsArr = towerModels[i]->fields.behaviors;
            Model** models = modelsArr->vector;
            if (models != NULL)
            {
                for (int j = 0; j < modelsArr->max_length; ++j)
                {
                    Model* model = models[j];

                    if (model != NULL && model->fields.name != NULL)
                    {
                        std::wstring name((wchar_t*)(&model->fields.name->fields.m_firstChar));

                        if (name.find(L"AttackModel") != std::wstring::npos)
                        {
                            AttackModel* attackModel = (AttackModel*)(model);

                            auto weaponModelsArr = attackModel->fields.weapons;
                            WeaponModel** weaponModels = weaponModelsArr->vector;

                            for (int k = 0; k < weaponModelsArr->max_length; ++k)
                            {
                                WeaponModel* weaponModel = weaponModels[k];

                                if (weaponModel != NULL)
                                {
                                    weaponModel->fields.rate = 0.01f;
                                    weaponModel->fields.rateFrames = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}