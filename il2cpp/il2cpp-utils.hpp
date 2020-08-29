#include "il2cpp-init.h"
#include <string>
#include <codecvt>
#include <iostream>

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
	
	class KonFuze
	{
	public:
		static double get_Value(Il2CppClass* konfuzeClass, app::KonFuze* konfuzeObj)
		{
			const MethodInfo* _method = il2cpp_class_get_method_from_name(konfuzeClass, "get_Value", 0);
			if (_method != nullptr)
			{
				return Assembly::callFunction<double>(_method, konfuzeObj, (MethodInfo*)_method);
			}
		}
		
		static void set_Value(Il2CppClass* konfuzeClass, app::KonFuze* konfuzeObj, double val)
		{
			const MethodInfo* _method = il2cpp_class_get_method_from_name(konfuzeClass, "Write", 1);
			if (_method != nullptr)
			{
				Assembly::callFunction<void>(_method, konfuzeObj, val, (MethodInfo*)_method);
			}
		}
	};

	class StringUtils
	{
	public:
		static std::wstring toWideString(app::String* str)
		{
			std::wstring wString;
			if (str == NULL) {
				wString = L"NULL";
			}
			else {
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
	struct Array {
		template<typename T>
		static void resize(T& src, size_t newsize) {
			
			// Allocate new array
			Il2CppArray* dst = il2cpp_array_new((Il2CppClass*)(src->vector[0]->klass), newsize);

			size_t dst_sz = sizeof(dst->vector[0]) * dst->max_length;
			size_t src_sz = sizeof(src->vector[0]) * src->max_length;

			// Copy the contents of the array
			memcpy_s(dst->vector, dst_sz, src->vector, src_sz);

			//FIXME: This function may memory leak, not sure how GC works.
			//il2cpp_free(src->vector);

			// Change the pointer
			src = (T)dst;
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