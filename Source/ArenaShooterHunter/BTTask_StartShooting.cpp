#include "BTTask_StartShooting.h"
#include "AIController.h"
#include "ArenaAICharacter.h"
#include "Engine/Engine.h"

UBTTask_StartShooting::UBTTask_StartShooting()
{
    NodeName = "Start Shooting";
}

EBTNodeResult::Type UBTTask_StartShooting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // TRAP 1: Did the Behavior Tree actually execute this node?
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("TASK NODE EXECUTED"));

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        // TRAP 2: The node ran, but it has no brain
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TASK FAILED: No AI Controller Found"));
        return EBTNodeResult::Failed;
    }

    AArenaAICharacter* AIChar = Cast<AArenaAICharacter>(AIController->GetPawn());
    if (!AIChar)
    {
        // TRAP 3: The brain exists, but the Cast failed (Wrong character class)
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TASK FAILED: Cast to ArenaAICharacter Failed"));
        return EBTNodeResult::Failed;
    }

    // Success: Pass the signal to the Character
    AIChar->StartShooting();
    return EBTNodeResult::Succeeded;
}