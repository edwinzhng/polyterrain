// Copyright Edwin Zhang

#pragma once

#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelEnvironment.generated.h"

class VoxelEnvironmentPager : public PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Pager
{
public:
	// Constructor
	VoxelEnvironmentPager(uint32 NoiseSeed = 128, uint32 Octaves = 3, float Frequency = 0.01, float Scale = 32, float Offset = 0, float Height = 64);

	// Destructor
	virtual ~VoxelEnvironmentPager() {};

	// PagedVolume::Pager functions
	virtual void pageIn(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);
	virtual void pageOut(const PolyVox::Region& region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);

private:
	// Fractal seed
	uint32 Seed = 128;

	// Octaves for noise generator
	uint32 NoiseOctaves = 3;

	// Noise frequency
	float NoiseFrequency = 0.01;

	// Multiplier for output
	float NoiseScale = 32;
	
	// Offset added to output
	float NoiseOffset = 0;

	// Maximum height of generated environment in voxels
	float EnvironmentHeight = 64;
};


UCLASS()
class POLYTERRAIN_API AVoxelEnvironment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelEnvironment();

	// Called after C++ constructor and after property initialization
	virtual void PostInitializeComponents() override;

	// Fractal seed
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) int32 Seed;

	// Octaves for noise generator
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) int32 NoiseOctaves;

	// Noise frequency
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) float NoiseFrequency;

	// Multiplier for fractal output
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) float NoiseScale;

	// Offset added to fractal output
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) float NoiseOffset;

	// Maximum height of generated environment in voxels
	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, EditAnywhere) float EnvironmentHeight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TSharedPtr<PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>> VoxelVolume;
	
};
