// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTeleportProjectile.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



ARogueTeleportProjectile::ARogueTeleportProjectile()
{
	ProjectileMovementComponent->InitialSpeed = 6000.0f;
}

void ARogueTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::StartDelayedTeleport, DetonateDelay);
}

void ARogueTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	StartDelayedTeleport();
}

void ARogueTeleportProjectile::StartDelayedTeleport()
{
	PlaySoundAndEffect();
	ProjectileMovementComponent->StopMovementImmediately();
	LoopingNiagaraComponent->Deactivate();
	LoopingSoundComponent->Stop();
	SetActorEnableCollision(false);
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::HandleTeleportation, TeleportSecondaryDelay);
}

void ARogueTeleportProjectile::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();
	// todo: We should check if instigator is still valid/alive once we implement Death
	check(ActorToTeleport);
	
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	Destroy();
}