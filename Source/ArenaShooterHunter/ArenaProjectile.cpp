// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArenaProjectile::AArenaProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	RootComponent = CollisionComp;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp->OnComponentHit.AddDynamic(this, &AArenaProjectile::OnHit);

}

// Called when the game starts or when spawned
void AArenaProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArenaProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Ensure we hit something valid and didn't just hit ourselves
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		Destroy(); // Remove the bullet from the world
	}
}
