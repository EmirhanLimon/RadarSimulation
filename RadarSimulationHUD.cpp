// Copyright Epic Games, Inc. All Rights Reserved.

#include "RadarSimulationHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ARadarSimulationHUD::ARadarSimulationHUD()
{
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void ARadarSimulationHUD::DrawHUD()
{
	Super::DrawHUD();

	
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

FVector2D ARadarSimulationHUD::GetRadarCenterPosition()
{
	
	return (Canvas) ? FVector2D(Canvas->SizeX * RadarStartLocation.X, Canvas->SizeY * RadarStartLocation.Y) : FVector2D(0, 0);
}

void ARadarSimulationHUD::DrawRadar()
{

	FVector2D RadarCenter = GetRadarCenterPosition();

	for (float i = 0; i < 360; i += DegreeStep)
	{
		
		float fixedX = FMath::Cos(i) * RadarRadius;
		float fixedY = FMath::Sin(i) * RadarRadius;

		
		DrawLine(RadarCenter.X, RadarCenter.Y, RadarCenter.X + fixedX, RadarCenter.Y + fixedY, FLinearColor::Gray, 1.f);
	}
}

void ARadarSimulationHUD::DrawPlayerInRadar()
{
	FVector2D RadarCenter = GetRadarCenterPosition();

	DrawRect(FLinearColor::Blue, RadarCenter.X, RadarCenter.Y, DrawPixelSize, DrawPixelSize);
}

void ARadarSimulationHUD::PerformRadarRaycast()
{
	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (Player)
	{
		TArray<FHitResult> HitResults;
		FVector EndLocation = Player->GetActorLocation();
		EndLocation.Z += SphereHeight;

		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(SphereRadius);

		
		GetWorld()->SweepMultiByChannel(HitResults, Player->GetActorLocation(), EndLocation, FQuat::Identity, ECollisionChannel::ECC_WorldDynamic, CollisionShape);

		for (auto It : HitResults)
		{
			AActor* CurrentActor = It.GetActor();
			
			if (CurrentActor && CurrentActor->ActorHasTag("Radar")) RadarActors.Add(CurrentActor);
		}
	}
}
