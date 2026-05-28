#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StartShooting.generated.h"

UCLASS()
class ARENASHOOTERHUNTER_API UBTTask_StartShooting : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_StartShooting();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};