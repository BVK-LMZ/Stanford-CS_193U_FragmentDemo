// Fill out your copyright notice in the Description page of Project Settings.


#include "MrLooman/Public/coolAttributes_h/GameplayComponent_Attributes.h"

// Sets default values for this component's properties
UGameplayComponent_Attributes::UGameplayComponent_Attributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameplayComponent_Attributes::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameplayComponent_Attributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

