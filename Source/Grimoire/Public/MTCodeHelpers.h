// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MTCodeHelpers.generated.h"

static constexpr uint32 Magic   = 0x99310038;
static constexpr uint32 Version = 1;

USTRUCT(BlueprintType)
struct FSaveHeader
{
	GENERATED_BODY()
	
	uint32 MagicNumber = Magic;
	uint32 SaveVersion = Version;
	uint32 PayloadSize = 0;
	uint32 Checksum = 0;
	
	friend FArchive& operator<<(FArchive& Ar, FSaveHeader& Header)
	{
		Ar << Header.MagicNumber;
		Ar << Header.SaveVersion;
		Ar << Header.PayloadSize;
		Ar << Header.Checksum;
		return Ar;
	}
};

/**
 * 
 */
UCLASS()
class GRIMOIRE_API UMTCodeHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "File")
	static bool SaveGameWithChecksum(USaveGame* SaveGameObject, FString SlotName, int32 UserIndex);
	
	UFUNCTION(BlueprintCallable, Category = "File")
	static USaveGame* LoadGameWithSanityCheck(FString SlotName, int32 UserIndex);
	
	UFUNCTION(BlueprintCallable, Category = "File")
	static void CopyTempSave();
	
	UFUNCTION(BlueprintCallable, Category = "File")
	static void RestoreBackup();
	
	UFUNCTION(BlueprintCallable, Category = "File")
	static void ArchivePlayerSave();
	
	UFUNCTION(BlueprintCallable, Category = "File")
	static void ClearUserSettingsCache();
	
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
