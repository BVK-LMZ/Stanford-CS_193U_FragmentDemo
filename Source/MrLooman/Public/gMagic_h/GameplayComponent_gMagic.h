// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayComponent_gMagic.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRLOOMAN_API UGameplayComponent_gMagic : public UActorComponent
{
	GENERATED_BODY()
protected:
	//assign class to the spawn actor
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
public:	
	// Sets default values for this component's properties
	UGameplayComponent_gMagic();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PrimaryAttack();


};
