// Fill out your copyright notice in the Description page of Project Settings.


#include "MrLooman/Public/gMagic_h/GameplayActor_gMagicProjectile.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleEmitter.h"

#include "Particles/ParticleSystemComponent.h"

// Sets Construcotr
AMagicProjectile::AMagicProjectile()
{

	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Innit and Customization of all our components Where Instead of ticking boxing visually we simply write out and assign the values in the code

	

	//SPHERE COMP
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	//Setting this SPHERE HITBOX to our custom overlap channel {IMPORTANT}
	SphereComp->SetCollisionProfileName("MagicProjectile");


	//PARTICLE SYS
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	ParticleSystemComp->SetupAttachment(RootComponent);


	//PROJECTILE MOVMEMENT
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("	ProjectileMoveComp");
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
	ProjectileMovementComp->InitialSpeed = 8000;
	


	ProjectileMovementComp->bForceSubStepping = true;
	ProjectileMovementComp->MaxSimulationTimeStep = 0.03f;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Similar to the BP side pannels of popular dynmaic functions for {this} actor
	OnActorHit.AddDynamic(this, &AMagicProjectile::OnActorHitFunc);
		
}





// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{	
	Super::BeginPlay();
	
	
	//If {this} magic projectile does not collide with collision params within two seconds then DESPAWN it (a timer is set for this I believe)
	FTimerHandle LifeSpan;
	float Lifespan = 2.5f;
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AMagicProjectile::ExplodeProjectile_Implementation, Lifespan, true);
}










void AMagicProjectile::ExplodeProjectile_Implementation()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Hello, world!"));

	
	// Spawn particle effect at the projectile's location
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OnHitVFX, GetActorLocation());
}


void AMagicProjectile::OnActorHitFunc(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	float Lifespan = .25f;
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMagicProjectile::ExplodeProjectile_Implementation, Lifespan, false);
}

