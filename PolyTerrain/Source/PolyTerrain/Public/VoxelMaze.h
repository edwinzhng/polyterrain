// Copyright Edwin Zhang

#pragma once

#include "ProceduralMeshComponent.h"
#include "PolyVox/Vector.h"
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelMaze.generated.h"

struct FPolyVoxVector : public FVector
{
	FORCEINLINE FPolyVoxVector()
	{}

	explicit FORCEINLINE FPolyVoxVector(EForceInit E) : FVector(E)
	{}

	FORCEINLINE FPolyVoxVector(float InX, float InY, float InZ) : FVector(InX, InY, InX)
	{}

	FORCEINLINE FPolyVoxVector(const FVector& VectorIn)
	{
		FVector::operator = (VectorIn);
	}

	FORCEINLINE FPolyVoxVector(const PolyVox::Vector3DFloat& VectorIn)
	{
		FPolyVoxVector::operator = (VectorIn);
	}

	FORCEINLINE FVector& operator = (const PolyVox::Vector3DFloat& Other)
	{
		this->X = Other.getX();
		this->Y = Other.getY();
		this->Z = Other.getZ();

		DiagnosticCheckNaN();

		return *this;
	}
};

class VoxelMazePager : public PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Pager
{
public:
	// Constructor
	VoxelMazePager(uint32 NoiseSeed = 128, uint32 Octaves = 3, float Frequency = 0.01, float Scale = 32, float Offset = 0, float Height = 64);

	// Destructor
	virtual ~VoxelMazePager() {};

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
class POLYTERRAIN_API AVoxelMaze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelMaze();

	// Called after C++ constructor and after property initialization
	virtual void PostInitializeComponents() override;

	UPROPERTY(Category = "Voxel Environment", BlueprintReadWrite, VisibleAnywhere) class UProceduralMeshComponent* Mesh;
	
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
