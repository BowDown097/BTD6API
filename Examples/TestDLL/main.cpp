// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"
#include <fstream>

void makeHypersonic(GameModel* gmdl, const std::string& where) {

    try {
        size_t size = 0;
        const Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(nullptr, &size);

        const Il2CppAssembly* assembly = BTD6API::Assembly::get(assemblies, "Assembly-CSharp", size);

        if (assembly == nullptr)
        {
            std::cout << "Error: Assembly-CSharp not found." << std::endl;
            return;
        }


        Il2CppClass* ShoptowersClass = il2cpp_class_from_name(assembly->image, "Assets.Scripts.Unity.UI_New.InGame.RightMenu", "ShopMenu");
        FieldInfo* shoptowersfield = il2cpp_class_get_field_from_name(ShoptowersClass, "instance");
        const MethodInfo* _method12 = il2cpp_class_get_method_from_name(ShoptowersClass, "CreateTowerButton", 3);//TowerPurchaseButton *, ShopMenu_CreateTowerButton, (ShopMenu * __this, TowerModel * model, int32_t buttonIndex, bool showTowerCounts, MethodInfo * method));
        TowerPurchaseButton* (*createbutton)(ShopMenu*, TowerModel*, int32_t, bool, MethodInfo*) = (TowerPurchaseButton * (*)(ShopMenu*, TowerModel*, int32_t, bool, MethodInfo*)) _method12->methodPointer;
        ShopMenu* sm = 0;
        il2cpp_field_static_get_value(shoptowersfield, &sm);

        std::cout << "Current button count: " << sm->fields.buttonCount << std::endl;

        sm->fields.buttonCount++;
        TowerPurchaseButton* eee = createbutton(sm, (TowerModel*)gmdl->fields.towerSet->vector[0], sm->fields.buttonCount - 1, false, (MethodInfo*)_method12);
    }
    catch (Il2CppExceptionWrapper e) {
        std::wcout << L"Il2cppException occurred:" << (wchar_t*)(e.ex->message->chars) << std::endl;
    }


}


using namespace app;
// Injected code entry point
void Run()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    Il2CppThread* thread = il2cpp_thread_attach(il2cpp_domain_get());

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
        makeHypersonic(inGameInstance->fields.bridge->fields.simulation->fields.model, "in-game");
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
    makeHypersonic(gameInstance->fields.model, "game");
}