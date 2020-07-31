// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "../../il2cpp/il2cpp-init.h"
#include "helpers.h"
#include <iostream>
#include <discord_rpc.h>
#include <codecvt>
#include <locale>
#include <regex>

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

static void updatePresence(int32_t selectedCoopPlayerCount, std::string selectedDifficulty, std::string selectedMap, std::string selectedMode)
{
	std::string details = "Cruising around the menus", state = "";

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

		details = "Playing " + std::regex_replace(selectedMap, std::regex("(\\B[A-Z]+?(?=[A-Z][^A-Z])|\\B[A-Z]+?(?=[^A-Z]))"), " $1"); // ya ik std::regex cring but this seems to be best way to split PascalCase into separate words (required for map names and mode names)
		if (selectedCoopPlayerCount > 0)
		{
			details += " with " + std::to_string(selectedCoopPlayerCount - 1) + " other people";
		}

		state = selectedDifficulty + ", " + std::regex_replace(selectedMode, std::regex("(\\B[A-Z]+?(?=[A-Z][^A-Z])|\\B[A-Z]+?(?=[^A-Z]))"), " $1"); // same std::regex as last one

		transform(selectedMap.begin(), selectedMap.end(), selectedMap.begin(), ::tolower); // change selectedMap to lower so we can get image key from discord
		discordPresence.largeImageKey = std::regex_replace("mapselect" + selectedMap + "button", std::regex("[$ & +, :; = ? @# | '<>.-^*()%!]"), "_").c_str(); // the std::regex for this one replaces all special characters with _; this is the same regex discord uses for image keys
		discordPresence.smallImageKey = "logo";
	} // if selectedDifficulty, selectedMap, and selectedMode are not empty, construct a rich presence; large image of map, small image of btd6 logo, details saying map you're playing and difficulty+mode
	else
	{
		discordPresence.largeImageKey = "logo";
		discordPresence.smallImageKey = "";
	} // if the condition doesn't pass, do rich presence differently; large image of btd6 logo, no small image key. details will be the default "Cruising around the menus" (should be in menus if the aforementioned strings are empty)

	discordPresence.details = details.c_str();
	discordPresence.state = state.c_str();
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

	const Il2CppAssembly* assembly = nullptr;
	for (auto i = 0; i < size; ++i)
	{
		if (std::string(assemblies[i]->aname.name) == "Assembly-CSharp")
		{
			std::cout << "Found assembly!" << std::endl;
			assembly = assemblies[i];
		}
	}

	if (assembly == nullptr)
	{
		std::cout << "Error: Assembly-CSharp not found." << std::endl;
		return;
	}

	while (true)
	{
		Il2CppClass* inGameClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity.UI_New.InGame", "InGame");
		FieldInfo* instance = il2cpp_class_get_field_from_name(inGameClass, "instance");

		InGame* inGameInstAddr = 0;
		il2cpp_field_static_get_value(instance, &inGameInstAddr);
		if (inGameInstAddr != NULL)
		{
			InGame* inGame = (InGame*)(inGameInstAddr);
			Helpers_InGameData inGameData = inGame->fields.inGameData;
			// set up parameters for presence
			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;

			int32_t selectedCoopPlayerCount = inGameData.selectedCoopPlayerCount;
			std::string selectedDifficulty = converter.to_bytes(std::wstring((wchar_t*)(&inGameData.selectedDifficulty->fields.m_firstChar)));
			std::string selectedMap = converter.to_bytes(std::wstring((wchar_t*)(&inGameData.selectedMap->fields.m_firstChar)));
			std::string selectedMode = converter.to_bytes(std::wstring((wchar_t*)(&inGameData.selectedMode->fields.m_firstChar)));
			// make presence
			updatePresence(selectedCoopPlayerCount, selectedDifficulty, selectedMap, selectedMode);
		}
		else
		{
			updatePresence(-1, "", "", "");
		}

#ifdef DISCORD_DISABLE_IO_THREAD
		Discord_UpdateConnection();
#endif
		Discord_RunCallbacks();

		Sleep(15000);
	}
	Discord_Shutdown();
}