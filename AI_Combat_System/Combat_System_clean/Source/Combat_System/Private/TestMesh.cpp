#include "TestMesh.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"

#include "UE4D_Logger.h"

ATestMesh::ATestMesh()
{
	PrimaryActorTick.bCanEverTick = true;

	pSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("pSceneComponent"));
	RootComponent = pSceneComponent;


	pSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("pSphereComponent"));
	pSphereComponent->InitSphereRadius(40.0f);
	pSphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	pSphereComponent->SetupAttachment(pSceneComponent);


	pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pStaticMeshComponent"));
	pStaticMeshComponent->SetStaticMesh(pStaticMesh);
	pStaticMeshComponent->SetupAttachment(pSceneComponent);

	
}

void ATestMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float blend = 0.5f + static_cast<float>(FMath::Cos(GetWorld()->TimeSeconds) / 2);
	pDynamicMaterial->SetScalarParameterValue(TEXT("Blend"), blend);


	
	//UE_LOG(LogTemp, Warning, FString::Printf(TEXT(" DDDD %s"), blend));
	//UE_LOG(LogTemp, Warning, TEXT("%f"), *FString::Printf(TEXT(" %f"), blend));

	UE4D::UE4D_Log("DUPA");
}

void ATestMesh::BeginPlay()
{
	Super::BeginPlay();
	//UMaterial* Material = CreateDefaultSubobject<UMaterial>(TEXT("MyMaterial"));
	//Material->SetVectorParameterValueEditorOnly("CubeMaterial", FLinearColor(0.0f, 1.0f, 1.0f, 0.1f));
	//pStaticMeshComponent->SetMaterial(0, Material);

	//// set material color of character
	//UMaterialInstanceDynamic* const material_instance = UMaterialInstanceDynamic::Create(pStaticMeshComponent->GetMaterial(0), this);
	//if (material_instance)
	//{
	//	material_instance->SetVectorParameterValue("Blend", FLinearColor(0.0f, 1.0f, 1.0f, 0.1f)); 
	//	pStaticMeshComponent->SetMaterial(0, material_instance);
	//}




	pDynamicMaterial = UMaterialInstanceDynamic::Create(pStaticMeshComponent->GetMaterial(0), NULL);
	pStaticMeshComponent->SetMaterial(0, pDynamicMaterial);
}