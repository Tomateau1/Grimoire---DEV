// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyData.generated.h"

/**
 * 
 */
UCLASS()
class GRIMOIRE_API UEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float FireRate = 1.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float SlotSearchAngle = 360.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 2500.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float PhysicalDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float MagicDamage = -1.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float PhysicalDamageReduction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float MagicDamageReduction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float CriticalChance = 0.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float CriticalDamageMultiplier = 200.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	float MaxHPs = 200.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	int EssencesValue;
};
