// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "PolyTerrainGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePolyTerrainGameModeBase() {}
// Cross Module References
	POLYTERRAIN_API UClass* Z_Construct_UClass_APolyTerrainGameModeBase_NoRegister();
	POLYTERRAIN_API UClass* Z_Construct_UClass_APolyTerrainGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_PolyTerrain();
// End Cross Module References
	void APolyTerrainGameModeBase::StaticRegisterNativesAPolyTerrainGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_APolyTerrainGameModeBase_NoRegister()
	{
		return APolyTerrainGameModeBase::StaticClass();
	}
	UClass* Z_Construct_UClass_APolyTerrainGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AGameModeBase,
				(UObject* (*)())Z_Construct_UPackage__Script_PolyTerrain,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
				{ "IncludePath", "PolyTerrainGameModeBase.h" },
				{ "ModuleRelativePath", "PolyTerrainGameModeBase.h" },
				{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
			};
#endif
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<APolyTerrainGameModeBase>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&APolyTerrainGameModeBase::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900288u,
				nullptr, 0,
				nullptr, 0,
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(APolyTerrainGameModeBase, 1170994934);
	static FCompiledInDefer Z_CompiledInDefer_UClass_APolyTerrainGameModeBase(Z_Construct_UClass_APolyTerrainGameModeBase, &APolyTerrainGameModeBase::StaticClass, TEXT("/Script/PolyTerrain"), TEXT("APolyTerrainGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(APolyTerrainGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
