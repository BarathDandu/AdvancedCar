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
		WheelFL->SetRelativeRotation(FRotator(0.f, 0.f, 180.f));
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
	SpringArm->bEnableCameraLag = false;
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

	FWheelStruct WSFL;
	FWheelStruct WSFR;
	FWheelStruct WSRL;
	FWheelStruct WSRR;

	Wheel = { WSFL,WSFL,WSFL,WSFL };

	Wheel[0].CorneringStiffness = 0.7f;
	Wheel[1].CorneringStiffness = 0.7f;
	Wheel[2].CorneringStiffness = 0.5f;
	Wheel[3].CorneringStiffness = 0.5f;

	UE_LOG(LogTemp, Warning, TEXT("radius %f, mass = %f"), WSFL.Radius, WSFL.Mass);

	FSuspensionStruct SSFL;
	FSuspensionStruct SSFR;
	FSuspensionStruct SSRL;
	FSuspensionStruct SSRR;

	Suspension = { SSFL,SSFR ,SSRL,SSRR };

	UE_LOG(LogTemp, Warning, TEXT("length %f, Travel = %f, Stiffness =%f, Damper =%f, Min = %f, Max = %f"), SSFL.Rest_Length, SSFL.Travel, SSFL.Stiffness, SSFL.Damper, SSFL.Force_Min, SSFL.Force_Max);

	bool WCFL = false;
	bool WCFR = false;
	bool WCRL = false;
	bool WCRR = false;

	WheelContact = { WCFL,WCFR,WCRL,WCRR };

	UE_LOG(LogTemp, Warning, TEXT("WheelContact Array Length %i"), WheelContact.Num());

	FHitResult OUTHitResultFL;
	FHitResult OUTHitResultFR;
	FHitResult OUTHitResultRL;
	FHitResult OUTHitResultRR;

	ArrayHitResult = { OUTHitResultFL ,OUTHitResultFR, OUTHitResultRL,	OUTHitResultRR };

	UE_LOG(LogTemp, Warning, TEXT("ArrayHitResult Array Length %i"), ArrayHitResult.Num());

	FVector WLVLFL;
	FVector WLVLFR;
	FVector WLVLRL;
	FVector WLVLRR;

	WheelLinearVelocityLocal = { WLVLFL,WLVLFR,WLVLRL,WLVLRR };

	TC1 = FKeyHandle();
	TC2 = FKeyHandle();
	TC3 = FKeyHandle();
	TC4 = FKeyHandle();
	TC5 = FKeyHandle();

	TorqueCurve.EditorCurveData.AddKey(0.f, 0.f, false, TC1);
	TorqueCurve.EditorCurveData.AddKey(2000.f, 250.f, false, TC2);
	TorqueCurve.EditorCurveData.AddKey(4000.f, 500.f, false, TC3);
	TorqueCurve.EditorCurveData.AddKey(6000.f, 350.f, false, TC4);
	TorqueCurve.EditorCurveData.AddKey(8000.f, 200.f, false, TC5);

	TorqueCurve.EditorCurveData.SetKeyTangentMode(TC1, ERichCurveTangentMode::RCTM_Auto);
	TorqueCurve.EditorCurveData.SetKeyInterpMode(TC1, ERichCurveInterpMode::RCIM_Cubic);

	TorqueCurve.EditorCurveData.SetKeyTangentMode(TC2, ERichCurveTangentMode::RCTM_Auto);
	TorqueCurve.EditorCurveData.SetKeyInterpMode(TC2, ERichCurveInterpMode::RCIM_Cubic);

	TorqueCurve.EditorCurveData.SetKeyTangentMode(TC3, ERichCurveTangentMode::RCTM_Auto);
	TorqueCurve.EditorCurveData.SetKeyInterpMode(TC3, ERichCurveInterpMode::RCIM_Cubic);

	TorqueCurve.EditorCurveData.SetKeyTangentMode(TC4, ERichCurveTangentMode::RCTM_Auto);
	TorqueCurve.EditorCurveData.SetKeyInterpMode(TC4, ERichCurveInterpMode::RCIM_Cubic);

	TorqueCurve.EditorCurveData.SetKeyTangentMode(TC5, ERichCurveTangentMode::RCTM_Auto);
	TorqueCurve.EditorCurveData.SetKeyInterpMode(TC5, ERichCurveInterpMode::RCIM_Cubic);

	FC1 = FKeyHandle();
	FC2 = FKeyHandle();
	FC3 = FKeyHandle();

	ForceCurve.EditorCurveData.AddKey(0.f, 0.f, false, FC1);
	ForceCurve.EditorCurveData.AddKey(1.f, 1.f, false, FC2);
	ForceCurve.EditorCurveData.AddKey(1.6f, 0.7f, false, FC3);

	ForceCurve.EditorCurveData.SetKeyTangentMode(FC1, ERichCurveTangentMode::RCTM_Auto);
	ForceCurve.EditorCurveData.SetKeyInterpMode(FC1, ERichCurveInterpMode::RCIM_Cubic);

	ForceCurve.EditorCurveData.SetKeyTangentMode(FC2, ERichCurveTangentMode::RCTM_Auto);
	ForceCurve.EditorCurveData.SetKeyInterpMode(FC2, ERichCurveInterpMode::RCIM_Cubic);

	ForceCurve.EditorCurveData.SetKeyTangentMode(FC3, ERichCurveTangentMode::RCTM_Auto);
	ForceCurve.EditorCurveData.SetKeyInterpMode(FC3, ERichCurveInterpMode::RCIM_Cubic);

	float GearR = -3.615;
	float GearN = 0;
	float Gear1 = 3.583;
	float Gear2 = 2.038;
	float Gear3 = 1.414;
	float Gear4 = 1.108;
	float Gear5 = 0.878;

	GearRatio = { GearR, GearN ,Gear1 ,Gear2 ,Gear3 ,Gear4 ,Gear5 };

	UE_LOG(LogTemp, Warning, TEXT("GearRatio Array Length %i"), GearRatio.Num());

	DriveTorque = { 0.f, 0.f, 0.f, 0.f };

	WheelInertia = { 0.f, 0.f, 0.f, 0.f };

	WheelAngularVelocity = { 0.f, 0.f, 0.f, 0.f };

	LongSlipVelocity = { 0.f, 0.f, 0.f, 0.f };

	UE_LOG(LogTemp, Warning, TEXT("DriveTorque Array Length %i"), DriveTorque.Num());

	LongLateralSlipVector = FVector2D(LongSlipNormalized, LateralSlipNormalized);

	TireForce = FVector2D(FxVal, FyVal);
}

// Called when the game starts or when spawned
void AImprezza::BeginPlay()
{
	Super::BeginPlay();

	RPM_to_RAD_PS = (2 * PI) / 60;
	RAD_PS_to_RPM = 1 / RPM_to_RAD_PS;

	if (DriveType == EDriveType::FWD)
	{
		TorqueRatio = { 1.f , 1.f, 0.f, 0.f };
	}
	else if (DriveType == EDriveType::RWD)
	{
		TorqueRatio = { 0.f ,0.f, 1.f, 1.f };
	}
	else
	{
		TorqueRatio = { FrontBiasPercent , FrontBiasPercent, 1 - FrontBiasPercent,  1 - FrontBiasPercent };
	}

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

		WheelInertia[i] = FMath::Square(Wheel[i].Radius / 100) * Wheel[i].Mass * 0.5f;

		UE_LOG(LogTemp, Warning, TEXT("Torque Bias: %f"), TorqueRatio[i]);

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

	DeltaTimee = DeltaTime;

	for (int32 i = 0; i < 4; i++)
	{
		DriveTorque[i] = FMath::Max(EngineTorque, 0.f) * TotalGearRatio * TorqueRatio[i] * 0.5;

		//UE_LOG(LogTemp, Warning, TEXT("DriveTorque on Wheel %i is %f"), i, DriveTorque[i]);

		//AngularVelocity += AngularAcceleration*DeltaTime
		//AngularAcceleration = Torque/inertia
		//max wheel speed on currentgear;
		
		if (Gear != 1)
		{
			MaxWheelSpeedOnCurrentGear = FMath::Abs(EngineAngularVelocity / TotalGearRatio);
		}
		else
		{
			MaxWheelSpeedOnCurrentGear = 9999.f;
		}

		WheelAngularVelocity[i] = FMath::Sign(MaxWheelSpeedOnCurrentGear) * FMath::Min(
			FMath::Abs(WheelAngularVelocity[i] + ((DriveTorque[i] / WheelInertia[i]) * DeltaTime)),
			MaxWheelSpeedOnCurrentGear);

		//UE_LOG(LogTemp, Warning, TEXT("WheelAngularVelocity %f"), WheelAngularVelocity[i]*RAD_PS_to_RPM);
		
		//max wheel speed on currentgear;
	


		auto TopLink = TopLinkComponent[i];
		if (!TopLink) { UE_LOG(LogTemp, Warning, TEXT("TopLink Error")); return; }
		auto StartLocation = TopLink->GetComponentLocation();

		auto gUpVector = TopLink->GetUpVector();
		auto gForwardVector = TopLink->GetForwardVector();
		auto gRightVector = TopLink->GetRightVector();
		auto gWheelCompLoc = WheelComponent[i]->GetComponentLocation();

		auto UpVector = (gUpVector)* RayLength[i];
		auto EndLocation = StartLocation - UpVector;

		FCollisionQueryParams TraceParams;


		//UE_LOG(LogTemp, Warning, TEXT("%i, %s"),i,*StartLocation.ToString());

		bool bWheelContact = GetWorld()->LineTraceSingleByChannel(ArrayHitResult[i], StartLocation, EndLocation, ECC_Visibility, TraceParams);

		//auto Result = ArrayHitResult[i].Location;
		//UE_LOG(LogTemp, Warning, TEXT("%s") ,*Result.ToText);

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1.f);

		if (bWheelContact)
		{
			DrawDebugBox(GetWorld(), ArrayHitResult[i].ImpactPoint, FVector(10.f, 10.f, 10.f), FColor::Red, false, 1.f);
			WheelContact[i] = bWheelContact;

			auto LengthUpVector = (gUpVector)* Wheel[i].Radius;
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
			WheelContact[i] = false;
			Length[i] = Suspension[i].Rest_Length + Suspension[i].Travel;
			//UE_LOG(LogTemp, Warning, TEXT("%f"), Length[i]);
		}
		//UE_LOG(LogTemp, Warning, TEXT("%i"), WheelContact[i]);
		auto Direction = Body->GetPhysicsLinearVelocityAtPoint(
			(gWheelCompLoc)-(gUpVector*Wheel[i].Radius));

		auto ComponentTransform = (TopLink->GetComponentTransform());
		ComponentTransform = Inverse(ComponentTransform);

		WheelLinearVelocityLocal[i] = (FVector(UKismetMathLibrary::TransformDirection(
			ComponentTransform, (Direction / 100))));

		//UE_LOG(LogTemp, Warning, TEXT("%s"), WheelLinearVelocityLocal[i].ToString());
		
		LongSlipVelocity[i] = (WheelAngularVelocity[i] * (Wheel[i].Radius / 100)) - WheelLinearVelocityLocal[i].X;

		//UE_LOG(LogTemp, Warning, TEXT("LongSlipVelocity %i: %f"),i ,LongSlipVelocity[i]);


		if (bWheelContact)
		{
			/*Fx[i] = Fz[i] * 0.5 * ForwardAxisValue;
			Fy[i] = FMath::Clamp(WheelLinearVelocityLocal[i].Y*-1 * Fz[i], -Fz[i], Fz[i]);

			auto AddingForce = gForwardVector * Fx[i] + gRightVector * Fy[i];
			Body->AddForceAtLocation(AddingForce * 100, ArrayHitResult[i].Location);
			*/
			

			//if(carspeed*slipSpeed>0) =  traction ,else friction
			LongLateralSlipVector.Y = FMath::Clamp((WheelLinearVelocityLocal[i].Y * Wheel[i].CorneringStiffness * -1.f), -1.f, 1.f);
			
			if ((LongSlipVelocity[i] * WheelLinearVelocityLocal[i].X) > 0)
			{
				//Traction = Drivetorque/radius
				LongLateralSlipVector.X = FMath::Clamp( (DriveTorque[i] / (Wheel[i].Radius / 100)) / FMath::Max(Fz[i], 0.000001f),-2.f,2.f );
			}
			else
			{
				LongLateralSlipVector.X = FMath::Clamp(Wheel[i].LongStiffness * LongSlipVelocity[i], -2.f, 2.f);
			}

			TireForce = FMath::Max(Fz[i], 0.f) *
				LongLateralSlipVector.GetSafeNormal() * ForceCurve.EditorCurveData.Eval(LongLateralSlipVector.Size());

			Fx[i] = TireForce.X;
			Fy[i] = TireForce.Y;

			WheelAngularVelocity[i] = WheelAngularVelocity[i] +
				(((FMath::Max(Fz[i], 0.f) * (Wheel[i].Radius / 100) * FMath::Clamp((LongSlipVelocity[i] / -10), -1.f, 1.f))
					/ WheelInertia[i]) * DeltaTime);
		}
		else
		{
			Fx[i] = 0;
			Fy[i] = 0;
		}

		auto AddingForce = gForwardVector * Fx[i] + gRightVector * Fy[i];
		Body->AddForceAtLocation(AddingForce * 100, ArrayHitResult[i].Location);

		UE_LOG(LogTemp, Warning, TEXT("%i Fx: %f Fy: %f wheelangularvelocity %f"), i, Fx[i], Fy[i], WheelAngularVelocity[i]);

		//wheel rotation
		if (i == 0 || i == 2) {
			WheelComponent[i]->AddLocalRotation(
				FRotator((FMath::RadiansToDegrees(WheelAngularVelocity[i]) * DeltaTime), 0.f, 0.f));
		}
		else {
			WheelComponent[i]->AddLocalRotation(
				FRotator((FMath::RadiansToDegrees(-WheelAngularVelocity[i]) * DeltaTime), 0.f, 0.f));
		}


		if (DebugForces)
		{
			auto DebugLineStart = gWheelCompLoc;

			TArray<FVector>  DebugLineEnd = { (gWheelCompLoc + ((Fx[i] / 35)*(gForwardVector))),
				(gWheelCompLoc + ((Fy[i] / 35)*(gRightVector))),(gWheelCompLoc + ((Fz[i] / 35)*(gUpVector))) };

			TArray<FColor> DebugColor = { FColor::Red, FColor::Green, FColor::Blue };

			for (int32 j = 0; j < 3; j++)
			{
				DrawDebugLine(GetWorld(), DebugLineStart, DebugLineEnd[j], DebugColor[j], false, 0.f, 0, 8.f);
			}
		}

	}

	//UE_LOG(LogTemp, Warning, TEXT("Gear: %f, Total Gear Ratio: %f"), GearRatio[Gear], TotalGearRatio);
}

// Called to bind functionality to input
void AImprezza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Look_X", this, &AImprezza::LookX);
	PlayerInputComponent->BindAxis("Look_Y", this, &AImprezza::LookY);
	PlayerInputComponent->BindAxis("SteerR", this, &AImprezza::Steer);
	PlayerInputComponent->BindAxis("Forward", this, &AImprezza::Forward);
	PlayerInputComponent->BindAxis("Throttle", this, &AImprezza::Throttle);

	PlayerInputComponent->BindAction("BodyVisibility", IE_Pressed, this, &AImprezza::SetBodyVisibility);
	PlayerInputComponent->BindAction("P", IE_Pressed, this, &AImprezza::GearUp);
	PlayerInputComponent->BindAction("L", IE_Pressed, this, &AImprezza::GearDown);
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
	ThrottleFilter = false;

	if (ThrottleFilter == false)
	{
		ThrottleValue = Value;
	}
	else
	{
		if (Value != 0)
		{
			ThrottleValue = FMath::Min((DeltaTimee * 1 + ThrottleValue), 1.f);
		}
		else
		{
			ThrottleValue = FMath::Max((ThrottleValue - DeltaTimee * 2), 0.f);
		}
	}


	EngineTorque = FMath::Lerp(Engine.BackTorque, ThrottleValue * TorqueCurve.EditorCurveData.Eval(EngineRPM), ThrottleValue);

	EngineAngularVelocity = FMath::Clamp(
		(EngineAngularVelocity + DeltaTimee * (EngineTorque / Engine.Inertia)),
		(RPM_to_RAD_PS * Engine.IdleRPM),
		(Engine.MaxRPM * RPM_to_RAD_PS));

	EngineRPM = EngineAngularVelocity * RAD_PS_to_RPM;

	//UE_LOG(LogTemp, Warning, TEXT("EngineRPM :%f, EngineTorque: %f "), EngineRPM, EngineTorque);
}

void AImprezza::Forward(float Value)
{
	//ForwardAxisValue = Value;

	//UE_LOG(LogTemp, Warning, TEXT("Throttle %f"), Value);
}


void AImprezza::Steer(float Value)
{
	if (Value != 0)
	{
		SteeringAngle = FMath::Clamp(((Value * 125 * DeltaTimee) + SteeringAngle), -SteeringAngleMax, SteeringAngleMax);
	}
	else
	{
		SteeringAngle = SteeringAngle * (0.7f);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Steer %f"), SteeringAngle);
	TopLinkFL->SetRelativeRotation(FRotator(0.f, SteeringAngle, 0.f));
	TopLinkFR->SetRelativeRotation(FRotator(0.f, SteeringAngle, 0.f));
	SteeringWheel->SetRelativeRotation(FRotator(-20.f, 0.f, (SteeringAngle / SteeringAngleMax)*180.f));


	//UE_LOG(LogTemp, Warning, TEXT("%s"), *ApplyingForce.ToString());

}

void AImprezza::SetBodyVisibility()
{
	Body->SetVisibility(DebugForces);
	if (DebugForces == false)
	{
		DebugForces = true;
	}
	else
	{
		DebugForces = false;
	}
}

void AImprezza::GearUp()
{
	GearTarget = FMath::Min((Gear + 1), (GearRatio.Num() - 1));
	Gear = 1;
	TotalGearRatio = 0;

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AImprezza::OnUPTimerExpire, GearChangeTime, false);
}

void  AImprezza::OnUPTimerExpire()
{
	Gear = GearTarget;
	TotalGearRatio = MainGear * GearRatio[Gear];

}

void AImprezza::GearDown()
{
	GearTarget = FMath::Max((Gear - 1), 0);
	Gear = 1;
	TotalGearRatio = 0;

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AImprezza::OnDOWNTimerExpire, GearChangeTime, false);
}

void  AImprezza::OnDOWNTimerExpire()
{
	Gear = GearTarget;
	TotalGearRatio = MainGear * GearRatio[Gear];
}