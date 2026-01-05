// Fill out your copyright notice in the Description page of Project Settings.

#include "MoreBuildables_BuildableLib.h"

DEFINE_LOG_CATEGORY(LogMoreBuildables_BuildableLib);

void UMoreBuildables_BuildableLib::SchematicUnlockRecipes(UFGSchematic* schematic, TArray<TSubclassOf<UFGRecipe>> unlock_recipes)
{
	UFGUnlockRecipe* unlocks = (UFGUnlockRecipe*) UFGSchematic::GetUnlocks(schematic->GetClass())[0];

	if (unlocks == nullptr)
	{
		UE_LOG(LogMoreBuildables_BuildableLib, Error, TEXT("Could not cast 'mUnlocks' property of UFGSchematic '%s' to UFGUnlockSchematic."), *(schematic->GetName()));
	}
	else
	{
		TArray<TSubclassOf<UFGRecipe>> _mRecipes = unlocks->GetmRecipes();
		for (size_t i = 0; i < unlock_recipes.Num(); i++)
			_mRecipes.Add(unlock_recipes[i]);

		unlocks->SetmRecipes(_mRecipes);
	}
}

void UMoreBuildables_BuildableLib::SchematicUnlockSchematics(UFGSchematic* schematic, TArray<TSubclassOf<UFGSchematic>> unlock_schematics)
{
	UFGUnlockSchematic* unlocks = (UFGUnlockSchematic*) UFGSchematic::GetUnlocks(schematic->GetClass())[1];
	if (unlocks == nullptr)
	{
		UE_LOG(LogMoreBuildables_BuildableLib, Error, TEXT("Could not cast 'mUnlocks' property of UFGSchematic '%s' to UFGUnlockSchematic."), *(schematic->GetName()));
	}
	else
	{
		TArray<TSubclassOf<UFGSchematic>> _mSchematics = unlocks->GetmSchematics();
		for (size_t i = 0; i < unlock_schematics.Num(); i++)
			_mSchematics.Add(unlock_schematics[i]);

		unlocks->SetmSchematics(_mSchematics);
	}
}

void UMoreBuildables_BuildableLib::UnlockingMaterialUnlocksBuildable(TArray<UFGSchematic*> materials, TArray<TSubclassOf<UFGSchematic>> cbg_schematics)
{
	for (size_t i = 0; i < materials.Num(); i++)
		SchematicUnlockSchematics(materials[i], { cbg_schematics[i] });
}

void UMoreBuildables_BuildableLib::MaterialSwatchAffectsBuildable(TArray<FRecipeMaterialStruct> recipes_array)
{
	for (size_t i = 0; i < recipes_array.Num(); i++)
	{
		TMap<TSubclassOf<AFGBuildable>, TSubclassOf<UFGRecipe>> _mBuildableMap = recipes_array[i].material_desc->GetmBuildableMap();
		for (size_t j = 0; j < recipes_array[i].recipes.Num(); j++)
		{
			for (size_t k = 0; k < recipes_array.Num(); k++)
			{
				TSubclassOf<UFGBuildingDescriptor> buildDesc = (TSubclassOf<UFGBuildingDescriptor>) recipes_array[k].recipes[j].GetDefaultObject()->GetProducts()[0].ItemClass;
				if (buildDesc == nullptr)
				{
					UE_LOG(LogMoreBuildables_BuildableLib, Error, TEXT("Could not cast UFGItemDescriptor* to UFGBuildingDescriptor*."));
				}
				else
				{
					if (recipes_array[k].material_desc != recipes_array[i].material_desc)
						_mBuildableMap.Add(UFGBuildingDescriptor::GetBuildableClass(buildDesc), recipes_array[i].recipes[j]);
				}
			}
		}

		recipes_array[i].material_desc->SetmBuildableMap(_mBuildableMap);
	}
}
