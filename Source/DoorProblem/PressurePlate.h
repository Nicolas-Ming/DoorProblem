#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"


UENUM()
enum class EKeysPP
{
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight
};

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

	void pressurePlateMove(float Time);

	UPROPERTY(EditAnywhere)
	EKeysPP KeyType = EKeysPP::One;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


