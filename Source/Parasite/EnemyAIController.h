// Copyright Adam Joyce 2017.  All rights reserved.

#pragma once

#include "AIController.h"
#include "BaseCharacter.h"
#include "EnemyAIController.generated.h"


UCLASS()
class PARASITE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	/************************************************************/
	/* Pawn Control and Setup.                                  */
	/************************************************************/

	/* Changes the blackboard's bot type. */
	void SetBlackboardBotType(EBotBehaviorType NewType);

protected:

private:
	/************************************************************/
	/* Components.                                              */
	/************************************************************/

	/* The bahviour tree. */
	UBehaviorTreeComponent* BehaviorComp;

	/* The blackboard for the behaviour tree. */
	UBlackboardComponent* BlackboardComp;

	/************************************************************/
	/* Pawn Control and Setup.                                  */
	/************************************************************/

	/* Called whenever the AI Controller possess a character bot. */
	virtual void Possess(class APawn* InPawn) override;

	/* Called whenever the AI Controller loses control of a character bot. */
	virtual void UnPossess() override;

	/************************************************************/
	/* Blackboard Key Names.                                    */
	/************************************************************/

	/* Blackboard key name for the target location. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterAI")
	FName BotTypeKeyName;
};
