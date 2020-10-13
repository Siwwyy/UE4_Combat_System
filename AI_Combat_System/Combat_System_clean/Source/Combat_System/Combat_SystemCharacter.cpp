// Copyright Epic Games, Inc. All Rights Reserved.

#include "Combat_SystemCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Kismet/GameplayStatics.h"

#include "Public/AI/NPC/NPC_PatrolPath_CPP.h"
#include "Public/Components/Combat_Component_CPP.h"

//////////////////////////////////////////////////////////////////////////
// ACombat_SystemCharacter

ACombat_SystemCharacter::ACombat_SystemCharacter()
{
	//Member Variables Initialization
	fDamage = 5.f;
	CharacterType = Character_Type::Player;
	//////////////////////////////////////

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

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm



	pCombat_Component_CPP->Get_pSphereComponent()->SetupAttachment(GetMesh(), FName("hand_r"));

	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}


void ACombat_SystemCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (pDynamicMaterial)
	{
		pDynamicMaterial->SetVectorParameterValue("BodyColor", FLinearColor(0.0f, 1.0f, 1.0f, 0.1f));
		GetMesh()->SetMaterial(0, pDynamicMaterial);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACombat_SystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &ACombat_SystemCharacter::Melee_Attack_Implementation);
	PlayerInputComponent->BindAction("BlockHit", IE_Pressed, this, &ACombat_SystemCharacter::Block_Hit_Implementation);

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

//float ACombat_SystemCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
//	AController* EventInstigator, AActor* DamageCauser)
//{
//	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//
//	//custom logic in here
//	//if (ACombat_SystemCharacter* Player = Cast<ACombat_SystemCharacter>(DamageCauser))
//	//{
//	//	/*bIsAttacked = true;
//	//	pAttacking_Player = Player;*/
//	//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Take damage NPC: %s"), *DamageCauser->GetName()));
//	//	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Take damage Player: %s"), *DamageCauser->GetName()));
//	//	fHealth -= DamageAmount;
//
//	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("ACombat_SystemCharacter health: %f"), fHealth));
//	//}
//
//	bIsAttacked = true;
//	fHealth -= DamageAmount;
//
//	DrawDebugString(GetWorld(), DamageCauser->GetActorLocation(), FString::Printf(TEXT("ACombat_SystemCharacter health: %f"), fHealth), 0, FColor::Blue, 0.4f, false, 3.f);
//
//	if (fHealth <= 0.f)
//	{
//		Destroy();
//	}
//
//	return ActualDamage;
//}

//void ACombat_SystemCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (ANPC_PatrolPath_CPP* NPC = Cast<ANPC_PatrolPath_CPP>(OtherActor))
//	{
//		//
//		const float fPlayerDamage = 5.f;
//		const FVector Player_Bone_Location = GetMesh()->GetBoneLocation("hand_r");
//		//const FDamageEvent DamageEvent(FPointDamageEvent());
//		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%s OnOverlapBegin | Victim: %s"), *this->GetName() ,*OtherActor->GetName()));
//		NPC->TakeDamage(fPlayerDamage, FPointDamageEvent(), GetController() , this);
//		UAISense_Damage::ReportDamageEvent(GetWorld(), NPC, this, fPlayerDamage, NPC->GetActorLocation(), Player_Bone_Location);
//
//		//
//		//DrawDebugSphere(GetWorld(),
//		//	Player_Bone_Location,
//		//	10.f,
//		//	10,
//		//	FColor::Blue,
//		//	false,
//		//	2.f
//		//	);
//
//	
//		//TSubclassOf<UDamageType> P;
//		//const FHitResult HitInfo(ForceInit);
//		//UGameplayStatics::ApplyPointDamage(NPC, fPlayerDamage, GetActorLocation(), HitInfo, GetController(), this, P);
//		
//		pBox_Component->SetGenerateOverlapEvents(false);	//when I hit NPC it prevents me from i.e hitting multiple times	
//	}
//}

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