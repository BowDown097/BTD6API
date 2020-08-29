// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"
#include <fstream>

using namespace app;

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

	TowerModel__Array* towerModelsArr = gameInstance->fields.model->fields.towers;
	TowerModel** towerModels = towerModelsArr->vector;

	for (int i = 0; i < towerModelsArr->max_length; ++i)
	{
		if (towerModels[i]->fields.display != NULL)
		{
			if (BTD6API::StringUtils::toWideString(towerModels[i]->fields.behaviors->vector[0]->fields.name).find(L"BoomerangMonkey-500") != std::wstring::npos)
			{
				Model__Array* modelsArr = towerModels[i]->fields.behaviors;
				Model** models = modelsArr->vector;
				if (models != NULL)
				{
					for (int j = 0; j < modelsArr->max_length; ++j)
					{
						if (models[j] != NULL && models[j]->fields.name != NULL)
						{
							if (BTD6API::StringUtils::toWideString(models[j]->fields.name).find(L"OrbitModel") != std::wstring::npos)
							{
								OrbitModel* orbit = (OrbitModel*)models[j];
								if (orbit != NULL)
								{
									Model__Array* orbitModelsArr = orbit->fields.projectile->fields.behaviors;
									Model** orbitModels = orbitModelsArr->vector;
									if (orbitModels != NULL)
									{
										for (int k = 0; k < orbitModelsArr->max_length; ++k)
										{
											if (orbitModels[k] != NULL && orbitModels[k]->fields.name != NULL)
											{
												std::cout << BTD6API::StringUtils::toString(orbitModels[k]->fields.name) << std::endl;
												if (BTD6API::StringUtils::toWideString(orbitModels[k]->fields.name).find(L"RotateModel") != std::wstring::npos)
												{
													RotateModel* rotate = (RotateModel*)orbitModels[k];
													if (rotate != NULL)
													{
														rotate->fields.angle = -150.0f;
														rotate->fields.rotationFrames = 0.0f;
														std::cout << "Patched! Rotate angle is " << std::to_string(rotate->fields.angle) << std::endl;
														std::cout << "Patched! Rotation frames are " << std::to_string(rotate->fields.rotationFrames) << "\n\n";
													}
												}
											}
										}
									}
								}
							}
							/*
							else if (BTD6API::StringUtils::toWideString(models[j]->fields.name) == L"AttackModel_OrbitAttack_")
							{
								AttackModel* attack = (AttackModel*)models[j];
								if (attack != NULL)
								{
									WeaponModel__Array* weaponsArr = attack->fields.weapons;
									WeaponModel** weapons = weaponsArr->vector;
									if (weapons != NULL)
									{
										for (int k = 0; k < weaponsArr->max_length; ++k)
										{
											if (weapons[k] != NULL)
											{
												weapons[k]->fields.rate = 0.0f;
												weapons[k]->fields.rateFrames = 0;
												std::cout << "Patched! Rate is 0" << std::endl;
											}
										}
									}
								}
							}
							*/
						}
					}
				}
			}
		}
	}
	/*
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

	const MethodInfo* _method = il2cpp_class_get_method_from_name(gameClass, "GetVersionString", 0);
	if (_method == nullptr)
	{
		std::cout << "Error: Game::GetVersionString not found." << std::endl;
		return;
	}

	std::cout << BTD6API::StringUtils::toString(BTD6API::Assembly::callFunction<String*>(_method, gameInstance, (MethodInfo*)_method));
	*/
}