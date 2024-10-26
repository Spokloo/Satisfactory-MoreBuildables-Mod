// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FGBuildable.h"
#include "FGRecipe.h"
#include "FGFactoryColoringTypes.h"

#include "CoreMinimal.h"
#include "MoreBuildables_Structs.generated.h"

/**
 * Struct used as a map.
 * 
 * @var material_desc UFGFactoryCustomizationDescriptor_Material object reference, used as the key of the map.
 * @var recipes Array of UFGRecipe, used as the value of the map. The array can contain every variation of the buildable recipes (1m, 2m, 4m, ...).
 */
USTRUCT(BlueprintType)
struct FRecipeMaterialStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	UFGFactoryCustomizationDescriptor_Material* material_desc;

	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<UFGRecipe>> recipes;
};

/**
 * Struct used as a map.
 * 
 * @var material_desc UFGFactoryCustomizationDescriptor_Material object reference, used as the key of the map.
 * @var recipes Array of AFGBuildable, used as the value of the map. The array can contain every variation of the buildable builds (1m, 2m, 4m, ...).
 */
USTRUCT(BlueprintType)
struct FBuildMaterialStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	UFGFactoryCustomizationDescriptor_Material* material_desc;

	UPROPERTY(BlueprintReadWrite)
	TArray<TSubclassOf<AFGBuildable>> builds;
};
