// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Imprezza.generated.h"

class UCameraComponent;
class USpringArmComponent;

USTRUCT()
struct FWheelStruct
{
	GENERATED_BODY()

	FWheelStruct()
	:Radius(34.f),Mass(15.f){}

	FWheelStruct (float inRadius, float inMass)
	: Radius(inRadius), Mass(inMass){}
	
	
	float Radius ;
	float Mass ;

	
};

USTRUCT()
struct FSuspensionStruct
{
	GENERATED_BODY()

	FSuspensionStruct()
	:Rest_Length(50.f), Travel(10.f),Stiffness(1500.f), Damper(15.f), Force_Min(-2000.f), Force_Max(6000.f) {}

	FSuspensionStruct(float inRestLength, float inTravel,float inStiffness,float inDamper,float inMin, float inMax)
	: Rest_Length(inRestLength), Travel(inTravel), Stiffness(inStiffness), Damper(inDamper), Force_Min(inMin), Force_Max(inMax){}

	float Rest_Length ;
	float Travel;
	float Stiffness ;
	float Damper;
	float Force_Min;
	float Force_Max;

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

	TArray<float> RayLength;

	TArray<bool> WheelContact;

	TArray<float> Length;

	TArray<float> LastLength;

	TArray<float> Fx;

	TArray<float> Fy;

	TArray<float> Fz;

	TArray<FVector> WheelLinearVelocityLocal;

	float ForwardAxisValue = 0;

	UPROPERTY(EditAnyWhere)
	float SteeringAngle;

	UPROPERTY(EditAnyWhere)
	float SteeringAngleMax = 45.f;


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

	void LookX(float Value);
	void LookY(float Value);
	void Steer(float Value);
	void Throttle(float Value);
};
