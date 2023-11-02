// Fill out your copyright notice in the Description page of Project Settings.


#include "MrLooman\Public\gMagic_h\GameplayComponent_gMagic.h"
#include "Engine/Engine.h"
#include "Interactables_h/GameplayInterface_Interactable.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values for this component's properties
UGameplayComponent_gMagic::UGameplayComponent_gMagic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	
	// ...
}


// Called when the game starts
void UGameplayComponent_gMagic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGameplayComponent_gMagic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGameplayComponent_gMagic::PrimaryAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT(""));

	// Define the object types to query for collision
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	// Get the owner of this gameplay component
	AActor* MyOwner = GetOwner();
	
	// Get the location and rotation of the owner's eyes
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	// Calculate the end point of the line trace by extending the eye location forward by 1000 units
	FVector End = EyeLocation + (EyeRotation.Vector() * 1500);




	
	TArray<FHitResult> Hits;



	//For the SphereSweep
	float ShapeRadius = 30.f;
	FCollisionShape Shape;
	Shape.SetSphere(ShapeRadius);

	// Perform a sweep test to check for collision between the line trace and objects of ECC_WorldDynamic type
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);


	for (const FHitResult& Hit : Hits)
	{
		
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{

			//THIS WILL DRAW BECAUSE WE ARE HITTING the player and that counts as a hit actor
			
			// Draw a debug line representing the line trace
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 2.f, 0, 2.f);
			
			if (HitActor->Implements<UGameplayInterface_Interactable>())
			{
				// Draw a debug sphere at the impact point of the line trace
				DrawDebugSphere(GetWorld(), Hit.ImpactPoint, ShapeRadius, 32, FColor::Green, false, 2.f);
				
				// If the hit actor implements the UGameplayInterface_Interactable interface, execute the Interact function
				APawn* ThisPawn = Cast<APawn>(MyOwner);
				IGameplayInterface_Interactable::Execute_Interact(HitActor, ThisPawn);
			}
		}




		
	}


	// Handle Spawning The Projectile Slightly In Front Of The Character !
	{
		//PARAMS
		FHitResult HitResult;
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform;
		APawn* ThisPawn = Cast<APawn>(GetOwner());


		
		if (ThisPawn && ThisPawn->Controller)
		{
			FVector sLocation = ThisPawn->GetActorLocation();
			FRotator CameraRotation = ThisPawn->Controller->GetControlRotation();
			FQuat sRotation = CameraRotation.Quaternion(); // Create a FQuat from the rotation vector

			SpawnTransform.SetLocation(sLocation);
			SpawnTransform.SetRotation(sRotation);

			GetWorld()->SpawnActor(ProjectileClass, &SpawnTransform, SpawnParam);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Projectile Fired"));
		}
	}
	// Handle Spawning The Projectile Slightly In Front Of The Character !
	
}


//void UGameplayComponent_gMagic::TeleportAttack()


