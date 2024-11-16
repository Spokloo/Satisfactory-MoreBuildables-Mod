// Fill out your copyright notice in the Description page of Project Settings.

#include "MoreBuildables_BuildableLib.h"

DEFINE_LOG_CATEGORY(LogMoreBuildables_BuildableLib);

void UMoreBuildables_BuildableLib::UnlockingMaterialUnlocksBuildable(TArray<UFGSchematic*> materials, TArray<TSubclassOf<UFGSchematic>> cbg_schematics)
{
	for (size_t i = 0; i < materials.Num(); i++)
	{
		UFGUnlockSchematic* unlockSchematics = (UFGUnlockSchematic*) materials[i]->GetmUnlocks()[1];
		if (unlockSchematics == nullptr)
		{
			UE_LOG(LogMoreBuildables_BuildableLib, Error, TEXT("Could not cast 'mUnlocks' property of UFGSchematic '%s' to UFGUnlockSchematic."), *(materials[i]->GetName()));
		}
		else
		{
			TArray<TSubclassOf<UFGSchematic>> _mSchematics = unlockSchematics->GetmSchematics();
			_mSchematics.Add(cbg_schematics[i]);
			unlockSchematics->SetmSchematics(_mSchematics);
		}
	}
}

void UMoreBuildables_BuildableLib::MaterialSwatchAffectsBuildable(TArray<FRecipeMaterialStruct> recipes_array, TArray<FBuildMaterialStruct> builds_array)
{
	for (size_t i = 0; i < recipes_array.Num(); i++)
	{
		TMap<TSubclassOf<AFGBuildable>, TSubclassOf<UFGRecipe>> _mBuildableMap = recipes_array[i].material_desc->GetmBuildableMap();
		for (size_t j = 0; j < recipes_array[i].recipes.Num(); j++)
		{
			for (size_t k = 0; k < builds_array.Num(); k++)
			{
				if (builds_array[k].material_desc != recipes_array[i].material_desc)
					_mBuildableMap.Add(builds_array[k].builds[j], recipes_array[i].recipes[j]);
			}
		}

		recipes_array[i].material_desc->SetmBuildableMap(_mBuildableMap);
	}
}
