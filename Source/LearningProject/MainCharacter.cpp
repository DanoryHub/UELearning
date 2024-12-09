// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DrawDebugHelpers.h"

#include "Pickable.h"
#include "Inventory.h"
#include "Helpers.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerInventory = NewObject<UInventory>(GetTransientPackage());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	if (LocalPlayer != nullptr)
	{
		PlayerInputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (PlayerInputSystem != nullptr && PlayerMappingContext != nullptr)
		{
			PlayerInputSystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
	
}

void AMainCharacter::Move(const FInputActionInstance& Instance)
{
	FVector2D AxisInput = Instance.GetValue().Get<FVector2D>();

	if (!AxisInput.IsZero())
	{
		FVector ActorForwardVector = GetActorForwardVector();

		// Walking forward and backward
		if (AxisInput.Y != 0)
		{
			AddMovementInput(ActorForwardVector, AxisInput.Y);
		}

		// Walking left and right
		if (AxisInput.X != 0)
		{
			FVector RightVector = ActorForwardVector.RotateAngleAxis(90, FVector(0, 0, 1));

			AddMovementInput(RightVector, AxisInput.X);
		}
	}
}

void AMainCharacter::RotateCamera(const FInputActionInstance& Instance)
{
	FVector2D AxisInput = Instance.GetValue().Get<FVector2D>();

	if (!AxisInput.IsZero())
	{
		FVector ActorForwardVector = GetActorForwardVector();

		// Looking up and down
		if (AxisInput.Y != 0)
		{
			AddControllerPitchInput(AxisInput.Y * MouseSensitivity);
		}

		// Looking left and right
		if (AxisInput.X != 0)
		{
			AddControllerYawInput(AxisInput.X * MouseSensitivity);
		}
	}
}

void AMainCharacter::PerformJump(const FInputActionInstance& Instance)
{
	Jump();
}

void AMainCharacter::PerformGrab(const FInputActionInstance& Instance)
{
	if (ItemInSight != nullptr)
	{
		PlayerInventory->AddItem(ItemInSight);

		ItemInSight = nullptr;
	}
}

void AMainCharacter::PerformIntrospect(const FInputActionInstance& Instance)
{
	TArray<FString> ItemsInInventory = PlayerInventory->InspectItems();

	for (int i = 0; i < ItemsInInventory.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Number %d: %s"), i, *ItemsInInventory[i]);
	}

	UE_LOG(LogTemp, Warning, TEXT("Active Item: %s"), *PlayerInventory->InspectActiveItem());
}

void AMainCharacter::TraceLine()
{
	FHitResult OutHit;
	FVector LineStart = PlayerCamera->GetComponentLocation();
	FVector LineEnd = PlayerCamera->GetForwardVector() * LookLength + LineStart;

	// Player trace channel - ECC_GameTraceChannel1
	GetWorld()->LineTraceSingleByChannel(OutHit, LineStart, LineEnd, ECC_GameTraceChannel1);

	AActor* HitActor = OutHit.GetActor();

	if (HitActor != nullptr)
	{
		APickable* PickableActor = Cast<APickable>(HitActor);

		if (PickableActor != nullptr)
		{
			if (PickableActor != ItemInSight)
			{
				ItemInSight = PickableActor;
			}
			return;
		}
	}

	ItemInSight = nullptr;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NearPickableCounter > 0)
	{
		TraceLine();
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputActions["IA_Move"], ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	EnhancedInputComponent->BindAction(InputActions["IA_CameraRotation"], ETriggerEvent::Triggered, this, &AMainCharacter::RotateCamera);
	EnhancedInputComponent->BindAction(InputActions["IA_Jump"], ETriggerEvent::Triggered, this, &AMainCharacter::PerformJump);
	EnhancedInputComponent->BindAction(InputActions["IA_Grab"], ETriggerEvent::Triggered, this, &AMainCharacter::PerformGrab);
	EnhancedInputComponent->BindAction(InputActions["IA_InventoryIntrospect"], ETriggerEvent::Triggered, this, &AMainCharacter::PerformIntrospect);
}

void AMainCharacter::IncreaseNearPickableCounter()
{
	NearPickableCounter++;
}

void AMainCharacter::DecreaseNearPickableCounter()
{
	if (NearPickableCounter > 0)
	{
		NearPickableCounter--;
	}
}

