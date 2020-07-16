// Fill out your copyright notice in the Description page of Project Settings.

#include "Imprezza.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"


// Sets default values
AImprezza::AImprezza()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	SetRootComponent(Body);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Car(TEXT("/Game/Imprezza/Impreza_StaticMesh"));

	if (Car.Succeeded())
	{
		Body->SetStaticMesh(Car.Object);
		Body->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		Body->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		Body->SetSimulatePhysics(true);
		Body->SetMassOverrideInKg(NAME_None, 1300.f);
		Body->SetCenterOfMass(FVector(35.f, 0.f, -30.f));
		Body->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	}


	TopLinkFL = CreateDefaultSubobject<USceneComponent>(FName("TopLinkFL"));
	TopLinkFL->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "FL");
	
	TopLinkFR = CreateDefaultSubobject<USceneComponent>(FName("TopLinkFR"));
	TopLinkFR->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "FR");
	
	TopLinkRL = CreateDefaultSubobject<USceneComponent>(FName("TopLinkRL"));
	TopLinkRL->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RL");
	
	TopLinkRR = CreateDefaultSubobject<USceneComponent>(FName("TopLinkRR"));
	TopLinkRR->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "RR");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>WheelMesh(TEXT("/Game/Imprezza/Wheel_33_01"));

	WheelFL = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelFL"));
	WheelFL->AttachToComponent(TopLinkFL, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (WheelMesh.Succeeded())
	{
		WheelFL->SetStaticMesh(WheelMesh.Object);
		WheelFL->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		WheelFL->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		WheelFL->SetRelativeRotation(FRotator(0.f,0.f,180.f));
		WheelFL->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		
	}
	
	WheelFR = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelFR"));
	WheelFR->AttachToComponent(TopLinkFR, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (WheelMesh.Succeeded())
	{
		WheelFR->SetStaticMesh(WheelMesh.Object);
		WheelFR->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		WheelFR->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		WheelFR->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		WheelFR->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	}

	WheelRL = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelRL"));
	WheelRL->AttachToComponent(TopLinkRL, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (WheelMesh.Succeeded())
	{
		WheelRL->SetStaticMesh(WheelMesh.Object);
		WheelRL->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		WheelRL->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		WheelRL->SetRelativeRotation(FRotator(0.f, 0.f, 180.f));
		WheelRL->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	}

	WheelRR = CreateDefaultSubobject<UStaticMeshComponent>(FName("WheelRR"));
	WheelRR->AttachToComponent(TopLinkRR, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (WheelMesh.Succeeded())
	{
		WheelRR->SetStaticMesh(WheelMesh.Object);
		WheelRR->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
		WheelRR->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		WheelRR->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		WheelRR->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SteeringMesh(TEXT("/Game/Imprezza/Impreza_Steering_Wheel"));

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("SteeringWheel"));
	SteeringWheel->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	if (SteeringMesh.Succeeded())
	{
		SteeringWheel->SetStaticMesh(SteeringMesh.Object);
		SteeringWheel->SetRelativeLocation(FVector(40.f, -35.f, 80.f));
		SteeringWheel->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		SteeringWheel->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
		SteeringWheel->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArm->SetWorldRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	// Create the chase camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(0.0, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	
	TopLinkComponent = { TopLinkFL,TopLinkFR,TopLinkRL,TopLinkRR };

	WheelComponent = { WheelFL, WheelFR, WheelRL, WheelRR };

	FWheelStruct WSFL  ;
	FWheelStruct WSFR ;
	FWheelStruct WSRL ;
	FWheelStruct WSRR ;

	Wheel = { WSFL,WSFR,WSRL,WSRR };

	UE_LOG(LogTemp, Warning, TEXT("radius %f, mass = %f"), WSFL.Radius, WSFL.Mass);

	FSuspensionStruct SSFL;
	FSuspensionStruct SSFR;
	FSuspensionStruct SSRL;
	FSuspensionStruct SSRR;

	Suspension = { SSFL,SSFR ,SSRL,SSRR };

	UE_LOG(LogTemp, Warning, TEXT("length %f, Travel = %f, Stiffness =%f, Damper =%f, Min = %f, Max = %f"), SSFL.Rest_Length, SSFL.Travel, SSFL.Stiffness, SSFL.Damper,SSFL.Force_Min,SSFL.Force_Max);
	
	bool WCFL  = false;
	bool WCFR = false;
	bool WCRL = false;
	bool WCRR = false;

	WheelContact = { WCFL,WCFR,WCRL,WCRR };

	UE_LOG(LogTemp, Warning, TEXT("WheelContact Array Length %i"), WheelContact.Num());

	FHitResult OUTHitResultFL;
	FHitResult OUTHitResultFR;
	FHitResult OUTHitResultRL;
	FHitResult OUTHitResultRR;

	ArrayHitResult = { OUTHitResultFL ,OUTHitResultFR, OUTHitResultRL,	OUTHitResultRR};
	
	UE_LOG(LogTemp, Warning, TEXT("ArrayHitResult Array Length %i"), ArrayHitResult.Num());

	FVector WLVLFL = FVector(0.0, 0.0f, 0.0f);
	FVector WLVLFR = FVector(0.0, 0.0f, 0.0f);
	FVector WLVLRL = FVector(0.0, 0.0f, 0.0f);
	FVector WLVLRR = FVector(0.0, 0.0f, 0.0f);

	WheelLinearVelocityLocal = { WLVLFL,WLVLFR,WLVLRL,WLVLRR };

}

// Called when the game starts or when spawned
void AImprezza::BeginPlay()
{
	Super::BeginPlay();

	float CurrentRayLength;

	float CurrentLength;

	for (int32 i = 0; i < 4; i++)
	{

		CurrentRayLength = Wheel[i].Radius + Suspension[i].Rest_Length + Suspension[i].Travel;
		RayLength.Add(CurrentRayLength);


		CurrentRayLength = 0;


		CurrentLength = Suspension[i].Rest_Length;
		Length.Add(CurrentLength);
		LastLength.Add(CurrentLength);

		CurrentLength = 0;

		Fx.Add(CurrentLength);
		Fy.Add(CurrentLength);
		Fz.Add(CurrentLength);
	}
	UE_LOG(LogTemp, Warning, TEXT("RayLength Array Length %i"), RayLength.Num());
	UE_LOG(LogTemp, Warning, TEXT("Length Array Length %i"), Length.Num());
	UE_LOG(LogTemp, Warning, TEXT("Fz Array Length %i"), Fz.Num());
	UE_LOG(LogTemp, Warning, TEXT("LastLength Array Length %i"), LastLength.Num());
}

// Called every frame
void AImprezza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for (int32 i = 0; i < 4; i++)
	{
		
		auto TopLink = TopLinkComponent[i];
		if (!TopLink) { UE_LOG(LogTemp, Warning, TEXT("TopLink Error")); return; }
		auto StartLocation = TopLink->GetComponentLocation();
		auto gUpVector = TopLink->GetUpVector();
		auto UpVector = (gUpVector) * RayLength[i];
		auto EndLocation =  StartLocation - UpVector;

		FCollisionQueryParams TraceParams;
		

		//UE_LOG(LogTemp, Warning, TEXT("%i, %s"),i,*StartLocation.ToString());

		bool bWheelContact = GetWorld()->LineTraceSingleByChannel(ArrayHitResult[i], StartLocation, EndLocation, ECC_Visibility, TraceParams);
		
		//auto Result = ArrayHitResult[i].Location;
		//UE_LOG(LogTemp, Warning, TEXT("%s") ,*Result.ToText);
		
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.f);

		if (bWheelContact)
		{
			DrawDebugBox(GetWorld(), ArrayHitResult[i].ImpactPoint, FVector(10.f,10.f,10.f), FColor::Red, false, 1.f);
			WheelContact[i] = bWheelContact;

			auto LengthUpVector = (gUpVector) * Wheel[i].Radius;
			auto HitLocxUpVec = LengthUpVector + ArrayHitResult[i].Location;
			auto VectorLength = FMath::Clamp(
				StartLocation.Z - HitLocxUpVec.Z, Suspension[i].Rest_Length - Suspension[i].Travel, Suspension[i].Rest_Length + Suspension[i].Travel);
			
			Length[i] = VectorLength;
			//UE_LOG(LogTemp, Warning, TEXT("%f") ,Length[i]);

			float SpringForce = (Suspension[i].Stiffness)*(Suspension[i].Rest_Length - Length[i]);
				
			float DamperForce = (Suspension[i].Damper)*((LastLength[i] - Length[i]) / DeltaTime);

			float  SpringplusDamperForce = FMath::Clamp(SpringForce + DamperForce, Suspension[i].Force_Min, Suspension[i].Force_Max);

			Fz[i] = SpringplusDamperForce;

			LastLength[i] = Length[i];

			auto ForceApplied = (Fz[i] * 100)*(gUpVector);
			Body->AddForceAtLocation(ForceApplied, StartLocation);

			WheelFL->SetRelativeLocation(FVector(0.f, 0.f, -Length[i]));
			WheelFR->SetRelativeLocation(FVector(0.f, 0.f, -Length[i]));
			WheelRL->SetRelativeLocation(FVector(0.f, 0.f, -Length[i]));
			WheelRR->SetRelativeLocation(FVector(0.f, 0.f, -Length[i]));

			//UE_LOG(LogTemp, Warning, TEXT("%i, Force : %f"), i, Fz[i]);
		}
		else
		{
			WheelContact[i]  = false;
			Length[i] = Suspension[i].Rest_Length + Suspension[i].Travel;
			//UE_LOG(LogTemp, Warning, TEXT("%f"), Length[i]);
		}
		//UE_LOG(LogTemp, Warning, TEXT("%i"), WheelContact[i]);
		 auto Direction = Body->GetPhysicsLinearVelocityAtPoint(
			(WheelComponent[i]->GetComponentLocation())-(gUpVector*Wheel[i].Radius));

		auto ComponentTransform = (TopLinkComponent[i]->GetComponentTransform());
		ComponentTransform = Inverse(ComponentTransform);
		
		WheelLinearVelocityLocal[i] = FVector(UKismetMathLibrary::TransformDirection(
			ComponentTransform,(Direction/100))); 
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *WheelLinearVelocityLocal[i].ToString());
		if (WheelContact[i])
		{
			Fx[i] = Fz[i] * 0.5*ForwardAxisValue;
			Fy[i] = FMath::Clamp(WheelLinearVelocityLocal[i].Y*-1 * Fz[i], -Fz[i], Fz[i]);

			auto AddingForce = 	TopLinkComponent[i]->GetForwardVector() * Fx[i] + TopLinkComponent[i]->GetRightVector() * Fy[i];
			Body->AddForceAtLocation(AddingForce * 100, ArrayHitResult[i].Location);
		}
		else
		{
			Fx[i] = 0;
			Fy[i] = 0; 
		}
		

	}
	

}

// Called to bind functionality to input
void AImprezza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Look_X", this, &AImprezza::LookX);
	PlayerInputComponent->BindAxis("Look_Y", this, &AImprezza::LookY);
	PlayerInputComponent->BindAxis("SteerR", this, &AImprezza::Steer);
	PlayerInputComponent->BindAxis("Throttle", this, &AImprezza::Throttle);
	
}

void AImprezza::LookX(float Value)
{
	if (Value != 0.f)
	{
		AddControllerYawInput(Value);
	}
}

void AImprezza::LookY(float Value)
{
	if (Value != 0.f)
	{
		AddControllerPitchInput(-Value);
	}
}


void AImprezza::Throttle(float Value)
{
	ForwardAxisValue = Value;
	
	//UE_LOG(LogTemp, Warning, TEXT("Throttle %f"), Value);
}

void AImprezza::Steer(float Value)
{
	if (Value != 0) 
	{
		SteeringAngle = FMath::Clamp(((Value * 2.f) + SteeringAngle), -SteeringAngleMax, SteeringAngleMax);
	}
	else
	{
		SteeringAngle = SteeringAngle * (0.7f);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Steer %f"), SteeringAngle);
	TopLinkFL->SetRelativeRotation(FRotator(0.f, SteeringAngle, 0.f));
	TopLinkFR->SetRelativeRotation(FRotator(0.f, SteeringAngle, 0.f));
	SteeringWheel->SetRelativeRotation(FRotator(-20.f, 0.f, (SteeringAngle/SteeringAngleMax)*180.f));

	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *ApplyingForce.ToString());

}
