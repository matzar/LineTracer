// Fill out your copyright notice in the Description page of Project Settings.

#include "LineTracer.h"
#include "RotateActor.h"


// Sets default values
ARotateActor::ARotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 300 - number of units away from the player in the X axis
	m_Dimensions = FVector(300, 0, 0);
	
	m_Multiplier = 50.0f;
}

// Called when the game starts or when spawned
void ARotateActor::BeginPlay()
{
	Super::BeginPlay();

	// what direction is the actor to be moved about
	// (0, 1, -1) for going left and
	// (0, 1, 1) for goiing right
	if (m_GoDown)
	{
		m_Axis = FVector(0, 1, -1);
	}
	else if (m_GoUp)
	{
		m_Axis = FVector(0, 1, 1);
	}

}

// Called every frame
void ARotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// rotate actor around the player
	FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// degree around the point the actor should move to
	// DeltaTime times m_Multiplier for smooth movement
	m_Angle += DeltaTime * m_Multiplier;

	// when the actor made a full circle around the player - reset m_Angle
	if (m_Angle >= 360.0f)
		m_Angle = 0;

	// Set RotateValue from m_Dimensions vector
	// this will return the number of units to move the actor to the new location
	FVector RotateValue = m_Dimensions.RotateAngleAxis(m_Angle, m_Axis);
	if (m_MoveRight)
	{
		NewLocation.X += RotateValue.X;
		NewLocation.Y += RotateValue.Y;
		NewLocation.Z += RotateValue.Z;
	}
	else if (m_MoveLeft)
	{
		NewLocation.X -= RotateValue.X;
		NewLocation.Y -= RotateValue.Y;
		NewLocation.Z -= RotateValue.Z;
	}

	FRotator NewRotation = FRotator(0, m_Angle, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);
}

