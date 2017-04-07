// Copyright Adam Joyce 2017.  All rights reserved.

#pragma once

#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PARASITE_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	/* Sets default values for this character's properties. */
	APlayerCharacter();

protected:

private:
	/* Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

	/* Called every frame. */
	virtual void Tick(float DeltaSeconds) override;

	/* Called to bind functionality to input. */
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/************************************************************/
	/* Components.                                              */
	/************************************************************/

	/* Player camera. */
	UPROPERTY(VisibleAnywhere, Category = "CharacterCamera")
	UCameraComponent* Camera;

	/* Spring arm for smooth camera transistions. */
	UPROPERTY(VisibleAnywhere, Category = "CharacterCamera")
	USpringArmComponent* SpringArm;

	/************************************************************/
	/* Camera.                                                  */
	/************************************************************/

	/* Height of the player camera. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterCamera")
	float CameraHeight;

	/* Camera rotation attached to spring arm. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterCamera")
	FRotator CameraRotation;

	/* Lag speed of the camera acttahed to the spring arm. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterCamera")
	float CameraLagSpeed;

	/************************************************************/
	/* Movement.                                                */
	/************************************************************/

	/* Speed the character travels at. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterMovement")
	float MovementSpeed;

	/* Moves the pawn along its forward vector. */
	void MoveForward(float AxisValue);

	/* Moves the pawn along its right vector. */
	void MoveRight(float AxisValue);
};
