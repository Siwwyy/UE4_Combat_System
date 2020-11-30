
#include "../../../Public/AI/Patrol_Path/Patrol_Path_CPP.h"


APatrol_Path_CPP::APatrol_Path_CPP()
{
	PrimaryActorTick.bCanEverTick = false;

	pSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("pSceneComponent"));
	RootComponent = pSceneComponent;
}