// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Helpers.h"
#include "GameFramework/Actor.h"
#include "Pickable.generated.h"

// Forward declaration
class USphereComponent;

UCLASS()
class LEARNINGPROJECT_API APickable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	USphereComponent* VisibilityActivationSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TransferableData")
	FPickableData ItemData;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FPickableData* GetItemData();

	UFUNCTION(BlueprintCallable)
	void SetPhysics(bool IsPhysicsEnabled);

	UFUNCTION(BlueprintCallable)
	void ApplyForce(FVector ForceDirection, float ForceStrength);
};
