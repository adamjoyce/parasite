// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController() : BotTypeKeyName("BotType")
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter* EnemyBot = Cast<AEnemyCharacter>(InPawn);
	if (EnemyBot)
	{
		if (EnemyBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*EnemyBot->BehaviorTree->BlackboardAsset);

			/// Ensure the blackboard has the type of the bot we possessed.
			SetBlackboardBotType(EnemyBot->BotType);
		}

		BehaviorComp->StartTree(*EnemyBot->BehaviorTree);
	}
}

void AEnemyAIController::UnPossess()
{
	Super::UnPossess();

	/// Stop any behavior running since we no longer control the pawn.
	BehaviorComp->StopTree();
}

void AEnemyAIController::SetBlackboardBotType(EBotBehaviorType NewType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (uint8)(NewType));
	}
}