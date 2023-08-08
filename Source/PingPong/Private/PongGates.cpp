// PingPong by Liemander

#include "PongGates.h"
#include "Components/BoxComponent.h"

APongGates::APongGates()
{
	PrimaryActorTick.bCanEverTick = false;

	GatesCollision = CreateDefaultSubobject<UBoxComponent>("GatesCollision");
    GatesCollision->SetCollisionResponseToAllChannels(ECR_Block);
    GatesCollision->SetCollisionObjectType(ECC_WorldStatic);
}

void APongGates::BeginPlay()
{
	Super::BeginPlay();
}



