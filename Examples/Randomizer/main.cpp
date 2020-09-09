// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch.hpp"
#include <random>
#include <chrono>

using namespace app;

enum RandomType {
    RANDOM_UNIFORM = 0,
    RANDOM_NORMAL = 1
};

template<typename T>
struct RandBounds {
    union {
        T m_min;
        T m_mean;
    };
    union {
        T m_max;
        T m_stand_dev;
    };
};

int64_t g_seed = 0;

template<typename T>
class Rand {
public:
    int64_t m_seed;
    RandomType m_rand_t;
    std::default_random_engine m_generator;
    RandBounds<T> bounds;
    std::uniform_real_distribution<T> m_udist;
    std::normal_distribution<T> m_ndist;

    Rand(uint64_t seed = g_seed) { m_seed = seed; };

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

    T GetRand(T min_clamp = 0, T max_clamp = std::numeric_limits<T>::max()) {
        if (m_rand_t == RANDOM_UNIFORM) {
            m_udist = std::uniform_real_distribution<T>(bounds.m_min, bounds.m_max);
            T val = m_udist(m_generator);
            return clampVal(val, min_clamp, max_clamp);
        }
        else if (m_rand_t == RANDOM_NORMAL) {
            m_ndist = std::normal_distribution<T>(bounds.m_mean, bounds.m_stand_dev);
            T val = m_ndist(m_generator);
            return clampVal(val, min_clamp, max_clamp);
        }
        else {
            throw std::exception("Get Rand has invalid type!");
        }
    }

    void GetBounds(T min_clamp = 0, T max_clamp = std::numeric_limits<T>::max()) {
        std::string min;
        std::string max;
        if (m_rand_t == RANDOM_UNIFORM) {
            std::cout << "Enter a minimum value" << std::endl;
        }
        else if (m_rand_t == RANDOM_NORMAL) {
            std::cout << "Enter the Mean value" << std::endl;
        }
        
        for (;;) {
            std::cin >> min;
            try {
                bounds.m_min = static_cast<T>(std::stod(min));
                bounds.m_min = clampVal(bounds.m_min, min_clamp, max_clamp);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid number" << std::endl;
                continue;
            }
        }

        if (m_rand_t == RANDOM_UNIFORM) {
            std::cout << "Enter a maxmimum value" << std::endl;
        }
        else if (m_rand_t == RANDOM_NORMAL) {
            std::cout << "Enter the standard deviation" << std::endl;
        }

        for (;;) {
            std::cin >> max;
            try {
                bounds.m_max = static_cast<T>(std::stod(max));
                bounds.m_max = clampVal(bounds.m_max, min_clamp, max_clamp);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid number" << std::endl;
                continue;
            }
        }

    }

    void GetDistribution() {
        std::cout << "Default: (1) Uniform Distribution" << std::endl;
        std::cout << "(1) Uniform Distribution" << std::endl;
        std::cout << "(2) Normal Distribution" << std::endl;

        std::string strDist;

        for (;;) {
            int64_t temp_val;
            std::getline(std::cin, strDist);
            if (strDist == "") {
                std::cout << "Empty distribution entered, using default" << std::endl;
                m_rand_t = RANDOM_UNIFORM;
                break;
            }     
            try {
                temp_val = std::stoll(strDist);
                if (temp_val < 1 || temp_val > 2) {
                    throw std::exception();
                }
                m_generator = std::default_random_engine(m_seed);
                m_rand_t = (RandomType)(temp_val - 1);
                break;
            }
            catch (std::exception e) {
                std::cout << "Please enter a valid distribution" << std::endl;
                continue;
            }
        }
    }


};

bool promptIsMultiply() {
    std::cout << "Default: (1) set" << std::endl;
    std::cout << "(1) Set (speed = r). R of 5 means speed of 5" << std::endl;
    std::cout << "(2) Multiplied (speed *= r) If R=5 and speed=2, then output is 10" << std::endl;

    std::string strDist;

    for (;;) {
        int64_t temp_val;
        std::getline(std::cin, strDist);
        if (strDist == "") {
            std::cout << "Empty option entered, using default" << std::endl;
            return false;
        }
        try {
            temp_val = std::stoll(strDist);
            if (temp_val < 1 || temp_val > 2) {
                throw std::exception();
            }
            return (bool)(temp_val - 1);
        }
        catch (std::exception e) {
            std::cout << "Please enter a valid value" << std::endl;
            continue;
        }
    }
}

const float BLOON_MIN_SPEED = 0.05;

void RandomizeBloonSpeeds(GameModel* gmdl) {

    std::cout << "Do you want your bloon speeds to be set to their random values, or multuplied?" << std::endl;
    bool isMultiply = promptIsMultiply();
    Rand<float> rand;
    std::cout << "How do you want your bloon speeds to be distributed?" << std::endl;
    rand.GetDistribution();
    std::cout << "What do you want your bounds to be?" << std::endl;
    rand.GetBounds(BLOON_MIN_SPEED);

    BloonModel__Array* bloonModelArr = gmdl->fields.bloons;
    BloonModel** bloonModels = bloonModelArr->vector;

    for (int i = 0; i < bloonModelArr->max_length; ++i)
    {
        if (bloonModels[i] != NULL)
        {
            if (bloonModels[i]->fields.display != NULL) {
                float oldSpeed = bloonModels[i]->fields.speed;
                if (isMultiply) {
                    bloonModels[i]->fields.speed = rand.GetRand(BLOON_MIN_SPEED);
                }
                else {

                }
                //wchar_t* display = (wchar_t*)(&bloonModels[i]->fields.display->fields.m_firstChar);
                // This is broken for some reason
                std::wcout << "Speed was: " << oldSpeed << ", Speed now is: " << bloonModels[i]->fields.speed << std::endl;
            }
        }
    }

    std::cout << "Speedy Bloons sucesfully changed bloons speed!" << std::endl;
}



void RandomizeGameModel(GameModel* gmdl, const std::string& where)
{
    std::cout << "Randomizer Initialized!" << std::endl;
    std::cout << "Using  (" << where << ")" << "model" << std::endl;

    std::string strSeed;
    

    std::cout << "Please enter a seed (" << 
        std::numeric_limits<decltype(g_seed)>::min() << "-" << 
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

    std::string opt = "";
    std::cout << "Do you want to Randomize bloons speeds? (Y/N)" << std::endl;
    std::cin >> opt;
    if (opt == "Y" || opt == "y") {
        std::cout << "Randomizing Bloon Speeds!" << std::endl;
        RandomizeBloonSpeeds(gmdl);
    }

    std::cout << "Randomizing Bloon Speeds!" << g_seed << std::endl;

    

    //TowerModel__Array* towersArr = gmdl->fields.towers;
    //TowerModel** towers = towersArr->vector;

    //for (int i = 0; i < towersArr->max_length; ++i)
    //{
    //    if (towers[i]->fields.display != NULL)
    //    {
    //        makeTowerHypersonic(towers[i]);
    //    }
    //}
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