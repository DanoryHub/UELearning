// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickable.h"
#include "Components/SphereComponent.h"

#include "MainCharacter.h"

// Sets default values
APickable::APickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(Mesh);

	VisibilityActivationSphere = CreateDefaultSubobject<USphereComponent>("TraceActivationSphere");
	VisibilityActivationSphere->SetupAttachment(RootComponent);

	// Setup on begin overlap event
	VisibilityActivationSphere->OnComponentBeginOverlap.AddDynamic(this, &APickable::OnSphereBeginOverlap);

	// Setup on begin overlap event
	VisibilityActivationSphere->OnComponentEndOverlap.AddDynamic(this, &APickable::OnSphereEndOverlap);
	
}

// Called when the game starts or when spawned
void APickable::BeginPlay()
{
	Super::BeginPlay();

	ItemData.ID = FGuid::NewGuid().ToString();
}

void APickable::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!AllowedLineTrace)
	{
		return;
	}

	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);

	if (Character != nullptr)
	{
		Character->IncreaseNearPickableCounter();
	}
}

void APickable::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!AllowedLineTrace)
	{
		return;
	}

	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);

	if (Character != nullptr)
	{
		Character->DecreaseNearPickableCounter();
	}
}

// Called every frame
void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FPickableData* APickable::GetItemData()
{
	return &ItemData;
}

void APickable::SetPhysics(bool IsPhysicsEnabled)
{
	Mesh->SetSimulatePhysics(IsPhysicsEnabled);
}

void APickable::ForbidLineTrace()
{
	AllowedLineTrace = false;
}

void APickable::AllowLineTrace()
{
	AllowedLineTrace = true;
}

void APickable::AttachToComponent(USceneComponent* ComponentToAttachTo)
{
	Mesh->AttachToComponent(ComponentToAttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APickable::ApplyForce(FVector ForceDirection, float ForceStrength)
{
	Mesh->AddForce(ForceDirection * ForceStrength);
}

