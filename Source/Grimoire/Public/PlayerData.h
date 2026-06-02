// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class GRIMOIRE_API UPlayerData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomMinDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomMaxDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomMinPitch;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float ZoomMaxPitch;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float MoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	FVector2D MoveVerticalClamp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	FVector2D MoveHorizontalClamp;
};
