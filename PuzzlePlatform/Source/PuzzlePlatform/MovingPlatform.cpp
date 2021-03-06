// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


AMovingPlatform::AMovingPlatform() 
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	bReplicates = true;
	bReplicateMovement = true;
}

void AMovingPlatform::BeginPlay() 
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void AMovingPlatform::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) 
	{
		if (ActiveTriggers == 1)
		{

			FVector Location = GetActorLocation();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if(JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}


			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();		

			Location += (Velocity * DeltaTime * Direction);
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers = 1;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers = 0;
}
