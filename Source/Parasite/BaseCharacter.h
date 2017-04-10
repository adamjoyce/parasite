// Copyright Adam Joyce 2017.  All rights reserved.

#pragma once

#include "GameFramework/Character.h"
#include "Types.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PARASITE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties. */
	ABaseCharacter();

	/************************************************************/
	/* Health                                                   */
	/************************************************************/

	/* Returns the player's current health. */
	UFUNCTION(BlueprintCallable, Category = "CharacterCondition")
	float GetHealth() const;

	/* Is the character above zero health? */
	UFUNCTION(BlueprintCallable, Category = "CharacterCondition")
	bool IsAlive() const;

protected:
	/************************************************************/
	/* Components.                                              */
	/************************************************************/

	/* Fractures on character death. */
	UPROPERTY(VisibleAnywhere, Category = "CharacterComponents")
	UDestructibleComponent* DestructibleMesh;

	/************************************************************/
	/* Health                                                   */
	/************************************************************/

	/* The character's health pool - zero means game over. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterCondition")
	float Health;

	/************************************************************/
	/* Damage and Death.                                        */
	/************************************************************/

	/* The damage the 'deathsplosion' applies to the character. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterDamage")
	float DestructibleExplosionDamage;

	/* The impulse force the 'deathsplosion applies to the character. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterDamage")
	float DestructibleExplosionImpulse;

	/* Damage. */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	/* What the character does on death. */
	virtual void OnDeath();

	/* Death animation and visual component actions. */
	virtual void PlayDeathAnimation();
};
