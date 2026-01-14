// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MTColorReferences.generated.h"

/**
 * 
 */
UCLASS()
class MNZOTEMPLATE_API UMTColorReferences : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colors|UI")
	FLinearColor ExampleColor;
};
