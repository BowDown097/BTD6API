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
	FieldInfo* towers = il2cpp_class_get_field_from_name(gameClass, "towers");
	String__Array* towersArry = NULL;
	il2cpp_field_static_get_value(towers, &towersArry);
	String** towersCArry = towersArry->vector;

	if (towersArry == NULL)
	{
		std::cout << "Some error occurred when trying to access the game model." << std::endl;
		return;
	}

	for (auto i = 0; i < towersArry->max_length; ++i) {
		std::wcout << BTD6API::StringUtils::toWideString(towersArry->vector[i]) << std::endl;
	}

	std::cout << "\n\n" << std::endl;

	BTD6API::Array::resize(towersArry, towersArry->max_length + 1);


	for (auto i = 0; i < towersArry->max_length; ++i) {
		std::wcout << BTD6API::StringUtils::toWideString(towersArry->vector[i]) << std::endl;
	}

	std::wcout << L"Done!" << std::endl;

}