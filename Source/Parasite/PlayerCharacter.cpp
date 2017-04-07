// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter() : CameraHeight(2000.0f),
									   CameraRotation(FRotator(-60.0f, 0.0f, 0.0f)),
									   CameraLagSpeed(3.0f),
									   MovementSpeed(2000.0f),
									   InfluenceRadius(200.0f),
									   CurrentInteractiveActor(nullptr)
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
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void APlayerCharacter::Amalgamate()
{
	if (CurrentInteractiveActor != nullptr && ((GetActorLocation() - CurrentInteractiveActor->GetActorLocation()).Size()) <= InfluenceRadius)
	{
		/// Merge the player with the interactive actor.
		UE_LOG(LogTemp, Warning, TEXT("AMALGAMATE"));
	}
}

AActor* APlayerCharacter::GetCurrentInteractiveActor()
{
	return CurrentInteractiveActor;
}

void APlayerCharacter::SetCurrentInteractiveActor(AActor* NewInteractiveActor)
{
	CurrentInteractiveActor = NewInteractiveActor;
}

