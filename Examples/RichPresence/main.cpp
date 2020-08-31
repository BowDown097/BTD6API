// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"
#include <discord_rpc.h>
#include <regex>

using namespace app;

static void updatePresence(int selectedCoopPlayerCount, int currentRound, int health, int cash, std::string selectedDifficulty, std::string selectedMap, std::string selectedMode)
{
	std::string details = "Cruising around the menus", state = "", largeImageText = "";
	std::regex pascalSplit("(\\B[A-Z]+?(?=[A-Z][^A-Z])|\\B[A-Z]+?(?=[^A-Z]))"); // ya ik std::regex cring
	std::regex removeSpecialChar("[$ & +, :; = ? @# | '<>.-^*()%!]");

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	if (!selectedDifficulty.empty() && !selectedMap.empty() && !selectedMode.empty())
	{
		if (selectedMode == "Clicks")
		{
			selectedMode = "CHIMPS";
		} // difficulty still has the old Clicks name, change to CHIMPS
		if (selectedMap == "Tutorial")
		{
			selectedMap = "MonkeyMeadow";
		} // change Tutorial (Monkey Meadow's internal name) to MonkeyMeadow

		details = "Playing " + std::regex_replace(selectedMap, pascalSplit, " $1");
		if (selectedCoopPlayerCount > 0)
		{
			details += " with " + std::to_string(selectedCoopPlayerCount - 1) + " other people";
		}

		state = "Round " + std::to_string(currentRound + 1) + ", $" + std::to_string(cash) + ", " + std::to_string(health) + " Lives";
		largeImageText = selectedDifficulty + ", " + std::regex_replace(selectedMode, pascalSplit, " $1");

		transform(selectedMap.begin(), selectedMap.end(), selectedMap.begin(), ::tolower); // change selectedMap to lower so we can get image key
		discordPresence.largeImageKey = std::regex_replace("mapselect" + selectedMap + "button", removeSpecialChar, "_").c_str(); // the std::regex for this one replaces all special characters with _; this is the same regex discord uses for image keys
		discordPresence.smallImageKey = "logo";
	} // if player if fully in-game, RP = large image of map (tooltip of difficulty), small image of btd6 logo, details = map, state = round, lives, and cash
	else
	{
		discordPresence.largeImageKey = "logo";
		discordPresence.smallImageKey = "";
	} // if the condition doesn't pass, RP = large image of btd6 logo, details will be "Cruising around the menus"

	discordPresence.details = details.c_str();
	discordPresence.state = state.c_str();
	discordPresence.largeImageText = largeImageText.c_str();
	discordPresence.instance = 0;
	Discord_UpdatePresence(&discordPresence);
}

static void initDiscord()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));

	Discord_Initialize("465015294122000387", &handlers, 1, NULL);
}

// Injected code entry point
void Run()
{
	initDiscord();

	std::cout << "Initializing..." << std::endl;

	size_t size = 0;
	const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(nullptr, &size);

	const Il2CppAssembly* assembly = BTD6API::Assembly::get(assemblies, "Assembly-CSharp", size);

	if (assembly == nullptr)
	{
		std::cout << "Error: Assembly-CSharp not found." << std::endl;
		return;
	}

	while (true)
	{
		Il2CppClass* inGameClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity.UI_New.InGame", "InGame");
		Il2CppClass* konfuzeClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Utils", "KonFuze");
		FieldInfo* instance = il2cpp_class_get_field_from_name(inGameClass, "instance");

		InGame* inGameInstAddr = 0;
		il2cpp_field_static_get_value(instance, &inGameInstAddr);
		if (inGameInstAddr != NULL)
		{
			InGame* inGame = (InGame*)(inGameInstAddr);
			Helpers_InGameData inGameData = inGame->fields.inGameData;
			Simulation* simulation = inGame->fields.bridge->fields.simulation;
			Spawner* spawner = simulation->fields.map->fields.spawner;
			if (spawner != NULL)
			{
				// parameters for rich presence
				Simulation_CashManager* cashManager = simulation->fields.cashManagers->fields.entries->vector[0].value;
				if (cashManager != NULL)
				{
					// get konfuze values (current round, health, cash)
					double cash = BTD6API::KonFuze::get_Value(assembly->image, cashManager->fields.cash);
					double currentRound = BTD6API::KonFuze::get_Value(assembly->image, spawner->fields.currentRound);
					double lives = BTD6API::KonFuze::get_Value(assembly->image, simulation->fields.health);
					// get in-game data
					int selectedCoopPlayerCount = inGameData.selectedCoopPlayerCount;
					std::string selectedDifficulty = BTD6API::StringUtils::toString(inGameData.selectedDifficulty);
					std::string selectedMap = BTD6API::StringUtils::toString(inGameData.selectedMap);
					std::string selectedMode = BTD6API::StringUtils::toString(inGameData.selectedMode);
					updatePresence(selectedCoopPlayerCount, currentRound, lives, cash, selectedDifficulty, selectedMap, selectedMode);
				}
			}
		}
		else
		{
			updatePresence(-1, -1, -1, -1, "", "", "");
		}

#ifdef DISCORD_DISABLE_IO_THREAD
		Discord_UpdateConnection();
#endif
		Discord_RunCallbacks();

		Sleep(15000);
	}
	Discord_Shutdown();
}