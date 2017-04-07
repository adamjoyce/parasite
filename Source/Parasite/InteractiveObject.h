// Copyright Adam Joyce 2017.  All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

UCLASS()
class PARASITE_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:	
	/* Sets default values for this actor's properties. */
	AInteractiveObject();

	/* Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

protected:
	
	/************************************************************/
	/* Components.                                              */
	/************************************************************/

	/* Visual static mesh component. */
	UPROPERTY(VisibleAnywhere, Category = "ActorMesh")
	UStaticMeshComponent* VisualMesh;

	/* This component is visible when the actor is highlighted by the player. */
	UPROPERTY(VisibleAnywhere, Category = "ActorMesh ")
	UStaticMeshComponent* HighlightMesh;

	/* Box collider for mouse over event. */
	UPROPERTY(VisibleAnywhere, Category = "ActorCollision")
	UBoxComponent* BoxCollider;

private:

	/************************************************************/
	/* Collision.                                               */
	/************************************************************/

	/* What happens when the mouse is over the actor. */
	UFUNCTION(BlueprintCallable, Category = "ActorCollision")
	void OnMouseOver(UPrimitiveComponent* TouchedComponent);

	/* What happens when the mouse is removed from over the actor. */
	UFUNCTION(BlueprintCallable, Category = "ActorCollision")
	void EndMouseOver(UPrimitiveComponent* TouchedComponent);
};
