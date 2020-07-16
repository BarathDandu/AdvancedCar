// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Imprezza.generated.h"

class UCameraComponent;
class USpringArmComponent;

UENUM()
enum class EDriveType : uint8
{
	FWD, 
	RWD,
	AWD
};

USTRUCT()
struct FWheelStruct
{
	GENERATED_BODY()

	FWheelStruct()
	:Radius(34.f), Mass(15.f), CorneringStiffness(1.f), LongStiffness(1.f){}

	FWheelStruct(float inRadius, float inMass, float inCornStiff, float inLongStiff)
	:Radius(inRadius), Mass(inMass), CorneringStiffness(inCornStiff), LongStiffness(inLongStiff){}
	
	float Radius;
	float Mass;
	float CorneringStiffness;
	float LongStiffness;
};

USTRUCT()
struct FSuspensionStruct
{
	GENERATED_BODY()

		FSuspensionStruct()
		:Rest_Length(50.f), Travel(10.f), Stiffness(1500.f), Damper(15.f), Force_Min(-2000.f), Force_Max(6000.f) {}

	FSuspensionStruct(float inRestLength, float inTravel, float inStiffness, float inDamper, float inMin, float inMax)
		: Rest_Length(inRestLength), Travel(inTravel), Stiffness(inStiffness), Damper(inDamper), Force_Min(inMin), Force_Max(inMax) {}

	float Rest_Length;
	float Travel;
	float Stiffness;
	float Damper;
	float Force_Min;
	float Force_Max;

};

USTRUCT()
struct FEngineStruct
{
	GENERATED_BODY()

		FEngineStruct()
		:IdleRPM(700.f), MaxRPM(7000.f), Inertia(0.3f), BackTorque(-100.f) {}

	FEngineStruct(float inIdleRPM, float inMaxRPM, float inInertia, float inBackTorque)
		: IdleRPM(inIdleRPM), MaxRPM(inMaxRPM), Inertia(inInertia), BackTorque(inBackTorque) {}


	float IdleRPM;
	float MaxRPM;
	float Inertia;
	float BackTorque;

};

UCLASS()
class MYPROJECT2_API AImprezza : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AImprezza();

	TArray<FHitResult> ArrayHitResult;

	TArray<USceneComponent*> TopLinkComponent;

	TArray<USceneComponent*> WheelComponent;

	TArray<FSuspensionStruct> Suspension;

	TArray<FWheelStruct> Wheel;

	FEngineStruct Engine;

	TArray<float> RayLength;

	TArray<bool> WheelContact;

	TArray<float> Length;

	TArray<float> LastLength;

	TArray<float> Fx;

	TArray<float> Fy;

	TArray<float> Fz;

	TArray<FVector> WheelLinearVelocityLocal;

	TArray<float> GearRatio;

	TArray<float> DriveTorque;

	TArray<float> TorqueRatio;

	TArray<float> WheelInertia;

	TArray<float> WheelAngularVelocity;

	TArray<float> LongSlipVelocity;

	float DeltaTimee;

	float ForwardAxisValue = 0;

	float ThrottleValue = 0;

	float EngineRPM = 0;

	float EngineTorque = 0;

	float EngineAngularVelocity = 0;

	float RPM_to_RAD_PS = 0;

	float RAD_PS_to_RPM = 0;

	int32 Gear = 1;

	int32 GearTarget ;

	float MainGear = 3.82;

	float TotalGearRatio ;

	float Efficiency = 0.8;

	float MaxWheelSpeedOnCurrentGear;

	float LateralSlipNormalized = 0.f;

	float LongSlipNormalized = 0.f;

	FVector2D LongLateralSlipVector ;

	float FxVal = 0;

	float FyVal = 0;

	FVector2D TireForce;

	UPROPERTY(EditDefaultsOnly)
		float GearChangeTime = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float FrontBiasPercent = 0.3f;

	UPROPERTY(EditAnyWhere)
		bool ThrottleFilter = false;

	UPROPERTY(EditAnyWhere)
		float SteeringAngle;

	UPROPERTY(EditAnyWhere)
		float SteeringAngleMax = 45.f;

	UPROPERTY(EditAnyWhere)
		bool DebugForces = false;

	UPROPERTY(EditAnywhere, Category = "Curve Category")
		FRuntimeFloatCurve TorqueCurve;

	FKeyHandle TC1;
	FKeyHandle TC2;
	FKeyHandle TC3;

	UPROPERTY(EditAnywhere, Category = "Curve Category")
		FRuntimeFloatCurve ForceCurve;

	FKeyHandle FC1;
	FKeyHandle FC2;
	FKeyHandle FC3;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Body = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* TopLinkFL = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* TopLinkFR = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* TopLinkRL = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* TopLinkRR = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelFL = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelFR = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelRL = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelRR = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* SteeringWheel = nullptr;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, Category = "Drive Type")
		EDriveType DriveType = EDriveType::AWD;

	void LookX(float Value);
	void LookY(float Value);
	void Steer(float Value);
	void Forward(float Value);
	void Throttle(float Value);
	void SetBodyVisibility();
	void GearUp();
	void GearDown();
	void OnUPTimerExpire();
	void OnDOWNTimerExpire();

};
