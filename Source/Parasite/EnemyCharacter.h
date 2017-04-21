// Copyright Adam Joyce 2017.  All rights reserved.

#pragma once

#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"


UCLASS()
class PARASITE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	/************************************************************/
	/* Components.                                              */
	/************************************************************/

	/* The brain of the enemy - makes decisions based on data from its blackboard. */
	/* Assigned at character level to enable reuse of the enemy AI controller. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterAI")
	class UBehaviorTree* BehaviorTree;

	/* The behviour this bot will execute (passive/patrol/...). */
	UPROPERTY(EditAnywhere, Category = "CharacterAI")
	EBotBehaviorType BotType;

	/************************************************************/
	/* AI Setup                                                 */
	/************************************************************/

	/* Change the default bot type during gameplay. */
	//void SetBotType(EBotBehaviorType NewType);
};
