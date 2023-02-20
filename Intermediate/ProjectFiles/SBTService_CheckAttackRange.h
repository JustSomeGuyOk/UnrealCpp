
#pragma once

#include "CoreMinimal.h"
#include "BehaviourTree/BTService.h"
#include "SBTService_CheckAttackRange.generated.h"

/**
*
*/
UCLASS()
class UNREALCPP_API USBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY();

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviourTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
}