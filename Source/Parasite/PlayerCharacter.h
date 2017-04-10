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

	/************************************************************/
	/* Targeting and Detection.                                 */
	/************************************************************/

	/* Get the currently highlighted interactive actor. */
	UFUNCTION(BlueprintCallable, Category = "CharacterDetection")
	AActor* GetHighlightedActor();

	/* Updates the currently highlighted interactive actor. */
	UFUNCTION(BlueprintCallable, Category = "CharacterDetection")
	void SetHighlightedActor(AActor* NewHighlightedActor);

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

	/* Sphere of influence used to determine what actors abilities can be used on. */
	/* Currently only used for visual radius. */
	UPROPERTY(VisibleAnywhere, Category = "CharacterDetection")
	USphereComponent* SphereOfInfluence;

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

	/************************************************************/
	/* Targeting and Detection.                                 */
	/************************************************************/

	/* Sphere of influence radius. */
	UPROPERTY(EditDefaultsOnly, Category = "CharacterDetection")
	float InfluenceRadius;

	/* If the character is currently merged with another actor. */
	bool IsAmalgamated;

	/* The currently highlighted interactive actor. */
	AActor* HighlightedActor;

	/* The actor the player is currently merged with. */
	AActor* AmalgamatedActor;

	/* The player amalgamates (merges) with the current interactive actor. */
	UFUNCTION(BlueprintCallable, Category = "CharacterDetection")
	void Amalgamate();

	/* Called when the player moves out of a previously amalgamated actor. */
	UFUNCTION(BlueprintCallable, Category = "CharacterDetection")
	void Seperate();
};
