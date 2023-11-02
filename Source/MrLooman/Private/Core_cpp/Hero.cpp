#include "core_h/Hero.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactables_h/GameplayComponent_Interactable.h"
#include "MrLooman/Public/Core_h/Hero.h"
#include "Engine/Engine.h"
#include "gMagic_h/GameplayComponent_gMagic.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"




//Constructor, innit of AHero Settings and Stuff
AHero::AHero()
{
	
	//These Components Provide Further Modular Functionality !
	InteractableComp = CreateDefaultSubobject<UGameplayComponent_Interactable>(TEXT("INTERACTABLE COMP")); 
	GMagicComp = CreateDefaultSubobject<UGameplayComponent_gMagic>(TEXT("GMagic COMP")); 




#pragma region /**Camera Settings*/
	// Don't rotate when the controller rotates {Camera Settings}
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//TPS CAMERA
	// Create a camera boom (pulls in towards the player if there is a collision)
	TPSCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("fpsCameraBoom"));
	TPSCameraBoom->SetupAttachment(RootComponent);
	TPSCameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	TPSCameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	// Create a follow camera
	TPSFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("fpsFollowCamera"));
	TPSFollowCamera->SetupAttachment(TPSCameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	TPSFollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//FPS CAMERA
	// Create a camera boom (pulls in towards the player if there is a collision)
	FPSCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("tpsCameraBoom"));
	FPSCameraBoom->SetupAttachment(RootComponent);
	FPSCameraBoom->TargetArmLength = 1.0f; // The camera follows at this distance behind the character	
	FPSCameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FPSFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("tpsFollowCamera"));
	FPSFollowCamera->SetupAttachment(FPSCameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FPSFollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
#pragma endregion


	


#pragma region /** Movement Innit */
	
		// Set size for collision capsule  (technically is it movement?!)
		GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
		// Configure character movement
    	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
    
    	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
    	// instead of recompiling to adjust them
    	GetCharacterMovement()->JumpZVelocity = 700.f;
    	GetCharacterMovement()->AirControl = 0.35f;
    	GetCharacterMovement()->MaxWalkSpeed = 500.f;
    	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++
#pragma endregion
	
}



#pragma region //* P.I.C */
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	{
		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
			//* Base Inputs */
			//Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);

			//Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);
			
			//Jumping
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

			//Switch Camera
			EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Triggered, this, &AHero::SwitchCamera);

			//* Base Inputs  End*/


			//* Component Inputs */	
			//Interacting
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AHero::PrimaryInteract);

			//Primary Attack
			EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &AHero::PrimaryAttack);		//Not Implemented Yet!
			
			//Double Attack
			EnhancedInputComponent->BindAction(DoubleAttackAction,ETriggerEvent::Triggered,this, &AHero::DoubleAttack);

			//MegaJump Attack
			EnhancedInputComponent->BindAction(MegaJumpAction,ETriggerEvent::Triggered,this,&AHero::MegaJumpAttack);

			//MegaJump Attack
			EnhancedInputComponent->BindAction(TeleportAttackAction,ETriggerEvent::Triggered,this,&AHero::StartNativeBP_TeleportAttack);
			
			//BlackHole Attack
			//EnhancedInputComponent->BindAction(BlackHoleAttackAction,ETriggerEvent::Triggered,this,&AHero::);
			//coming soon
		}

	}
}
#pragma endregion 




// Called when the game starts or when spawned
void AHero::BeginPlay()
{
		// Call the base class  
		Super::BeginPlay();

		//SET UP PIC
		//Add Input Mapping Context
		if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


#pragma region /** Camera && Movement Functions */
void AHero::ToggleCameraView()
{
	bIsFirstPersonView = !bIsFirstPersonView;
}
void AHero::Move (const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void AHero::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		
	}
}
void AHero::SwitchCamera()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello, World!"));
	// Switch the camera mode
	bIsFirstPersonView = !bIsFirstPersonView;

	// Enable/disable camera components based on the camera mode with the preconfigured Camera Nodes !
	if (bIsFirstPersonView)
	{
		TPSCameraBoom->Deactivate();
		TPSFollowCamera->Deactivate();
		FPSCameraBoom->Activate();
		FPSFollowCamera->Activate();
		GetMesh()->SetVisibility(false); // Hide the character skeleton mesh

	}
	else
	{
		TPSCameraBoom->Activate();
		TPSFollowCamera->Activate();
		FPSCameraBoom->Deactivate();
		FPSFollowCamera->Deactivate();
		GetMesh()->SetVisibility(true); // Hide the character skeleton mesh

	}
	
}
#pragma endregion


// gMagicComponent (WITHIN Hero)*/
#pragma region //* Primary Attack*/
void AHero::PrimaryAttack()
{
	
	if (!bIsPrimaryAttackOnCooldown)
	{
		PlayAnimMontage(PrimaryAttackAnimA);
		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this, &AHero::PrimaryAttack_TimeElapsed,.35f);
		bIsPrimaryAttackOnCooldown = true;
	}
}



void AHero::PrimaryAttack_TimeElapsed()
{
	GMagicComp->PrimaryAttack();
	ResetPrimaryAttackCooldown();
}

void AHero::ResetPrimaryAttackCooldown()
{
	
	bIsPrimaryAttackOnCooldown = false;
}
#pragma endregion 
#pragma region //* Double Attack */

void AHero::DoubleAttack()
{
	
	if (!bIsDoubleAttackOnCooldown)
	{
		PlayAnimMontage(PrimaryAttackAnimB);
		GMagicComp->PrimaryAttack();
		GetWorldTimerManager().SetTimer(TimerHandle_DoubleAttack,this, &AHero::DoubleAttack_TimeElapsed,.35f);
		bIsDoubleAttackOnCooldown = true;
	}
	
}



void AHero::DoubleAttack_TimeElapsed()
{
	PlayAnimMontage(PrimaryAttackAnimA);
	
	GMagicComp->PrimaryAttack();
	
	
	ResetDoubleAttackCooldown();
}

void AHero::ResetDoubleAttackCooldown()
{
	
	bIsDoubleAttackOnCooldown = false;
}
#pragma endregion	
#pragma region//*MegaJumpAttack//
void AHero::MegaJumpAttack()
{
	if (!bIsMegaJumpAttackOnCooldown)
	{
		PlayAnimMontage(MegaJumpActionAnim);

		FVector LaunchVelocity = FVector(0.0f, 0.0f, (GetCharacterMovement()->Velocity.Z + GetCharacterMovement()->JumpZVelocity + GetCharacterMovement()->JumpZVelocity));
		LaunchCharacter(LaunchVelocity, true, false);
		
		
		GetWorldTimerManager().SetTimer(TimerHandle_MegaJumpAttack,this, &AHero::MegaJumpAttack_TimeElapsed,2.5f);
		bIsMegaJumpAttackOnCooldown = true;
	}
}


void AHero::MegaJumpAttack_TimeElapsed()
{
	ResetMegaJumpAttackCooldown();
}

void AHero::ResetMegaJumpAttackCooldown()
{
	bIsMegaJumpAttackOnCooldown = false;
}

#pragma endregion	
#pragma region //* Teleport Attack */


void TeleportAttack_Implementation()
{
	//The Blueprint implementation will take precedence.
}

void AHero::StartNativeBP_TeleportAttack()
{
	TeleportAttack_Implementation();
}

#pragma endregion 






//Component Calling Functions
void AHero::PrimaryInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Hello World"));
	PlayAnimMontage(PrimaryAttackAnimB);
	InteractableComp->PrimaryInteract();
	
}





