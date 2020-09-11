// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace app;

//
// Randomizer mod
// Randomizes Bloon speeds
//

int64_t g_seed = 0;

enum DistType : uint8_t {
    RANDOM_UNIFORM = 0,
    RANDOM_NORMAL = 1
};

enum OpType : uint8_t {
    OP_SET = 0,
    OP_MULTIPLY = 1,
    OP_ADD = 2
};

template<typename T>
struct RandBounds {
    T min;
    T max;
};

template<typename T>
struct RandStuff {
    std::default_random_engine generator;
    std::uniform_real_distribution<T> udist;
    std::normal_distribution<T> ndist;
};

template<typename T>
struct Opt {
    bool isEnabled;
    DistType t;
    RandBounds<T> bounds;
    OpType op_t;

    T clampVal(T val, T min_clamp, T max_clamp) {
        if (val < min_clamp) {
            std::cout << "Clamping " << val << " to " << min_clamp << std::endl;
            val = min_clamp;
        }
        if (val > max_clamp) {
            std::cout << "Clamping " << val << " to " << max_clamp << std::endl;
            val = max_clamp;
        }
        return val;
    }

#pragma region Prompts
    void promptRandomization(const char* s) {
        std::string strOpt = "";
        std::cout << "Do you want to Randomize " << s << " ? (Y/N)" << std::endl;
        std::cin >> strOpt;
        if (strOpt == "Y" || strOpt == "y") {
            std::cout << "Randomizing " << s << " Bloon Speeds!" << std::endl;
            isEnabled = true;
            return;
        }
        isEnabled = false;
    }

    void promptBounds(T min_clamp = 0, T max_clamp = std::numeric_limits<T>::max()) {
        std::string min;
        std::string max;
        if (t == RANDOM_UNIFORM) {
            std::cout << "What do you want the min and max of the distrubtion to be?" << std::endl;
            std::cout << "Enter a minimum value" << std::endl;
        }
        else if (t == RANDOM_NORMAL) {
            std::cout << "What do you want the mean and sigma of the distrubtion to be?" << std::endl;
            std::cout << "Enter the Mean value" << std::endl;
        }

        for (;;) {
            std::cin >> min;
            try {
                if (sizeof(T) == 8) {
                    // stod is probably bad, but it works
                    double tempval = std::stod(min);
                    bounds.min = static_cast<T>(tempval);
                }
                else if (sizeof(T) == 4) {
                    float tempval = std::stof(min);
                    bounds.min = static_cast<T>(tempval);
                }
                else {
                    std::cout << "Invalid size!" << std::endl;
                }

                bounds.min = clampVal(bounds.min, min_clamp, max_clamp);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid number" << std::endl;
                continue;
            }
        }

        if (t == RANDOM_UNIFORM) {
            std::cout << "Enter a maxmimum value" << std::endl;
        }
        else if (t == RANDOM_NORMAL) {
            std::cout << "Enter the standard deviation" << std::endl;
        }

        for (;;) {
            std::cin >> max;
            try {
                if (sizeof(T) == 8) {
                    // stod is probably bad, but it works
                    double tempval = std::stod(max);
                    bounds.max = static_cast<T>(tempval);
                }
                else if (sizeof(T) == 4) {
                    float tempval = std::stof(max);
                    bounds.max = static_cast<T>(tempval);
                }
                else {
                    std::cout << "Invalid size!" << std::endl;
                }
                bounds.max = clampVal(bounds.max, min_clamp, max_clamp);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid number" << std::endl;
                continue;
            }
        }

    }

    void promptDistribution() {
        std::cout << "How do you want your random values to be distributed?" << std::endl;
        std::cout << "Default: (1) Uniform Distribution" << std::endl;
        std::cout << "(1) Uniform Distribution" << std::endl;
        std::cout << "(2) Normal Distribution" << std::endl;

        std::string strDist;

        for (;;) {
            int64_t temp_val;
            std::getline(std::cin, strDist);
            if (strDist == "") {
                std::cout << "Empty distribution entered, using default" << std::endl;
                t = RANDOM_UNIFORM;
                break;
            }
            try {
                temp_val = std::stoll(strDist);
                if (temp_val < 1 || temp_val > 2) {
                    throw std::exception();
                }
                t = (DistType)(temp_val - 1);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid distribution" << std::endl;
                continue;
            }
        }
    }

    void promptOp() {
        std::cout << "What operator do you want to have applied to your random values?" << std::endl;
        std::cout << "Default: (1) Set" << std::endl;
        std::cout << "(1) Set (speed = r). R of 5 means speed of 5" << std::endl;
        std::cout << "(2) Multiplied (speed *= r) If R=5 and speed=2, then output is 10" << std::endl;
        std::cout << "(3) Add (speed += r) If R=5 and speed=2, then output is 7 (Supports negatives!)" << std::endl;

        std::string strOp;

        for (;;) {
            int64_t temp_val;
            // WHy 2????
            std::getline(std::cin, strOp);
            std::getline(std::cin, strOp);
            if (strOp == "") {
                std::cout << "Empty option entered, using default" << std::endl;
                op_t = OP_SET;
                break;
            }
            try {
                temp_val = std::stoll(strOp);
                if (temp_val < 1 || temp_val > 3) {
                    std::cout << "Please enter a valid value" << std::endl;
                    continue;
                }
                op_t = (OpType)(temp_val - 1);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid value" << std::endl;
                continue;
            }
        }
    }
#pragma endregion

    T doOp(T& a, T b) {
        switch (op_t) {
        case OP_SET:
            a = b;
            break;
        case OP_MULTIPLY:
            return a *= b;
            break;
        case OP_ADD:
            return a += b;
            break;
        default:
            std::cout << "Oophsie Whoopsie when choosing operator.";
            return 0;
        }
    }

    RandStuff<T>* r;

    Opt() { r = new RandStuff<T>; r->generator = std::default_random_engine(g_seed); };
    ~Opt() { delete r; }

    T GetRand(T min_clamp = 0, T max_clamp = std::numeric_limits<T>::max()) {
        if (t == RANDOM_UNIFORM) {
            r->udist = std::uniform_real_distribution<T>(bounds.min, bounds.max);
            T val = r->udist(r->generator);
            return clampVal(val, min_clamp, max_clamp);
        }
        else if (t == RANDOM_NORMAL) {
            r->ndist = std::normal_distribution<T>(bounds.min, bounds.max);
            T val = r->ndist(r->generator);
            return clampVal(val, min_clamp, max_clamp);
        }
        else {
            throw std::exception("Get Rand has invalid type!");
        }
    }
};

struct Options {
    size_t seed;

    Opt<float> BloonSpeeds;
    Opt<float> FireRate;

    Options* fromString(std::string s) {
        if (s.length() % 2 != 0) {
            std::cout << "Error! String was not valid" << std::endl;
        }

        Options* ret = new Options;

        for (auto i = 0; i < s.length(); i += 2) {
            reinterpret_cast<uint8_t*>(ret)[i] = static_cast<uint8_t>(std::stoi(std::string("" + s[i])));
            reinterpret_cast<uint8_t*>(ret)[i + 1] = static_cast<uint8_t>(std::stoi(std::string("" + s[i + 1])));
        }

        return ret;
    }

    std::string toString(Options* opt) {
        std::stringstream ss;
        ss << std::hex;

        for (auto i = 0; i < sizeof(Options); ++i) {
            ss << std::setw(2) << std::setfill('0') << (int)(reinterpret_cast<uint8_t*>(opt))[i];
        }

        return ss.str();
    }
};

const float BLOON_MIN_SPEED = 0.05;

void RandomizeBloonSpeeds(GameModel* gmdl, Options& opt) {
    opt.BloonSpeeds.promptOp();
    opt.BloonSpeeds.promptDistribution();
    opt.BloonSpeeds.promptBounds();

    BloonModel__Array* bloonModelArr = gmdl->fields.bloons;
    BloonModel** bloonModels = bloonModelArr->vector;

    for (int i = 0; i < bloonModelArr->max_length; ++i)
    {
        if (bloonModels[i] != NULL)
        {
            if (bloonModels[i]->fields.display != NULL) {
                float oldSpeed = bloonModels[i]->fields.speed;
                opt.BloonSpeeds.doOp(bloonModels[i]->fields.speed, opt.BloonSpeeds.GetRand(BLOON_MIN_SPEED));
                //wchar_t* display = (wchar_t*)(&bloonModels[i]->fields.display->fields.m_firstChar);
                // This is broken for some reason
                std::wcout << "Speed was: " << oldSpeed << ", Speed now is: " << bloonModels[i]->fields.speed << std::endl;
            }
        }
    }

    std::cout << "Speedy Bloons sucesfully changed bloons speed!" << std::endl;
}

//
// Randomize stuff yoinked from hypersonic
//

void RandomizeWeaponRate(AttackModel* attack, Options& opt) {
    WeaponModel__Array* weaponsArr = attack->fields.weapons;
    WeaponModel** weapons = weaponsArr->vector;

    for (int k = 0; k < weaponsArr->max_length; ++k)
    {
        WeaponModel* weapon = weapons[k];

        if (weapon != NULL)
        {
            float oldSpeed = weapon->fields.rate;
            opt.FireRate.doOp(weapon->fields.rate, opt.FireRate.GetRand());

           // std::wcout << "Speed was: " << oldSpeed << ", Speed now is: " << weapon->fields.rate << std::endl;
        }
    }
}

void RandomizeTowerRate(TowerModel* tmdl, Options& opt) {
    Model__Array* modelsArr = tmdl->fields.behaviors;
    Model** models = modelsArr->vector;
    if (models != NULL)
    {
        for (int i = 0; i < modelsArr->max_length; ++i)
        {
            Model* model = models[i];
            if (model != NULL && model->fields.name != NULL)
            {

                std::wstring name = BTD6API::StringUtils::toWideString(model->fields.name);

                // This hero works differently to literally everything else in the game.
                if (name.find(L"AbilityModel_UCAVAbility") != std::wstring::npos) {
                    AbilityModel* ab = (AbilityModel*)model;

                    for (int j = 0; j < ab->fields.behaviors->max_length; ++j) {
                        Model* bm = ab->fields.behaviors->vector[j];

                        std::wstring modelName = BTD6API::StringUtils::toWideString(bm->fields.name);

                        if (modelName.find(L"UCAVModel") != std::wstring::npos) {
                            UCAVModel* mdl = (UCAVModel*)(bm);
                            RandomizeTowerRate(mdl->fields.uavTowerModel, opt);
                            RandomizeTowerRate(mdl->fields.ucavTowerModel, opt);
                        }
                    }
                }

                if (name.find(L"DroneSupportModel") != std::wstring::npos) {
                    DroneSupportModel* dsm = (DroneSupportModel*)(model);
                    RandomizeTowerRate(dsm->fields.droneModel, opt);
                }

                if (name.find(L"AttackModel") != std::wstring::npos || name.find(L"AttackAirUnitModel") != std::wstring::npos)
                {
                    AttackModel* attack = (AttackModel*)model;
                    RandomizeWeaponRate(attack, opt);
                }
            }
        }
    }
}

void RandomizeTowerRate(GameModel* gmdl, Options& opt) {
    opt.FireRate.promptOp();
    opt.FireRate.promptDistribution();
    opt.FireRate.promptBounds();

    TowerModel__Array* towersArr = gmdl->fields.towers;
    TowerModel** towers = towersArr->vector;

    for (int i = 0; i < towersArr->max_length; ++i)
    {
        if (towers[i]->fields.display != NULL)
        {
            RandomizeTowerRate(towers[i], opt);
        }
    }
}


void RandomizeGameModel(GameModel* gmdl, const std::string& where)
{
    std::cout << "Randomizer Initialized!" << std::endl;
    std::cout << "Using  (" << where << ")" << "model" << std::endl;

    std::string strSeed;

    std::cout << "Please enter a seed (" <<
        std::numeric_limits<decltype(g_seed)>::min() << " - " <<
        std::numeric_limits<decltype(g_seed)>::max() << ")" << std::endl;

    for (;;) {
        std::getline(std::cin, strSeed);
        if (strSeed == "") {
            std::cout << "Empty seed entered, using system time!" << std::endl;
            g_seed = std::chrono::system_clock::now().time_since_epoch().count();
            break;
        }
        try {
            g_seed = std::stoll(strSeed);
            break;
        }
        catch (std::exception e) {
            std::cout << "Please enter a valid seed" << std::endl;
            continue;
        }
    }

    std::cout << "Seed is: " << g_seed << std::endl;

    Options opt = Options();
    opt.BloonSpeeds.promptRandomization("Bloon Speeds");
    if (opt.BloonSpeeds.isEnabled) {
        RandomizeBloonSpeeds(gmdl, opt);
    }

    opt.FireRate.promptRandomization("Fire rates");
    if (opt.FireRate.isEnabled) {
        RandomizeTowerRate(gmdl, opt);
    }

    std::cout << "Randomizing Bloon Speeds!" << g_seed << std::endl;

    //std::cout << "funny1" << sizeof(Options) << std::endl;
    //std::cout << "funny2: " << opt.toString(&opt) << std::endl;

}

// Injected code entry point
void Run()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

    std::cout << "Initializing Randomizer!" << std::endl;

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
        RandomizeGameModel(inGameInstance->fields.bridge->fields.simulation->fields.model, "in-game");
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
    RandomizeGameModel(gameInstance->fields.model, "game");

    //std::cout << "Randomizer Randomier succesfully!" << std::endl;

}