// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayComponent_Interactable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MRLOOMAN_API UGameplayComponent_Interactable : public UActorComponent
{
	
	GENERATED_BODY()
	



#pragma region //* actor boiler plate */


protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;



	// Called every frame and IG I do need it like this and virtually overriden LOL
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion


public:
	// Constructor Declaration 
	UGameplayComponent_Interactable();
	

	//Component That will provide functionality to the player, in this case a interact ray trace!
	//The ray checks if hit actor implements interface and then has that actor that implements it call it's BP implemented function
	void PrimaryInteract();


	
};
