#include "ArenaPC.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "ArenaProjectile.h"

AArenaPC::AArenaPC()
{
    // Create the temporary static mesh and attach it
    TempMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TempMesh"));
    TempMesh->SetupAttachment(RootComponent);

    // Create the fresh camera and attach it
    FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
    FPCamera->SetupAttachment(TempMesh);
    FPCamera->bUsePawnControlRotation = true;
}

void AArenaPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);


    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AArenaPC::Fire);
    PlayerInputComponent->BindAxis("MoveForward", this, &AArenaPC::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AArenaPC::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AArenaPC::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AArenaPC::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void AArenaPC::Fire()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = FPCamera->GetComponentLocation() + (FPCamera->GetForwardVector() * 100.0f);
        FRotator SpawnRotation = FPCamera->GetComponentRotation();

        GetWorld()->SpawnActor<AArenaProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
    } 
}