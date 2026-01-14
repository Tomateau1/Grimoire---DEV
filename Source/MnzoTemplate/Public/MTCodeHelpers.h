// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MTCodeHelpers.generated.h"

/**
 * 
 */
UCLASS()
class MNZOTEMPLATE_API UMTCodeHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Saves")
	static bool RestoreBackupIfCorrupted(const FString& MainSlot, const FString& BackupSlot);
	
	UFUNCTION(BlueprintCallable, Category = "Window")
	static FVector2D GetWindowPosition();

	UFUNCTION(BlueprintCallable, Category = "Window")
	static void SetWindowPosition(FVector2D Position);
	
	UFUNCTION(BlueprintCallable, Category = "Window")
	static FVector2D GetMonitorSize();
	
	UFUNCTION(BlueprintCallable, Category = "Sorting")
	static TArray<FVector2D> NormalizeAndSortVector2DArray(const TArray<FVector2D> Points);

	UFUNCTION(BlueprintCallable, Category = "Sorting")
	static TArray<float> SortFloatArrayAscending(const TArray<float> InputArray);
};
