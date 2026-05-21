// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArenaTarget.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API AArenaTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenaTarget();

protected:


	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* TargetMesh;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Health;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
