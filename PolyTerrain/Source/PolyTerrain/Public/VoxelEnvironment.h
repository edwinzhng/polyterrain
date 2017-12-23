// Copyright Edwin Zhang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelEnvironment.generated.h"

UCLASS()
class POLYTERRAIN_API AVoxelEnvironment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelEnvironment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
