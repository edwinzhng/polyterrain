// Copyright Edwin Zhang

#include "VoxelEnvironment.h"
#include "VM/kernel.h"

using PolyVox::PagedVolume;
using PolyVox::MaterialDensityPair44;

// Sets default values
AVoxelEnvironment::AVoxelEnvironment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Seed = 128;
	NoiseOctaves = 3;
	NoiseFrequency = 0.01f;
	NoiseScale = 32.f;
	NoiseOffset = 0.f;
	EnvironmentHeight = 64.f;
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

void AVoxelEnvironment::PostInitializeComponents()
{
	VoxelVolume = MakeShareable(new PagedVolume<MaterialDensityPair44>(new VoxelEnvironmentPager(Seed, NoiseOctaves, NoiseFrequency, NoiseScale, NoiseOffset, EnvironmentHeight)));
	Super::PostInitializeComponents();
}


// VoxelEnvironmentPager function definitions

// Constructor
VoxelEnvironmentPager::VoxelEnvironmentPager(uint32 NoiseSeed, uint32 Octaves, float Frequency, float Scale, float Offset, float Height) : 
PagedVolume<MaterialDensityPair44>::Pager(), Seed(NoiseSeed), NoiseOctaves(Octaves), NoiseFrequency(Frequency), NoiseScale(Scale), NoiseOffset(Offset), EnvironmentHeight(Height)
{
		
}

// Called when when new chunk paged in
void VoxelEnvironmentPager::pageIn(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{
	anl::CKernel NoiseKernel;
	auto Zero = NoiseKernel.constant(0);
	auto One = NoiseKernel.constant(1);
	auto VerticalHeight = NoiseKernel.constant(EnvironmentHeight);

	// Gradient on vertical axis for ground plane
	auto VerticalGradient = NoiseKernel.divide(NoiseKernel.clamp(NoiseKernel.subtract(VerticalHeight, NoiseKernel.z()), Zero, VerticalHeight), VerticalHeight);

	// Turn gradient into two solids that represent ground and air
	auto VerticalSelect = NoiseKernel.select(Zero, One, VerticalGradient, NoiseKernel.constant(0.5), Zero);

	// Noise simple fBm generator for hills
	auto EnvironmentFractal = NoiseKernel.simplefBm(anl::BasisTypes::BASIS_SIMPLEX, anl::InterpolationTypes::INTERP_LINEAR, NoiseOctaves, NoiseFrequency, Seed);

	// Scale and offset the noise values
	auto EnvironmentScale = NoiseKernel.scaleOffset(EnvironmentFractal, NoiseScale, NoiseOffset);

	// Turn fractal into heightmap by setting height to Zero
	auto EnvironmentZScale = NoiseKernel.scaleZ(EnvironmentScale, Zero);

	//Apply the Z offset from fractal to ground plane.
	auto ApplyOffset = NoiseKernel.translateZ(VerticalSelect, EnvironmentZScale);

	anl::CNoiseExecutor EnvironmentExecutor(NoiseKernel);

	// Loop over chunk to apply noise
	for (int x = region.getLowerX(); x <= region.getUpperX(); x++)
	{
		for (int y = region.getLowerY(); y <= region.getUpperY(); y++)
		{
			for (int z = region.getLowerZ(); z <= region.getUpperZ(); z++) { 
				auto EvaluatedNoise = EnvironmentExecutor.evaluateScalar(x, y, z, ApplyOffset); 
				MaterialDensityPair44 Voxel; 
				bool bSolid = EvaluatedNoise > 0.5;

				Voxel.setDensity(bSolid ? 255 : 0);
				Voxel.setMaterial(bSolid ? 1 : 0);

				// Subtract lower corner position of the region from volume space position to get chunk space position
				Chunk->setVoxel(x - region.getLowerX(), y - region.getLowerY(), z - region.getLowerZ(), Voxel);
			}
		}
	}
}

// Called when chunk is paged out
void VoxelEnvironmentPager::pageOut(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{

}