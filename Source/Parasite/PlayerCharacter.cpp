// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "PlayerCharacter.h"


APlayerCharacter::APlayerCharacter() : CameraHeight(2000.0f),
									   CameraRotation(FRotator(-60.0f, 0.0f, 0.0f)),
									   CameraLagSpeed(3.0f),
									   MovementSpeed(2000.0f),
									   InfluenceRadius(200.0f)
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

	/// Bind the component overlap delegates for the sphere of influence.
	if (SphereOfInfluence)
	{
		SphereOfInfluence->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);
		SphereOfInfluence->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapEnd);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

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

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherActor->ActorHasTag(TEXT("Interactive")))
	{
		UE_LOG(LogTemp, Warning, TEXT("ENTERED"));
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor != this && OtherActor->ActorHasTag(TEXT("Interactive")))
	{
		UE_LOG(LogTemp, Warning, TEXT("EXITED"));
	}
}

