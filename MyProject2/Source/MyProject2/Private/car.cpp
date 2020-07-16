// Fill out your copyright notice in the Description page of Project Settings.


#include "car.h"

// Sets default values
Acar::Acar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	RootComponent = Body;

	RR = CreateDefaultSubobject<USceneComponent>(FName("RR"));
	RR->SetupAttachment(Body);

	SceneAxleConstraintRR = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SceneAxleConstraintRR"));
	SceneAxleConstraintRR->SetupAttachment(RR);

	AxleRR = CreateDefaultSubobject<USphereComponent>(FName("AxleRR"));
	AxleRR->SetupAttachment(RR);

	AxleWheelConstraintRR = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraintRR"));
	AxleWheelConstraintRR->SetupAttachment(AxleRR);

	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelRR"));
	WheelRR->SetupAttachment(AxleRR);

	RL = CreateDefaultSubobject<USceneComponent>(FName("RL"));
	RL->SetupAttachment(Body);

	SceneAxleConstraintRL = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SceneAxleConstraintRL"));
	SceneAxleConstraintRL->SetupAttachment(RL);

	AxleRL = CreateDefaultSubobject<USphereComponent>(FName("AxleRL"));
	AxleRL->SetupAttachment(RL);

	AxleWheelConstraintRL = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraintRL"));
	AxleWheelConstraintRL->SetupAttachment(AxleRL);

	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelRL"));
	WheelRL->SetupAttachment(AxleRL);

	FR = CreateDefaultSubobject<USceneComponent>(FName("FR"));
	FR->SetupAttachment(Body);

	SceneAxleConstraintFR = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SceneAxleConstraintFR"));
	SceneAxleConstraintFR->SetupAttachment(FR);

	AxleFR = CreateDefaultSubobject<USphereComponent>(FName("AxleFR"));
	AxleFR->SetupAttachment(FR);

	AxleWheelConstraintFR = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraintFR"));
	AxleWheelConstraintFR->SetupAttachment(AxleFR);

	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelFR"));
	WheelFR->SetupAttachment(AxleFR);

	FL = CreateDefaultSubobject<USceneComponent>(FName("FL"));
	FL->SetupAttachment(Body);

	SceneAxleConstraintFL = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SceneAxleConstraintFL"));
	SceneAxleConstraintFL->SetupAttachment(FL);

	AxleFL = CreateDefaultSubobject<USphereComponent>(FName("AxleFL"));
	AxleFL->SetupAttachment(FL);

	AxleWheelConstraintFL = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraintFL"));
	AxleWheelConstraintFL->SetupAttachment(AxleFL);

	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelFL"));
	WheelFL->SetupAttachment(AxleFL);


}

// Called when the game starts or when spawned
void Acar::BeginPlay()
{
	Super::BeginPlay();

	WheelRR->SetNotifyRigidBodyCollision(true);
	WheelRR->OnComponentHit.AddDynamic(this, &Acar::OnHit);

	WheelRL->SetNotifyRigidBodyCollision(true);
	WheelRL->OnComponentHit.AddDynamic(this, &Acar::OnHit);

	WheelFR->SetNotifyRigidBodyCollision(true);
	WheelFR->OnComponentHit.AddDynamic(this, &Acar::OnHit);

	WheelFL->SetNotifyRigidBodyCollision(true);
	WheelFL->OnComponentHit.AddDynamic(this, &Acar::OnHit);

	SetupConstraint();

	InitialYaw = WheelFL->GetRelativeRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	UE_LOG(LogTemp, Warning, TEXT("Initial Yaw %f, CurrentYaw %f, TargetYaw,%f"), InitialYaw, CurrentYaw, TargetYaw);
	
}

void Acar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}


void Acar::SetupConstraint()
{
	SceneAxleConstraintRR->SetConstrainedComponents(Body, NAME_None, AxleRR, NAME_None);
	AxleWheelConstraintRR->SetConstrainedComponents(AxleRR, NAME_None, WheelRR, NAME_None);

	SceneAxleConstraintRL->SetConstrainedComponents(Body, NAME_None, AxleRL, NAME_None);
	AxleWheelConstraintRL->SetConstrainedComponents(AxleRL, NAME_None, WheelRL, NAME_None);

	SceneAxleConstraintFR->SetConstrainedComponents(Body, NAME_None, AxleFR, NAME_None);
	AxleWheelConstraintFR->SetConstrainedComponents(AxleFR, NAME_None, WheelFR, NAME_None);

	SceneAxleConstraintFL->SetConstrainedComponents(Body, NAME_None, AxleFL, NAME_None);
	AxleWheelConstraintFL->SetConstrainedComponents(AxleFL, NAME_None, WheelFL, NAME_None);
}

void Acar::AddDrivingForce(float Force)
{
	float ForceMagnitude= Force * MaxDrivingForce;
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}


void Acar::ApplyForce()
{
	WheelRR->AddForce(AxleFL->GetRightVector() * TotalForceMagnitudeThisFrame);
	WheelRL->AddForce(AxleFL->GetRightVector() * TotalForceMagnitudeThisFrame);
	WheelFR->AddForce(AxleFL->GetRightVector() * TotalForceMagnitudeThisFrame);
	WheelFL->AddForce(AxleFL->GetRightVector() * TotalForceMagnitudeThisFrame);
}

// Called every frame
void Acar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}
	
}

// Called to bind functionality to input
void Acar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void Acar::SteerRight(float value)
{
	//float PassYaw = FMath::Clamp<float>(TargetYaw, 0, 30);
	float Angle = value * 30;
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float PassYaw = FMath::FInterpConstantTo(0, Angle, DeltaTime ,15);

	FRotator PassValue(0.f, PassYaw, 0.f);

	UE_LOG(LogTemp, Warning, TEXT("Initial Yaw %f, CurrentYaw %f, TargetYaw,%f"), InitialYaw, CurrentYaw, TargetYaw)

	WheelFL->SetRelativeRotation(PassValue);
	WheelFR->SetRelativeRotation(PassValue);
}
