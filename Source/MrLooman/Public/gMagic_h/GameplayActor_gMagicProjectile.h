// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleEmitter.h"
#include "GameplayActor_gMagicProjectile.generated.h"

UCLASS()
class MRLOOMAN_API AMagicProjectile : public AActor
{
	GENERATED_BODY()


#pragma region //* actor boilerplate */
protected:
	// Sets default values for this actor's properties
	AMagicProjectile();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion 

#pragma region //* components */
	UPROPERTY(VisibleAnywhere, Category = "CUSTOM")
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "CUSTOM")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere, Category = "CUSTOM")
	UParticleSystemComponent* ParticleSystemComp;

	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* OnHitVFX;
	

#pragma endregion 

	
public:




	//Some lookings that Magic Projectile Needs !
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ExplodeProjectile();
	

	UFUNCTION()
	void OnActorHitFunc(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);


	//needed for destroy self
	FTimerHandle DelayTimerHandle;

	
};
