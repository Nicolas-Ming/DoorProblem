// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	myFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("thisFrame"));
	RootComponent = myFrame;
	myDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("thisDoor"));
	myDoor->SetupAttachment(RootComponent);
	frontCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("thisFrontCollider"));
	frontCollide->SetupAttachment(RootComponent);
	backCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("thisBackCollider"));	
	backCollide->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	
	beginningRotation = FRotator(0, 0, 0);
	openRotation =  FRotator(0, -90, 0);
	doorXDistance = 100 ;
	doorZDistance = 200 ;
	ratio = 0;
	timer = 0;
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isMoving) {

		switch (DoorType) {
		case EDoorOpenStyle::TwoWayHinge:
		{
			TwoWayHinge(DeltaTime);
			break;
		}
		case EDoorOpenStyle::SlidingRight:
		{
			SlidingRight(DeltaTime);
			break;
		}
		case EDoorOpenStyle::SlidingUp:
		{
			SlidingUp(DeltaTime);
			break;
		}
		case EDoorOpenStyle::SlidingLeft:
		{
			SlidingLeft(DeltaTime);
			break;
		}
		case EDoorOpenStyle::SlidingDown:
		{
			SlidingDown(DeltaTime);
			break;
		}
		case EDoorOpenStyle::Shrinking:
		{
			Shrinking(DeltaTime);
			break;
		}
		case EDoorOpenStyle::Disappearing:
		{
			Disappearing(DeltaTime);
			break;
		}
		case EDoorOpenStyle::Roadkill:
		{
			Roadkill(DeltaTime);
			break;
		}
		}
	}
	
}

void ADoor::TwoWayHinge(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeRotation(FMath::Lerp(beginningRotation, openRotation * doorDirection, ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeRotation(FMath::Lerp(beginningRotation, openRotation * doorDirection, ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::SlidingRight(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0),FVector(-doorXDistance,0,0), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(-doorXDistance,0,0), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::SlidingUp(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(0, 0, doorZDistance ), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(0, 0, doorZDistance), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::SlidingLeft(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(doorXDistance, 0, 0), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(doorXDistance, 0, 0), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::SlidingDown(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(0, 0, -doorZDistance), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeLocation(FMath::Lerp(FVector(0, 0, 0), FVector(0, 0, -doorZDistance), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::Shrinking(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeScale3D(FMath::Lerp(FVector(1, 1, 1), FVector(0, 0, 0), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeScale3D(FMath::Lerp(FVector(1, 1, 1), FVector(0, 0, 0), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::Disappearing(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeScale3D(FMath::Lerp(FVector(1, 1, 1), FVector(0, 0, 0), ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeScale3D(FMath::Lerp(FVector(1, 1, 1), FVector(0, 0, 0), ratio));
		if (ratio == 0) isMoving = false;
	}
}
void ADoor::Roadkill(float Time) {
	if (isDoorOpen == true) {
		timer += Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);

		myDoor->SetRelativeRotation(FMath::Lerp(FRotator(0, 0, 0), FRotator(0, 0, 90) * doorDirection, ratio));

		if (ratio == 1) isMoving = false;
	}
	else if (isDoorOpen == false && canClose) {
		timer -= Time;
		ratio = FMath::Clamp(timer * doorSpeed, 0, 1);
		myDoor->SetRelativeRotation(FMath::Lerp(FRotator(0, 0, 0), FRotator(0, 0, 90) * doorDirection, ratio));
		if (ratio == 0) isMoving = false;
	}
}

void ADoor::OpenDoor() {
	isDoorOpen = true;
	if (ratio == 0) {
		if (frontCollide->IsOverlappingActor(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))) {
			doorDirection = -1;
		}
		else if (backCollide->IsOverlappingActor(Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))) {
			doorDirection = 1;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ratio = %f"), ratio));
	}

	if (isMoving) {
		//Do not change timer, it is in motion
	}
	else {
		timer = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("We should be movin")));
		isMoving = true;
	}
}
void ADoor::CloseDoor() {
	isDoorOpen = false;
	if (isMoving) {
		//Do not change timer, it is in motion
	}
	else {
		ratio = 1;
		isMoving = true;
	}
	
}
