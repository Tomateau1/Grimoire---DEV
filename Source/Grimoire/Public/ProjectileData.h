// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileData.generated.h"

/**
 * 
 */
UCLASS()
class GRIMOIRE_API UProjectileData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float LifeSpan = 5.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float Speed = 10000.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float TurnRate = 300.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float TurnRateGrowth = 200.0;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FRotator RelativeRotation = FRotator(0.0, 0.0, 0.0);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float OuterCurveWidth;
};

