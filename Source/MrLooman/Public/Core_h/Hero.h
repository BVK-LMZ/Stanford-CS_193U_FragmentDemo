#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Hero.generated.h"

UCLASS()
class MRLOOMAN_API AHero : public ACharacter
{
	
public:
	
	GENERATED_BODY()


#pragma region //* core coponents */	
	//PIC
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Gameplay Components
	
	//<Interactable>
	UPROPERTY(VisibleAnywhere)
	class UGameplayComponent_Interactable* InteractableComp;
	//<gMagic>
	UPROPERTY(VisibleAnywhere)
	class UGameplayComponent_gMagic* GMagicComp;
#pragma endregion 	

#pragma region /** CAMERAs */
	
	//tps camera
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* TPSCameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TPSFollowCamera;
	
	//fps camera
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* FPSCameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPSFollowCamera;
#pragma endregion

	

#pragma region /** Input */
public:

	//Needed to innit Mapping Context from BP and core PIC functionality
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	// Boiler Plate Movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Boiler Plate Looking Around
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Boiler Plate Jump
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;
	
	// Toggle between Cameras
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwitchCameraAction;
	
	// Short Interact Ray from Interact Projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;
	
	#pragma region //* gMagic Component */
	
	// Primary Attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* PrimaryAttackAction;
	// Double Attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* DoubleAttackAction;
	// MegaJumpAttack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MegaJumpAction;

	// Teleport Attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* TeleportAttackAction;


	//switch to black hole soon
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MegaJumpAction;*/
#pragma endregion

#pragma endregion 


#pragma region //* camera and movement member functions and variables */
	UFUNCTION()
	void SwitchCamera();
	
	UFUNCTION()
	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

		
	UFUNCTION(BlueprintCallable)
	void ToggleCameraView(); //Camera flip func
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CUSTOM)
	bool bIsFirstPersonView; // for camera flipping (bool check on func to change cameras)

#pragma endregion


	
#pragma region //* animations n fx*/

	//ANIM MONTAGEs
	UPROPERTY(EditAnywhere,Category = CUSTOM)
	UAnimMontage* PrimaryAttackAnimA;

	UPROPERTY(EditAnywhere,Category = CUSTOM)
	UAnimMontage* PrimaryAttackAnimB;

	UPROPERTY(EditAnywhere,Category = CUSTOM)
	UAnimMontage* PrimaryAttackAnimC;

	UPROPERTY(EditAnywhere,Category = CUSTOM)
	UAnimMontage* MegaJumpActionAnim;


	
#pragma endregion 


#pragma region //* gMagic Component All */

	
	
#pragma region	 //* gMagic Primary Attack  */
	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void ResetPrimaryAttackCooldown();

	UFUNCTION()
	void PrimaryAttack_TimeElapsed();
	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	bool bIsPrimaryAttackOnCooldown;
	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	FTimerHandle TimerHandle_PrimaryAttack;
#pragma endregion 

	
#pragma region //* gMagic Double Attack */
	
	UFUNCTION()
	void DoubleAttack();
	void DoubleAttack_TimeElapsed();

	UFUNCTION()
	void ResetDoubleAttackCooldown();


	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	bool bIsDoubleAttackOnCooldown;
	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	FTimerHandle TimerHandle_DoubleAttack;
	
#pragma endregion

	
#pragma region //* gMagic MegaJump Attack */	
	//local var for MegaJump Attack
	 
	UFUNCTION()
	void MegaJumpAttack();
	void MegaJumpAttack_TimeElapsed();

	UFUNCTION()
	void ResetMegaJumpAttackCooldown();


	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	bool bIsMegaJumpAttackOnCooldown;
	
	UPROPERTY(EditAnywhere, Category = CUSTOM)
	FTimerHandle TimerHandle_MegaJumpAttack;
	
	
#pragma endregion


#pragma region //* gMagic Teleport Attack */	
	//local var for MegaJump Attack
	 
	UFUNCTION(BlueprintImplementableEvent)
	void TeleportAttack();

	UFUNCTION()
	void StartNativeBP_TeleportAttack();

	
#pragma endregion

	
#pragma endregion 
	



	//More / ETC
	public:
	AHero();

protected:
	virtual void BeginPlay();
	void Tick(float DeltaTime);
	
	
	UFUNCTION(BlueprintCallable)
	void PrimaryInteract(); //placeholder for a component function

};
