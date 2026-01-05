// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FGBuildable.h"
#include "FGBuildingDescriptor.h"
#include "FGFactoryColoringTypes.h"
#include "FGRecipe.h"
#include "FGUnlock.h"
#include "FGUnlockSchematic.h"
#include "FGUnlockRecipe.h"

#include "MoreBuildables_Structs.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MoreBuildables_BuildableLib.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMoreBuildables_BuildableLib, Verbose, All);

/**
 * This class is used when making new buildables that have materials such as foundations or walls.
 */
UCLASS()
class MOREBUILDABLES_API UMoreBuildables_BuildableLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Add all recipes in `unlock_recipes` to the recipes that `schematic` will unlock.
	 *
	 * @param schematic			Pointer to UFGSchematic. Schematic that will be updated with the new recipes in `unlock_recipes`.
	 * @param unlock_recipes	Array of UFGRecipe. Contains the recipes that will be added to `schematic`.
	 */
	UFUNCTION(BlueprintCallable, Category = "MakeBuildables")
	static void SchematicUnlockRecipes(UFGSchematic* schematic, TArray<TSubclassOf<UFGRecipe>> unlock_recipes);

	/**
	 * Add all schematics in `unlock_schematics` to the schematics that `schematic` will unlock.
	 *
	 * @param schematic			Pointer to UFGSchematic. Schematic that will be updated with the new schematics in `unlock_schematics`.
	 * @param unlock_schematics	Array of UFGSchematic. Contains the schematics that will be added to `schematic`.
	 */
	UFUNCTION(BlueprintCallable, Category = "MakeBuildables")
	static void SchematicUnlockSchematics(UFGSchematic* schematic, TArray<TSubclassOf<UFGSchematic>> unlock_schematics);

	/**
	 * Unlocks a buildable when unlocking the corresponding material.
	 * For example, unlocking the Concrete material will unlock the CBG schematic related to that material.
	 * 
	 * @param materials			Array of UFGSchematic that corresponds to the material schematics.
	 * @param cbg_schematics	Array of UFGSchematic that corresponds to the CBG schematics to be unlocked. Order must match the order of the `materials` array.
	 */
	UFUNCTION(BlueprintCallable, Category = "MakeBuildables")
	static void UnlockingMaterialUnlocksBuildable(TArray<UFGSchematic*> materials, TArray<TSubclassOf<UFGSchematic>> cbg_schematics);

	/**
	 * Makes it so that changing the material swatch on a buildable works like expected.
	 * 
	 * @param recipes_array		Array of FRecipeMaterialStruct struct that acts as a map. See documentation of the struct for more details.
	 */
	UFUNCTION(BlueprintCallable, Category = "MakeBuildables")
	static void MaterialSwatchAffectsBuildable(TArray<FRecipeMaterialStruct> recipes_array);
};
