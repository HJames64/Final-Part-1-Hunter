#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
    NodeName = "Find Random Location";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Safely get the AI Controller and the physical enemy Pawn
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) return EBTNodeResult::Failed;

    // Safely get the Navigation System
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSys) return EBTNodeResult::Failed;

    // Find a random point on the green NavMesh within a 1500 unit radius
    FNavLocation RandomLocation;
    if (NavSys->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), 1500.0f, RandomLocation))
    {
        // Save the location to the Blackboard so the "Move To" node can use it
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}