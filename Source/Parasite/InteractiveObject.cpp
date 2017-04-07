// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "PlayerCharacter.h"
#include "InteractiveObject.h"


AInteractiveObject::AInteractiveObject()
{
 	/// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// An arrow that acts at the root component.
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	/// Setup the visual mesh.
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(RootComponent);

	/// Setup the highlight mesh.
	HighlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HightlightMesh"));
	HighlightMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HighlightMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HighlightMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	HighlightMesh->SetVisibility(false);
	HighlightMesh->SetupAttachment(RootComponent);

	/// Setup the box collider component.
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
	BoxCollider->bGenerateOverlapEvents = false;
	BoxCollider->SetupAttachment(RootComponent);

	/// Set 'Interactive' tag so the player detects the object.
	Tags.Add(TEXT("Interactive"));
}

void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	if (BoxCollider)
	{
		BoxCollider->OnBeginCursorOver.AddDynamic(this, &AInteractiveObject::OnMouseOver);
		BoxCollider->OnEndCursorOver.AddDynamic(this, &AInteractiveObject::EndMouseOver);
	}
}

void AInteractiveObject::OnMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (GetWorld() && HighlightMesh != nullptr)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerCharacter != nullptr && PlayerCharacter->GetCurrentInteractiveActor() != this)
		{
			PlayerCharacter->SetCurrentInteractiveActor(this);
		}

		HighlightMesh->SetVisibility(true);
	}
}

void AInteractiveObject::EndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (GetWorld() && HighlightMesh != nullptr)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (PlayerCharacter != nullptr)
		{
			PlayerCharacter->SetCurrentInteractiveActor(nullptr);
		}

		HighlightMesh->SetVisibility(false);
	}
}

