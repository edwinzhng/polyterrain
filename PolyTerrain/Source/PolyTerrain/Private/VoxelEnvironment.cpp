// Copyright Edwin Zhang

#include "VoxelEnvironment.h"
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"

// Sets default values
AVoxelEnvironment::AVoxelEnvironment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelEnvironment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

