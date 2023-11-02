// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayInterface_Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameplayInterface_Interactable : public UInterface
{
	GENERATED_BODY()
};

/**
 *  DO NOT FUCK WITH ABOVE
 */
class MRLOOMAN_API IGameplayInterface_Interactable
{
	GENERATED_BODY()


//key below

	
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);







//key above




	
};
