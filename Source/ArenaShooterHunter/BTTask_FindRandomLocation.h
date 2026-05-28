#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindRandomLocation.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API UBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
    GENERATED_BODY()

public:
    UBTTask_FindRandomLocation();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};