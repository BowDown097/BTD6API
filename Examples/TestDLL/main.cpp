// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "../../il2cpp/il2cpp-init.h"
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

    std::cout << "Initializing sauce\n";

    size_t size = 0;
    const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(nullptr, &size);

    const Il2CppAssembly* CSharpAssembly = nullptr;
    for (auto i = 0; i < size; ++i)
    {
        if (std::string(assemblies[i]->aname.name) == "Assembly-CSharp")
        {
            std::cout << "Found assembly!";
            CSharpAssembly = assemblies[i];
        }
    }

    if (CSharpAssembly == nullptr)
    {
        std::cout << "Error! CSharpAssembly not found!";
        return;
    }

    Il2CppClass* towerSelectKlass = il2cpp_class_from_name(CSharpAssembly->image, "Assets.Scripts.Unity.UI_New.InGame.TowerSelectionMenu", "TowerSelectionMenu");
    FieldInfo* instance = il2cpp_class_get_field_from_name(towerSelectKlass, "instance");
    TowerSelectionMenu* towerSelectInstAddr = 0;
    il2cpp_field_static_get_value(instance, &towerSelectInstAddr);

    if (towerSelectInstAddr == NULL)
    {
        std::cout << "Some error occurred when trying to access the tower selection menu.";
        return;
    }

    TowerSelectionMenu* towerSelect = (TowerSelectionMenu*)(towerSelectInstAddr);

    UpgradeObject__Array* upgradeButtonsArr = towerSelect->fields.upgradeButtons;
    UpgradeObject** upgradeButtons = upgradeButtonsArr->vector;

    for (int i = 0; i < upgradeButtonsArr->max_length; ++i)
    {
        std::cout << "Found UpgradeObject in TowerSelectionMenu with buttonID " << upgradeButtons[i]->fields.buttonID << std::endl;
        upgradeButtons[i]->fields.upgradeButton->fields.upgradeStatus = UpgradeButton_UpgradeStatus__Enum_Purchasable;
        upgradeButtons[i]->fields.upgradeButton->fields.upgradeCost = 0.0f;
    }
}