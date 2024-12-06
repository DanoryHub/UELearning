// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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

	UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f"), AxisInput.X, AxisInput.Y);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputActions["IA_Move"], ETriggerEvent::Triggered, this, &AMainCharacter::Move);
}

