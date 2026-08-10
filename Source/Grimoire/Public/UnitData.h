// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UnitData.generated.h"

/**
 * 
 */
UCLASS()
class GRIMOIRE_API UUnitData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float FireRate = 1.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float SpellDuration = -1.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float SlotSearchAngle = 360.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Passive|PassiveAbility")
	bool IsPassiveAbilityEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Passive|PassiveResource")
	bool IsPassiveResourceEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Passive|PassiveResource")
	int Segments;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Passive|PassiveResource")
	bool HasIncreaseAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data|Passive|PassiveResource")
	FLinearColor FillColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 2000.0;
	
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
	bool HasMana = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	float MaxMana = 100.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	float ManaGain;
};
