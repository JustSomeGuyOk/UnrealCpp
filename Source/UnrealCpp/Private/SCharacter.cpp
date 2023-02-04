// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("USpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent); //the capsule essencially


	CameraComp = CreateDefaultSubobject<UCameraComponent>("UCameraComp");
	CameraComp->SetupAttachment(SpringArmComp); //attach to character but for distance and not first person

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;	//booleans start with b, coding standard

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");


}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);	//Orient rotation to movement, rotates characters smoother between frames.
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);  //Yaw is horizontal, Pitch is vertical rotation (like airplane?)
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);	//input trigger for attack
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);	//input trigger for attack
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f; //Dont want to pitch/roll into the sky/floor (up down)
	ControlRot.Roll = 0.0f;

	AddMovementInput(GetActorForwardVector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f; //Get the right axis for rotator (side to side on floor)
	ControlRot.Roll = 0.0f;

	//X = Forward (Red) (look up color in unreal for ref)
	//Y = Right (Green)
	//Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); //Y = Right Axis

	AddMovementInput(RightVector, Value);
}

void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");		//you can add sockets in unreal too
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);	//where the control is looking at, where in the actor to attach
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //specifying spawn rules;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams); //spawning is always done though GetWorld
}								
										   // spawn TM is just xyz transform matrix, these params just hold the general structure for the attack.

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp) 
	{
		InteractionComp->PrimaryInteract();
	}
}
