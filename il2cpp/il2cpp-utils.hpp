#include "il2cpp-init.h"
#include <string>
#include <codecvt>

namespace BTD6API
{
	class Assembly
	{
	public:
		static const Il2CppAssembly* get(const Il2CppAssembly** assemblies, const std::string& assemblyName, size_t size)
		{
			const Il2CppAssembly* assembly = nullptr;
			for (auto i = 0; i < size; ++i)
			{
				if (std::string(assemblies[i]->aname.name) == assemblyName)
				{
					assembly = assemblies[i];
				}
			}

			return assembly;
		}
		
		// from https://stackoverflow.com/a/46011055
		template <typename R, typename... Args>
		static R callFunction(const MethodInfo* method, Args... args)
		{
			if (method != nullptr)
			{
				typedef R(*Function)(Args...);
				Function fn = (Function)((void*)method->methodPointer);
				return fn(args...);
			}
		}
	};

	class StringUtils
	{
	public:
		static std::wstring toWideString(app::String* str)
		{
			std::wstring wString;
			if (str != NULL)
			{
				wString = std::wstring((wchar_t*)(&str->fields.m_firstChar));
			}
			return wString;
		}

		static std::string toString(app::String* str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
			return converter.to_bytes(toWideString(str));
		}
	};

	class ModelUtils
	{
	public:
		static Model* locateModel(Model__Array* modelsArr, std::wstring name)
		{
			Model* model = nullptr;
			Model** models = modelsArr->vector;
			if (models != NULL)
			{
				for (int i = 0; i < modelsArr->max_length; ++i)
				{
					Model* temp = models[i];

					if (temp != NULL && temp->fields.name != NULL)
					{
						if (StringUtils::toWideString(temp->fields.name).find(name) != std::wstring::npos)
						{
							model = temp;
						}
					}
				}
			}

			return model;
		}
	};

	class TowerUtils
	{
	public:
		static void patchTowerAttack(TowerModel* tower, AttackModel* attack)
		{
			Model__Array* modelsArr = tower->fields.behaviors;
			if (modelsArr != NULL)
			{
				Model** models = modelsArr->vector;
				for (int i = 0; i < modelsArr->max_length; ++i)
				{
					if (models[i] != NULL && models[i]->fields.name != NULL)
					{
						if (StringUtils::toWideString(models[i]->fields.name).find(L"AttackModel") != std::wstring::npos)
						{
							models[i] = (Model*)(attack);
						}
					}
				}
			}
		} // just the method declaration took over 20 minutes to type.. pizdec
	};
}