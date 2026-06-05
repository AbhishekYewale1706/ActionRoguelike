
#include "RogueProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ARogueProjectileBase::ARogueProjectileBase()
{
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent=SphereComponent;
	SphereComponent->SetSphereRadius(16.f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed=2000.f;
	ProjectileMovementComponent->ProjectileGravityScale=0.f;
	
	LoopingNiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopingNiagaraComponent"));
	LoopingNiagaraComponent->SetupAttachment(SphereComponent);
	
	LoopingSoundComponent=CreateDefaultSubobject<UAudioComponent>(TEXT("LoopingSoundComponent"));
	LoopingSoundComponent->SetupAttachment(SphereComponent);
}



void ARogueProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentHit.AddDynamic(this,&ARogueProjectileBase::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(),true);
}

void ARogueProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	PlaySoundAndEffect();
	FVector HitFromDirection = GetActorRotation().Vector();;
	UGameplayStatics::ApplyPointDamage(OtherActor,10.f,HitFromDirection,Hit,GetInstigatorController(),this,DamageTypeClass);
	Destroy();
}

void ARogueProjectileBase::PlaySoundAndEffect()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ExplosionEffect,GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this,ExplosionSound,GetActorLocation());
}

