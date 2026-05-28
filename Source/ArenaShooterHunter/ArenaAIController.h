

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ArenaAIController.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API AArenaAIController : public AAIController
{
    GENERATED_BODY()

public:
    AArenaAIController();

protected:
    virtual void BeginPlay() override;

public:
    // The perception component acts as the AI's senses
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UAIPerceptionComponent* AIPerceptionComp;

    // The specific configuration for Sight
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    class UAISenseConfig_Sight* SightConfig;

    // The function that triggers when the AI sees or loses sight of something
    UFUNCTION()
    void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

    UPROPERTY(EditDefaultsOnly, Category = "AI")
    class UBehaviorTree* AIBehavior;
};