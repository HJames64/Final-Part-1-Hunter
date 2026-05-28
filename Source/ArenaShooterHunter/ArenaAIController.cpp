#include "ArenaAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AArenaAIController::AArenaAIController()
{
    // Create the perception component and sight config
    AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    // Configure the sight parameters
    SightConfig->SightRadius = 1500.0f;
    SightConfig->LoseSightRadius = 1800.0f;
    SightConfig->PeripheralVisionAngleDegrees = 90.0f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    // Apply the configuration to the perception component
    AIPerceptionComp->ConfigureSense(*SightConfig);
    AIPerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AArenaAIController::BeginPlay()
{
    Super::BeginPlay();

    // 1. BOOT THE BRAIN FIRST
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
    }
    else
    {
        // TRAP: If the Blueprint dropped the Behavior Tree, this will fire instantly on play
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CRITICAL: AIBEHAVIOR IS EMPTY IN BLUEPRINT!"));
    }

    // 2. OPEN THE EYES SECOND
    if (AIPerceptionComp)
    {
        AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AArenaAIController::OnTargetDetected);
    }
}

void AArenaAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
    // TRAP 1: This is completely outside the if-statements. 
    // If the delegate works, this WILL print yellow.
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("C++ FUNCTION IS ALIVE!"));

    // Try to get the Blackboard
    UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

    // TRAP 2: Check if the Blackboard is missing
    if (BlackboardComp == nullptr)
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("ERROR: BLACKBOARD IS NULL!"));
        return;
    }

    // Normal Logic
    if (Stimulus.WasSuccessfullySensed())
    {
        BlackboardComp->SetValueAsObject(TEXT("TargetActor"), Actor);
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("AI SEES YOU!"));
    }
    else
    {
        BlackboardComp->ClearValue(TEXT("TargetActor"));
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("AI LOST YOU!"));
    }
}
