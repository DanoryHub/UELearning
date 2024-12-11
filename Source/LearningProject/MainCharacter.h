// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//Forward declaration
class APickable;
class UInventory;
class UInputAction;
class UArrowComponent;
class UCameraComponent;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS()
class LEARNINGPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move(const FInputActionInstance& Instance);

	UFUNCTION()
	void RotateCamera(const FInputActionInstance& Instance);

	UFUNCTION()
	void PerformJump(const FInputActionInstance& Instance);

	UFUNCTION()
	void PerformGrab(const FInputActionInstance& Instance);

	UFUNCTION()
	void PerformIntrospect(const FInputActionInstance& Instance);

	UFUNCTION()
	void PerformItemDrop(const FInputActionInstance& Instance);

	void TraceLine();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TMap<FString, UInputAction*> InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	USceneComponent* DropSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* DropOrientation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float MouseSensitivity = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WorldInteraction")
	float LookLength = 500.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float DropForceStrength = 100.0;

	int32 NearPickableCounter = 0;

	UInventory* PlayerInventory;

	APlayerController* PlayerController;

	UEnhancedInputLocalPlayerSubsystem* PlayerInputSystem;

	APickable* ItemInSight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void IncreaseNearPickableCounter();

	UFUNCTION(BlueprintCallable)
	void DecreaseNearPickableCounter();

};
