// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	StartRotation = GetActorRotation();

	FString MyName = GetName();
	
	UE_LOG(LogTemp, Display, TEXT("Here is my Name: %s"), *MyName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
	
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
		if (ShouldPlatformReturn())
		{
			FVector MoveDirection = PlatformVelocity.GetSafeNormal();
			StartLocation += MoveDirection * MovedDistance;
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity;
		}
		else
		{
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation += PlatformVelocity * DeltaTime;
			SetActorLocation(CurrentLocation);
		}
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MovedDistance;
}


double AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

// ********************************************************************************

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	if (ShouldPlatformRotateOtherDirection())
	{
		RotationVelocity = RotationVelocity.GetInverse();
	}
	else
	{
		AddActorLocalRotation(RotationVelocity * DeltaTime);
	}
}

bool AMovingPlatform::ShouldPlatformRotateOtherDirection() const
{
	return GetRotationRotated() > 180.f;
}

double AMovingPlatform::GetRotationRotated() const
{
	return FMath::Abs((GetActorRotation() - StartRotation).Yaw);
}

// **********************************************************************************


