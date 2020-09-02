// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"

using namespace app;

void makeWeaponHypersonic(AttackModel* attack) {
    WeaponModel__Array* weaponsArr = attack->fields.weapons;
    WeaponModel** weapons = weaponsArr->vector;

    for (int k = 0; k < weaponsArr->max_length; ++k)
    {
        WeaponModel* weapon = weapons[k];

        if (weapon != NULL)
        {
            weapon->fields.rate = 0.0f;
            weapon->fields.rateFrames = 0;
        }
    }
}

void makeTowerHypersonic(TowerModel* tmdl) {
    Model__Array* modelsArr = tmdl->fields.behaviors;
    Model** models = modelsArr->vector;
    if (models != NULL)
    {
        for (int j = 0; j < modelsArr->max_length; ++j)
        {
            Model* model = models[j];
            if (model != NULL && model->fields.name != NULL)
            {

                std::wstring name = BTD6API::StringUtils::toWideString(model->fields.name);

                // This hero works differently to literally everything else in the game.
                if (name.find(L"DroneSupportModel") != std::wstring::npos) {
                    DroneSupportModel* dsm = (DroneSupportModel*)(model);
                    makeTowerHypersonic(dsm->fields.droneModel);
                }

                if (name.find(L"AttackModel") != std::wstring::npos || name.find(L"AttackAirUnitModel") != std::wstring::npos)
                {
                    AttackModel* attack = (AttackModel*)model;
                    makeWeaponHypersonic(attack);
                }
            }
        }
    }
}


void makeHypersonic(TowerModel__Array* towersArr, const std::string& where)
{
    TowerModel** towers = towersArr->vector;

    for (int i = 0; i < towersArr->max_length; ++i)
    {
        if (towers[i]->fields.display != NULL)
        {
            makeTowerHypersonic(towers[i]);
        }
    }

    std::cout << "Made towers hypersonic (" << where << ")" << std::endl;
}

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

    // do in-game patches (will need to patch InGame if user is currently in-game, just patching Game will do nothing in that case)
    Il2CppClass* inGameClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity.UI_New.InGame", "InGame");
    FieldInfo* inGameInstanceInfo = il2cpp_class_get_field_from_name(inGameClass, "instance");
    InGame* inGameInstAddr = 0;
    il2cpp_field_static_get_value(inGameInstanceInfo, &inGameInstAddr);

    if (inGameInstAddr != NULL)
    {
        InGame* inGameInstance = (InGame*)inGameInstAddr;
        makeHypersonic(inGameInstance->fields.bridge->fields.simulation->fields.model->fields.towers, "in-game");
    }
    // game patches
	Il2CppClass* gameClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity", "Game");
	FieldInfo* gameInstanceInfo = il2cpp_class_get_field_from_name(gameClass, "instance");
	Game* gameInstAddr = 0;
	il2cpp_field_static_get_value(gameInstanceInfo, &gameInstAddr);

	if (gameInstAddr == NULL)
	{
		std::cout << "Some error occurred when trying to access the game model." << std::endl;
		return;
	}

	Game* gameInstance = (Game*)gameInstAddr;
    makeHypersonic(gameInstance->fields.model->fields.towers, "game");
}