// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "EnemyCharacter.h"


AEnemyCharacter::AEnemyCharacter() : BehaviorTree(nullptr),
									 BotType(EBotBehaviorType::Passive)
{
	/// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

}