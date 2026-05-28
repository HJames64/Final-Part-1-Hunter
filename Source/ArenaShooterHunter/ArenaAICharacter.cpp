#include "ArenaAICharacter.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
AArenaAICharacter::AArenaAICharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AArenaAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AArenaAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AArenaAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AArenaAICharacter::StartShooting()
{
    // TRAP 1: Did the Behavior Tree successfully find the character?
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, TEXT("1. BT TRIGGERED C++!"));

    if (GetWorldTimerManager().IsTimerActive(ShotTimerHandle))
    {
        return;
    }

    // TRAP 2: Is the timer actually booting up?
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Magenta, TEXT("2. TIMER STARTED!"));
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AArenaAICharacter::FireWeapon, 0.2f, true);
}

void AArenaAICharacter::StopShooting()
{
    // TRAP 3: Is the Patrol branch accidentally killing our timer?
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("X. TIMER KILLED BY PATROL BRANCH!"));
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}
void AArenaAICharacter::FireWeapon()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.4f, FColor::Orange, TEXT("BANG!"));

    UWorld* World = GetWorld();
    if (!World) return;

    // 1. DETERMINE START AND END POINTS
    // Start the trace from the AI's eye position or gun location
    FVector StartLocation = GetActorLocation() + FVector(0.f, 0.f, 60.f);

    // Find which way the AI is currently aiming/facing
    FVector ForwardVector = GetActorForwardVector();

    // Set a maximum effective range for the gun (e.g., 5000 units / 50 meters)
    float WeaponRange = 5000.f;
    FVector EndLocation = StartLocation + (ForwardVector * WeaponRange);

    // 2. CONFIGURE COLLISION PARAMETERS
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Prevent the AI from accidentally shooting itself

    // 3. EXECUTE THE LINE TRACE
    // ECC_Visibility checks for anything that blocks sight lines (players, walls, geometry)
    bool bHitSuccess = World->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECC_Visibility,
        QueryParams
    );

    // 4. VISUALIZE THE SHOT IN THE EDITOR (TEMPORARY DEBUG)
    // Draws a red line for 0.4 seconds so you can see where the AI is shooting
    DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, 0.4f, 0, 2.0f);

    // 5. PROCESS THE HIT DATA
    if (bHitSuccess && HitResult.GetActor())
    {
        AActor* HitActor = HitResult.GetActor();

        if (GEngine)
        {
            FString HitMessage = FString::Printf(TEXT("💥 AI HIT: %s 💥"), *HitActor->GetName());
            GEngine->AddOnScreenDebugMessage(-1, 0.4f, FColor::Orange, HitMessage);
        }

        // Send 15 points of base damage to whatever the laser just touched
        UGameplayStatics::ApplyDamage(HitActor, 15.0f, GetController(), this, UDamageType::StaticClass());
    }
    }
float AArenaAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // 1. Process the math
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health -= ActualDamage;

    // 2. Check for Death
    if (Health <= 0.0f)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("💀 AI KILLED! RESPAWNING... 💀"));

        // 3. Find a safe spot to drop the new AI (600 units straight up from where it died)
        FVector DropZone = GetActorLocation() + FVector(0.0f, 0.0f, 600.0f);

        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        // 4. Spawn the fresh clone using the exact same Blueprint class
        GetWorld()->SpawnActor<AArenaAICharacter>(GetClass(), DropZone, GetActorRotation(), SpawnParams);

        // 5. Destroy the dead body
        Destroy();
    }
    else
    {
        // Print remaining health if it survived the shot
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("AI Health: %f"), Health));
    }

    return ActualDamage;
}