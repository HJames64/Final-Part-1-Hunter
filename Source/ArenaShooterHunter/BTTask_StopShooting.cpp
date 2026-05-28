#include "BTTask_StopShooting.h"
#include "AIController.h"
#include "ArenaAICharacter.h"

UBTTask_StopShooting::UBTTask_StopShooting()
{
    NodeName = "Stop Shooting";
}

EBTNodeResult::Type UBTTask_StopShooting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    AArenaAICharacter* AIChar = Cast<AArenaAICharacter>(AIController->GetPawn());
    if (!AIChar) return EBTNodeResult::Failed;

    AIChar->StopShooting();
    return EBTNodeResult::Succeeded;
}