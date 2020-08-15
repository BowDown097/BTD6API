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
	auto upgradeModelsArr = gameInstance->fields.model->fields.upgrades;
	TowerModel** towerModels = towerModelsArr->vector;
	UpgradeModel** upgradeModels = upgradeModelsArr->vector;

	AttackModel* towerAttack = 0;
	for (int i = 0; i < towerModelsArr->max_length; ++i)
	{
		if (towerModels[i]->fields.display != NULL)
		{
			if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.baseId) == L"Wizard-LordPhoenix")
			{
				Model__Array* modelsArr = towerModels[i]->fields.behaviors;
				AttackModel* attackModel = (AttackModel*)(BTD6API::ModelUtils::locateModel(modelsArr, L"AttackModel"));
				if (attackModel != NULL)
				{
					attackModel->fields.attackThroughWalls = false;
					for (int j = 0; j < attackModel->fields.weapons->max_length; ++j)
					{
						attackModel->fields.weapons->vector[j]->fields.rate = 10;
						attackModel->fields.weapons->vector[j]->fields.projectile->fields.pierce = 1;
					}
					towerAttack = attackModel;
				}
				break;
			}
		}
	}

	for (int i = 0; i < towerModelsArr->max_length; ++i)
	{
		if (towerModels[i]->fields.display != NULL)
		{
			if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.portrait).find(L"000-DartMonkey") != std::wstring::npos)
			{
				towerModels[i]->fields.cost = 1700;

				BTD6API::TowerUtils::patchTowerAttack(towerModels[i], towerAttack);
				std::cout << "Found and patched 000 Dart TowerModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.behaviors->vector[0]->fields.name).find(L"DartMonkey-100") != std::wstring::npos)
			{
				for (int j = 0; j < towerAttack->fields.weapons->max_length; ++j)
				{
					towerAttack->fields.weapons->vector[j]->fields.projectile->fields.pierce = 2;
				}

				BTD6API::TowerUtils::patchTowerAttack(towerModels[i], towerAttack);
				std::cout << "Found and patched 100 Dart TowerModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.behaviors->vector[0]->fields.name).find(L"DartMonkey-200") != std::wstring::npos)
			{
				for (int j = 0; j < towerAttack->fields.weapons->max_length; ++j)
				{
					towerAttack->fields.weapons->vector[j]->fields.rate = 6;
				}

				BTD6API::TowerUtils::patchTowerAttack(towerModels[i], towerAttack);
				std::cout << "Found and patched 200 Dart TowerModel" << std::endl;
			}
			// TODO: 300 add lightning and fire tornadoes
			// TODO: 400 add fire ring
			else if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.behaviors->vector[0]->fields.name).find(L"DartMonkey-500") != std::wstring::npos)
			{
				for (int j = 0; j < towerAttack->fields.weapons->max_length; ++j)
				{
					towerAttack->fields.weapons->vector[j]->fields.rate = 0.01f;
				}

				BTD6API::TowerUtils::patchTowerAttack(towerModels[i], towerAttack);
				std::cout << "Found and patched 500 Dart TowerModel" << std::endl;
			}
		}
	}

	for (int i = 0; i < upgradeModelsArr->max_length; ++i)
	{
		if (upgradeModels[i]->fields.icon != NULL)
		{
			if (BTD6API::StringUtils::toWideString(upgradeModels[i]->fields.icon).find(L"/SharpShots") != std::wstring::npos)
			{
				upgradeModels[i]->fields.cost = 1100;
				upgradeModels[i]->fields.localizedNameOverride = (String*)il2cpp_string_new("Hotter Fire");

				std::cout << "Found and patched 100 Dart UpgradeModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(upgradeModels[i]->fields.icon).find(L"/RazorSharpShots") != std::wstring::npos)
			{
				upgradeModels[i]->fields.cost = 1700;
				upgradeModels[i]->fields.localizedNameOverride = (String*)il2cpp_string_new("Rapid Production");

				std::cout << "Found and patched 200 Dart UpgradeModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(upgradeModels[i]->fields.icon).find(L"/Spike-o-pult") != std::wstring::npos)
			{
				upgradeModels[i]->fields.cost = 8400;
				upgradeModels[i]->fields.localizedNameOverride = (String*)il2cpp_string_new("Raging Thunder");

				std::cout << "Found and patched 300 Dart UpgradeModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(upgradeModels[i]->fields.icon).find(L"/Juggernaut") != std::wstring::npos)
			{
				upgradeModels[i]->fields.cost = 70000;
				upgradeModels[i]->fields.localizedNameOverride = (String*)il2cpp_string_new("Hellstorm");

				std::cout << "Found and patched 400 Dart UpgradeModel" << std::endl;
			}
			else if (BTD6API::StringUtils::toWideString(upgradeModels[i]->fields.icon).find(L"/UltraJuggernaut") != std::wstring::npos)
			{
				upgradeModels[i]->fields.cost = 999999;
				upgradeModels[i]->fields.localizedNameOverride = (String*)il2cpp_string_new("HYPERSONIC!!!!!");
				upgradeModels[i]->fields.confirmation = (String*)il2cpp_string_new("This will probably crash your game. Good luck.");

				std::cout << "Found and patched 500 Dart UpgradeModel" << std::endl;
			}
		}
	}
}