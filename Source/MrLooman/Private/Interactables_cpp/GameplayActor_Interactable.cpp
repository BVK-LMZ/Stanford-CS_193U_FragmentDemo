// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables_h/GameplayActor_Interactable.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

void AGameplayActor_Interactable::Interact_Implementation(APawn* InstigatorPawn)
{
	
	//You the player have raycasted and thus told this gameplay actor to call it's interactable function 
	//There is a text string printing from here and then the child (bp will elaborate further) as long as you implement the interface within the BP
	
	IGameplayInterface_Interactable::Interact_Implementation(InstigatorPawn);
	UE_LOG(LogTemp, Warning, TEXT("printed from interactable actor"));

}

// Sets default values
AGameplayActor_Interactable::AGameplayActor_Interactable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region //*Component Innit*/
	//Set up commponents and then their attachments.
	// MeshComp1
	MeshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp1"));
	RootComponent = MeshComp1;
	// MeshComp2
	MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));
	MeshComp2->SetupAttachment(MeshComp1);
	// CollisionComp
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));

	//No attachment for this collision component how bad could manually setting it up be?
	//CollisionComp->SetupAttachment(MeshComp2);


	//Only the box collision will gener8 overlaps events
	MeshComp1->SetGenerateOverlapEvents(false);
	MeshComp2->SetGenerateOverlapEvents(false);
	CollisionComp->SetGenerateOverlapEvents(true);
#pragma endregion
	
}

// Called when the game starts or when spawned
void AGameplayActor_Interactable::BeginPlay()
{
	Super::BeginPlay();
	
}



