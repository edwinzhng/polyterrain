// Copyright Edwin Zhang

#include "VoxelMaze.h"
#include "VM/kernel.h"
#include "PolyVox/CubicSurfaceExtractor.h"
#include "PolyVox/Mesh.h"

using PolyVox::PagedVolume;
using PolyVox::MaterialDensityPair44;

// Sets default values
AVoxelMaze::AVoxelMaze()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Seed = 128;
	NoiseOctaves = 3;
	NoiseFrequency = 0.01f;
	NoiseScale = 32.f;
	NoiseOffset = 0.f;
	EnvironmentHeight = 64.f;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Environment Mesh"));
}

// Called when the game starts or when spawned
void AVoxelMaze::BeginPlay()
{
	PolyVox::Region ToExtract(PolyVox::Vector3DInt32(0, 0, 0), PolyVox::Vector3DInt32(127, 127, 63));
	auto ExtractedMesh = PolyVox::extractCubicMesh(VoxelVolume.Get(), ToExtract);
	auto DecodedMesh = PolyVox::decodeMesh(ExtractedMesh);

	auto Vertices = TArray<FVector>();
	auto Indices = TArray<int32>();
	auto Normals = TArray<FVector>();
	auto UV0 = TArray<FVector2D>();
	auto Colors = TArray<FColor>();
	auto Tangents = TArray<FProcMeshTangent>();

	for (uint32 i = 0; i < DecodedMesh.getNoOfIndices() - 2; i += 3)
	{
		// Get indices in reverse to ensure triangle is not upside down
		auto Index = DecodedMesh.getIndex(i + 2);
		auto Vertex2 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex2.position) * 100.f));

		Index = DecodedMesh.getIndex(i + 1);
		auto Vertex1 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex1.position) * 100.f));

		Index = DecodedMesh.getIndex(i);
		auto Vertex0 = DecodedMesh.getVertex(Index);
		Indices.Add(Vertices.Add(FPolyVoxVector(Vertex0.position) * 100.f));

		const FVector Edge1 = FPolyVoxVector(Vertex1.position - Vertex0.position);
		const FVector Edge2 = FPolyVoxVector(Vertex2.position - Vertex0.position);

		const FVector TangentX = Edge1.GetSafeNormal();
		FVector TangentZ = (Edge1 ^ Edge2).GetSafeNormal();

		for (int32 i = 0; i < 3; i++)
		{
			Tangents.Add(FProcMeshTangent(TangentX, false));
			Normals.Add(TangentZ);
		}
	}

	Mesh->CreateMeshSection(0, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
}

// Called every frame
void AVoxelMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoxelMaze::PostInitializeComponents()
{
	VoxelVolume = MakeShareable(new PagedVolume<MaterialDensityPair44>(new VoxelMazePager(Seed, NoiseOctaves, NoiseFrequency, NoiseScale, NoiseOffset, EnvironmentHeight)));
	Super::PostInitializeComponents();
}

// VoxelMazePager function definitions

// Constructor
VoxelMazePager::VoxelMazePager(uint32 NoiseSeed, uint32 Octaves, float Frequency, float Scale, float Offset, float Height) :
	PagedVolume<MaterialDensityPair44>::Pager(), Seed(NoiseSeed), NoiseOctaves(Octaves), NoiseFrequency(Frequency), NoiseScale(Scale), NoiseOffset(Offset), EnvironmentHeight(Height)
{

}

// Called when when new chunk paged in
void VoxelMazePager::pageIn(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{
	anl::CKernel NoiseKernel;
	auto Zero = NoiseKernel.constant(0);
	auto One = NoiseKernel.constant(1);
	auto VerticalHeight = NoiseKernel.constant(EnvironmentHeight);

	// Gradient on vertical axis for ground plane
	auto VerticalGradient = NoiseKernel.divide(NoiseKernel.clamp(NoiseKernel.subtract(VerticalHeight, NoiseKernel.z()), Zero, VerticalHeight), VerticalHeight);
	auto VerticalSelect = NoiseKernel.select(Zero, One, VerticalGradient, NoiseKernel.constant(0.5), Zero);

	// Noise simple fBm generator for hills
	auto EnvironmentFractal = NoiseKernel.simplefBm(anl::BasisTypes::BASIS_SIMPLEX, anl::InterpolationTypes::INTERP_LINEAR, NoiseOctaves, NoiseFrequency, Seed);

	auto EnvironmentScale = NoiseKernel.scaleOffset(EnvironmentFractal, NoiseScale, NoiseOffset);
	auto EnvironmentZScale = NoiseKernel.scaleZ(EnvironmentScale, Zero);

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
void VoxelMazePager::pageOut(const PolyVox::Region& region, PagedVolume<MaterialDensityPair44>::Chunk* Chunk)
{

}