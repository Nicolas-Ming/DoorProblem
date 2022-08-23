#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

class ADoor;

UCLASS()
class DOORPROBLEM_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	bool isPressured = false;
	UPROPERTY(EditAnywhere)
	float plateSpeed = 2;


	bool isMoving = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* myPlate;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool isAButton = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ADoor*> affectedDoors;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};