// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaAICharacter.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API AArenaAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArenaAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void StartShooting();
	void StopShooting();

protected:
	void FireWeapon();
	FTimerHandle ShotTimerHandle;



public:
	// The AI's starting health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 100.0f;

	// The function that listens for incoming damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
