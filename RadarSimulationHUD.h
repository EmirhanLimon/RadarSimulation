// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RadarSimulationHUD.generated.h"

UCLASS()
class ARadarSimulationHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARadarSimulationHUD();

	
	virtual void DrawHUD() override;

private:
	
	class UTexture2D* CrosshairTex;

protected:
	
	UPROPERTY(EditAnywhere, Category = Radar)
		FVector2D RadarStartLocation = FVector2D(0.9f, 0.2f);

	
	UPROPERTY(EditAnywhere, Category = Radar)
		float RadarRadius = 100.f;

	UPROPERTY(EditAnywhere, Category = Radar)
		float DegreeStep = 0.25f;

	
	UPROPERTY(EditAnywhere, Category = Radar)
		float DrawPixelSize = 5.f;

	
	UFUNCTION()
	FVector2D GetRadarCenterPosition();

	
	UFUNCTION()
	void DrawRadar();
	UFUNCTION()
	void DrawPlayerInRadar();


	
	UPROPERTY(EditAnywhere, Category = Radar)
		float SphereHeight = 200.f;

	UPROPERTY(EditAnywhere, Category = Radar)
		float SphereRadius = 2750.f;

	
	TArray<AActor*> RadarActors;
	UFUNCTION()
	void PerformRadarRaycast();


	
	UPROPERTY(EditAnywhere, Category = Radar)
		float RadarDistanceScale = 25.f;

	
	UFUNCTION()
	FVector2D ConvertWorldLocationToLocal(AActor* ActorToPlace);

	
	UFUNCTION()
	void DrawRaycastedActors();

};

