/*
* Bloon conversions (modifiers are respected):
* Red -> Blue
* Blue -> Green
* Green -> Yellow
* Yellow -> Pink
* Pink -> White/Black (RNG)
* White -> Purple
* Black -> Lead
* Purple -> Lead (fortified)
* Lead -> Zebra
* Zebra -> Rainbow
* Rainbow -> Ceramic
* Ceramic -> MOAB
* MOAB -> BFB
* BFB -> ZOMG
* ZOMG -> DDT
* DDT -> BAD
* BAD -> Fortified BAD
*/

#include "../../il2cpp/il2cpp-utils.hpp"
#include "helpers.h"
#include <iostream>
#include <map>
#include <random>

using namespace app;

std::map<std::string, std::string> promotionMap {
	{"Red", "Blue"},
	{"RedCamo", "BlueCamo"},
	{"RedRegrow", "BlueRegrow"},
	{"RedRegrowCamo", "BlueRegrowCamo"},
	{"Blue", "Green"},
	{"BlueCamo", "GreenCamo"},
	{"BlueRegrow", "GreenRegrow"},
	{"BlueRegrowCamo", "GreenRegrowCamo"},
	{"Green", "Yellow"},
	{"GreenCamo", "YellowCamo"},
	{"GreenRegrow", "YellowRegrow"},
	{"GreenRegrowCamo", "YellowRegrowCamo"},
	{"Yellow", "Pink"},
	{"YellowCamo", "PinkCamo"},
	{"YellowRegrow", "PinkRegrow"},
	{"YellowRegrowCamo", "PinkRegrowCamo"},
	{"White", "Purple"},
	{"WhiteCamo", "PurpleCamo"},
	{"WhiteRegrow", "PurpleRegrow"},
	{"WhiteRegrowCamo", "PurpleRegrowCamo"},
	{"Black", "Lead"},
	{"BlackCamo", "LeadCamo"},
	{"BlackRegrow", "LeadRegrow"},
	{"BlackRegrowCamo", "LeadRegrowCamo"},
	{"Purple", "LeadFortified"},
	{"PurpleCamo", "LeadFortifiedCamo"},
	{"PurpleRegrow", "LeadRegrowFortified"},
	{"PurpleRegrowCamo", "LeadRegrowFortifiedCamo"},
	{"Lead", "Zebra"},
	{"LeadCamo", "ZebraCamo"},
	{"LeadRegrow", "ZebraRegrow"},
	{"LeadRegrowCamo", "ZebraRegrowCamo"},
	{"Zebra", "Rainbow"},
	{"ZebraCamo", "RainbowCamo"},
	{"ZebraRegrow", "RainbowRegrow"},
	{"ZebraRegrowCamo", "RainbowRegrowCamo"},
	{"Rainbow", "Ceramic"},
	{"RainbowCamo", "CeramicCamo"},
	{"RainbowRegrow", "CeramicRegrow"},
	{"RainbowRegrowCamo", "CeramicRegrowCamo"},
	{"Ceramic", "Moab"},
	{"CeramicCamo", "Moab"},
	{"CeramicRegrow", "Moab"},
	{"CeramicRegrowCamo", "Moab"},
	{"CeramicFortified", "MoabFortified"},
	{"CeramicFortifiedCamo", "MoabFortified"},
	{"CeramicRegrowFortified", "MoabFortified"},
	{"CeramicRegrowFortifiedCamo", "MoabFortified"},
	{"Moab", "Bfb"},
	{"MoabFortified", "BfbFortified"},
	{"Bfb", "Zomg"},
	{"BfbFortified", "ZomgFortified"},
	{"Zomg", "Ddt"},
	{"ZomgFortified", "DdtFortified"},
	{"DdtCamo", "Bad"},
	{"DdtFortifiedCamo", "Bad"},
	{"Bad", "BadFortified"}
}; // surely there's a better way to do this..

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

std::string promoteBloon(std::string bloon)
{
	if (bloon.find("Pink") != std::string::npos)
	{
		std::string mod = "";
		if (bloon != "Pink")
			mod = bloon.substr(4, bloon.size() - 4);

		std::random_device r;
		std::uniform_int_distribution<int> uniform_dist(1, 2);
		if (uniform_dist(r) == 1)
			return "White" + mod;
		else
			return "Black" + mod;
	}

	std::string finalBloon = promotionMap[bloon];
	if (finalBloon.empty())
		return bloon;

	return finalBloon;
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

	RoundSetModel__Array* roundSetsArr = gameInstance->fields.model->fields.roundSets;
	RoundSetModel** roundSets = roundSetsArr->vector;
	for (int i = 0; i < roundSetsArr->max_length; ++i)
	{
		RoundModel__Array* roundsArr = roundSets[i]->fields.rounds;
		RoundModel** rounds = roundsArr->vector;
		for (int j = 0; j < roundsArr->max_length; ++j)
		{
			std::cout << "Round" << std::to_string(j + 1) << ":" << std::endl;
			BloonGroupModel__Array* groupsArr = rounds[j]->fields.groups;
			BloonGroupModel** groups = groupsArr->vector;
			for (int k = 0; k < groupsArr->max_length; ++k)
			{
				std::cout << BTD6API::StringUtils::toString(groups[k]->fields.bloon) << " > ";
				groups[k]->fields.bloon = (String*)il2cpp_string_new(promoteBloon(BTD6API::StringUtils::toString(groups[k]->fields.bloon)).c_str());
				std::cout << BTD6API::StringUtils::toString(groups[k]->fields.bloon) << std::endl;
			}
			std::cout << "\n\n\n";
		}
	}
	std::cout << "Patched all default/alternate rounds!" << std::endl;
}