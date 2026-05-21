
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaPC.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API AArenaPC : public ACharacter
{
    GENERATED_BODY()

public:
    AArenaPC();

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AArenaProjectile> ProjectileClass;

    void Fire();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* TempMesh;

    // Renamed to FPCamera to force Unreal to build a fresh one
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCameraComponent* FPCamera;

    void MoveForward(float Value);
    void MoveRight(float Value);
};