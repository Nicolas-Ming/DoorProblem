// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;

UENUM()
enum class EDoorOpenStyle
{
	TwoWayHinge,
	SlidingRight,
	SlidingUp,
	SlidingLeft,
	SlidingDown,
	Shrinking,
	Disappearing,
	Roadkill
};


UCLASS()
class DOORPROBLEM_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned

	FRotator openRotation;
	FRotator beginningRotation;

	UPROPERTY(EditAnywhere)
	EDoorOpenStyle DoorType = EDoorOpenStyle::TwoWayHinge;
	UPROPERTY(EditAnywhere)
	float doorSpeed = 4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isAutomatic = false;
	UPROPERTY(BlueprintReadOnly)
	bool isDoorOpen = false;
	bool isBack = false;
	bool isFront = false;
	bool isMoving = false;
	UPROPERTY(EditAnywhere)
	bool canClose = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isLocked = false;
	float timer;
	float ratio;
	float doorXDistance;
	float doorZDistance;
	float doorDirection = 1;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* myDoor;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* myFrame;
	UPROPERTY(EditAnywhere)
	UBoxComponent* frontCollide;
	UPROPERTY(EditAnywhere)
	UBoxComponent* backCollide;
	virtual void BeginPlay() override;

	void TwoWayHinge(float Time);
	void SlidingRight(float Time);
	void SlidingUp(float Time);
	void SlidingLeft(float Time);
	void SlidingDown(float Time);
	void Shrinking(float Time);
	void Disappearing(float Time);
	void Roadkill(float Time);

public:	
	UFUNCTION(BlueprintCallable)
	void OpenDoor();
	UFUNCTION(BlueprintCallable)
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	void UnlockDoor();
	UFUNCTION(BlueprintCallable)
	void LockDoor();
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
