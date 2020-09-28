// Copyright Epic Games, Inc. All Rights Reserved.

#include "Combat_SystemCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

#include "Public/AI/NPC/NPC_PatrolPath_CPP.h"

//////////////////////////////////////////////////////////////////////////
// ACombat_SystemCharacter

ACombat_SystemCharacter::ACombat_SystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	pBox_Component = CreateDefaultSubobject<UBoxComponent>(TEXT("pBox_Component"));
	pBox_Component->SetupAttachment(GetMesh(), FName("s_hand_punch"));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ACombat_SystemCharacter::BeginPlay()
{
	Super::BeginPlay();

	//APlayerCameraManager* const cam_manager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//cam_manager->ViewPitchMin = -50.0f;
	//cam_manager->ViewPitchMax = 10.0f;

	// set material color of character
	UMaterialInstanceDynamic* const material_instance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	if (material_instance)
	{
		material_instance->SetVectorParameterValue("BodyColor", FLinearColor(0.0f, 1.0f, 1.0f, 0.1f));
		GetMesh()->SetMaterial(0, material_instance);
	}

	if (ANPC_PatrolPath_CPP* NPC = Cast<ANPC_PatrolPath_CPP>(pCharacter))
	{
		Attack_Delegate.AddDynamic(NPC, &ANPC_PatrolPath_CPP::NCP_is_Attacked);
	}



	pBox_Component->OnComponentBeginOverlap.AddDynamic(this, &ACombat_SystemCharacter::OnOverlapBegin);
	//pBox_Component->OnComponentHit.AddDynamic(this, &ACombat_SystemCharacter::OnHit);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACombat_SystemCharacter::Melee_Attack_Implementation()
{
	if (Attack_Delegate.IsBound())
	{
		Attack_Delegate.Broadcast();
	}

	if (ICombatInterfaceCPP* Interface = Cast<ICombatInterfaceCPP>(this))
	{
		Interface->Execute_Melee_Attack(this);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Melee_AttackCPP")));
	}
}

void ACombat_SystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ACombat_SystemCharacter::Melee_Attack_Implementation);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACombat_SystemCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACombat_SystemCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACombat_SystemCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACombat_SystemCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACombat_SystemCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACombat_SystemCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACombat_SystemCharacter::OnResetVR);
}

//void ACombat_SystemCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Melee_AttackCPP"), *OtherActor->GetName()));
//	//UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR: %s"), *OtherActor->GetName());
//}

void ACombat_SystemCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ANPC_PatrolPath_CPP* NPC = Cast<ANPC_PatrolPath_CPP>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("OnOverlapBegin from Player: %s"), *OtherActor->GetName()));
		NPC->TakeDamage(50.f, FDamageEvent(), nullptr, this);
		pBox_Component->SetGenerateOverlapEvents(false);	//when I hit NPC it prevents me from i.e hitting multiple times
	}
}

void ACombat_SystemCharacter::Spawn()
{
	//UWorld* world = GetWorld();
	//if (ToSpawn && world)
	//{
	//	FActorSpawnParameters spawnParams;
	//	spawnParams.Owner = this;

	//	//FRotator SpawnRotation(0.f,0.f,90.f);
	//	FRotator SpawnRotation;
	//	//FVector SpawnLocation(-1880.f, -3080.f, 218.f);
	//	FVector SpawnLocation = RootComponent->GetComponentLocation();

	//	world->SpawnActor<ANPCCPP>(ToSpawn, SpawnLocation, SpawnRotation, spawnParams);
	//}
}

void ACombat_SystemCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACombat_SystemCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ACombat_SystemCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ACombat_SystemCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACombat_SystemCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACombat_SystemCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACombat_SystemCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}