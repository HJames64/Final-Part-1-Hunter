// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaTarget.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

AArenaTarget::AArenaTarget()
{
    PrimaryActorTick.bCanEverTick = true;

    TargetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
    RootComponent = TargetMesh;
    Health = 100.0f;
}

void AArenaTarget::BeginPlay()
{
    Super::BeginPlay();
}

void AArenaTarget::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

float AArenaTarget::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;

    if (GEngine)
    {
        FString HealthMessage = FString::Printf(TEXT("Target Health: %f"), Health);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, HealthMessage);
    }

    if (Health <= 0.0f)
    {
        Destroy();
    }

    return DamageAmount;
}