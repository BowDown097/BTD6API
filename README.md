# BTD6API
An API allowing you to develop BTD6 mod tools.
<p align="center">
    <a alt="Downloads">
        <!-- put release downloads shield here -->
    <a href="https://discord.gg/nuMvgkP" alt="Discord">
        <img src="https://img.shields.io/discord/504782676331331584" /></a>
</p>

## Dependencies
This project's IL2CPP modding functionality depends on [Il2CppInspector.](https://github.com/djkaty/Il2CppInspector)
## How to use in your project
- Click "Clone or download," and then "Open in Visual Studio" (if available) or "Download ZIP" if the aforementioned option is not available. Then, build the project. Alternatively, you can use the pre-built DLL in Releases. Afterwards, simply include the DLL in your project (if you don't know how to, [see here to learn how to do it in Visual Studio.](https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2019#create-a-client-app-that-uses-the-dll))
- To begin developing your mod, I recommend duplicating one of the mods in the Examples folder. All mods, including the ones in the Examples folder, should follow this format in main.cpp:
  ```cpp
  #include "il2cpp/il2cpp.hpp"
  #include "helpers.h"
  #include <iostream>
  
  using namespace app;
  
  extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";
  
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
	
	// your code goes here
  }
  ```
- And that is all! You can use the Wiki or the examples in the Examples folder to learn what to do from here.