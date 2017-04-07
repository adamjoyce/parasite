// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "BaseCharacter.h"


ABaseCharacter::ABaseCharacter() : Health(100.0f),
								   DestructibleExplosionDamage(10.0f),
								   DestructibleExplosionImpulse(10000.0f)
{
	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Create the destructible mesh component.
	DestructibleMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleMesh"));
	DestructibleMesh->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	DestructibleMesh->SetupAttachment(RootComponent);
}

float ABaseCharacter::GetHealth() const
{
	return Health;
}

bool ABaseCharacter::IsAlive() const
{
	return Health > 0;
}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return 0.0f;
	}

	const float DamageToTake = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (DamageToTake > 0.0f)
	{
		Health -= DamageToTake;

		if (Health <= 0.0f)
		{
			/// Stick dying code in here...
			/// Maybe place checks to see if dying is possible...
			OnDeath();
		}
	}

	return DamageToTake;
}

void ABaseCharacter::OnDeath()
{
	/// Disable all collision on capsule.
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	PlayDeathAnimation();
}

void ABaseCharacter::PlayDeathAnimation()
{
	bool IsDying = false;
	if (IsPendingKill())
	{
		IsDying = false;
	} 
	else
	{
		/// Explode destructible character mesh.
		DestructibleMesh->ApplyRadiusDamage(DestructibleExplosionDamage, GetActorLocation(), 1.0f, DestructibleExplosionImpulse, true);
		IsDying = true;
	}

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}

	if (!IsDying)
	{
		/// Hide the character immediately.
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(1.0f);
	} else
	{
		SetLifeSpan(3.0f);
	}
}

