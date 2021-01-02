#pragma once
#include "ClassData.h"
#include "Void/Core/Log.h"


//There has to be a way to get file name at compile time and use it as a typename
#define REGISTER_CLASS(Type) static ClassRegistryHelper<class Type> ClassRegistryHelper##Type

template<typename T>
struct ClassRegistryHelper
{
	ClassRegistryHelper()
	{
		printf("Registering: %s \n", typeid(T).name());
		ClassRegistry::Register<T>();
	}
};

class ClassRegistry
{

public:

	template<typename T>
	static void Register()
	{
		ClassData<T>* RegisteredClass = new ClassData<T>();

		(*GetClassRegistryMap())[typeid(T).name()] = UniqueRef<ClassData<T>>(RegisteredClass);
	}

	static ClassHandle* GetClass(const std::string& Name)
	{
		std::unordered_map<std::string, UniqueRef<ClassHandle>>* ClassRegistryMap = GetClassRegistryMap();
		VD_CORE_ASSERT_CUSTOM(ClassRegistryMap->find(Name) != ClassRegistryMap->end(), VD_CORE_CRITICAL("Retreiving unregistered class {0}", Name));
		return (*ClassRegistryMap)[Name].get();
	}

	static std::vector<ClassHandle*> GetRegisteredClasses()
	{
		std::vector<ClassHandle*> RegisteredClasses;

		for (auto& A : *GetClassRegistryMap())
		{
			RegisteredClasses.push_back(A.second.get());
		}

		return RegisteredClasses;
	}


	static std::unordered_map<std::string, UniqueRef<ClassHandle>>* GetClassRegistryMap()
	{
		static std::unordered_map<std::string, UniqueRef<ClassHandle>>* ClassRegistryMap = new std::unordered_map<std::string, UniqueRef<ClassHandle>>();
		return ClassRegistryMap;
	}
};