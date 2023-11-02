// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayInterface_Interactable.h"
#include "GameFramework/Actor.h"
#include "GameplayActor_Interactable.generated.h"

UCLASS()
class MRLOOMAN_API AGameplayActor_Interactable : public AActor, public IGameplayInterface_Interactable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	

	//Constructor Deceleration 
	AGameplayActor_Interactable();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override; //Implement this in bp!


#pragma region //* components */

	//these two are smart ptrs for some reason
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp2;
	
	//couldn't get this one working as a smart pointer!
	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionComp;
#pragma endregion 
	

};
