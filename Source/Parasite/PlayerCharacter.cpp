// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter() : CameraHeight(2000.0f),
									   CameraRotation(FRotator(-60.0f, 0.0f, 0.0f)),
									   CameraLagSpeed(3.0f),
									   MovementSpeed(2000.0f),
									   InfluenceRadius(200.0f),
									   IsAmalgamated(false),
									   HighlightedActor(nullptr),
									   AmalgamatedActor(nullptr)
{
	/// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Spring arm for the camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = CameraRotation;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CameraLagSpeed;
	SpringArm->bDoCollisionTest = false;

	/// Setup the camera and attach it to the spring arm.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	/// The player's sphere of influence.
	/// Currently used for visual representation.
	SphereOfInfluence = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOfInfluence"));
	SphereOfInfluence->InitSphereRadius(InfluenceRadius);
	SphereOfInfluence->SetupAttachment(RootComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/// Apply changes that may have been made in the editor.
	SpringArm->TargetArmLength = CameraHeight;
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	SphereOfInfluence->SetSphereRadius(InfluenceRadius);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AmalgamatedActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *AmalgamatedActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULLPTR"));
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Amalgamate", IE_Pressed, this, &APlayerCharacter::Amalgamate);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent && AxisValue != 0.0f)
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);

		/// Resets the amalgamation actor and flag.
		if (IsAmalgamated)
		{
			Seperate();
		}
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent && AxisValue != 0.0f)
	{
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);

		/// Resets the amalgamation actor and flag.
		if (IsAmalgamated)
		{
			Seperate();
		}
	}
}

void APlayerCharacter::Amalgamate()
{
	if (HighlightedActor != nullptr && ((GetActorLocation() - HighlightedActor->GetActorLocation()).Size()) <= InfluenceRadius)
	{
		if (!IsAmalgamated)
		{
			IsAmalgamated = true;
		}

		AmalgamatedActor = HighlightedActor;

		/// Merge the player with the interactive actor.
		//SetActorLocation(HighlightedFVector(-10.0f, 0.0f, 0.0f))
		//AttachRootComponentTo(CurrentInteractiveActor->GetRootComponent());
		UE_LOG(LogTemp, Warning, TEXT("AMALGAMATE"));
	}
}

void APlayerCharacter::Seperate()
{
	IsAmalgamated = false;
	AmalgamatedActor = nullptr;
}

AActor* APlayerCharacter::GetHighlightedActor()
{
	return HighlightedActor;
}

void APlayerCharacter::SetHighlightedActor(AActor* NewHighlightedActor)
{
	HighlightedActor = NewHighlightedActor;
}

AActor* APlayerCharacter::GetAmalgamatedActor()
{
	return AmalgamatedActor;
}

void APlayerCharacter::SetAmalgamatedActor(AActor* NewAmalgamatedActor)
{
	AmalgamatedActor = NewAmalgamatedActor;
}

