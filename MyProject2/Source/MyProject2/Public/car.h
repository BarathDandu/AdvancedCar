// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "car.generated.h"

UCLASS()
class MYPROJECT2_API Acar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	void SetupConstraint();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;

	UFUNCTION(BlueprintCallable, Category = Input)
		void AddDrivingForce(float Force);

	UPROPERTY(EditDefaultsOnly)
		float MaxDrivingForce = 40000;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SteerRight(float value);

	float InitialYaw, CurrentYaw;

	UPROPERTY(EditAnywhere)
		float TargetYaw = 30.f;


	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Body= nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* RR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SceneAxleConstraintRR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * AxleRR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraintRR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelRR = nullptr;




	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* RL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SceneAxleConstraintRL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * AxleRL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraintRL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelRL = nullptr;




	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* FR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SceneAxleConstraintFR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * AxleFR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraintFR = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelFR = nullptr;




	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* FL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* SceneAxleConstraintFL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent * AxleFL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraintFL = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* WheelFL = nullptr;




	UPROPERTY(EditAnywhere, Category = "Location")
		FVector RRLocation = FVector(50.f,50.f,0.f);
	UPROPERTY(EditAnywhere, Category = "Location")
		FVector RLLocation;
	UPROPERTY(EditAnywhere, Category = "Location")
		FVector FRLocation; 
	UPROPERTY(EditAnywhere, Category = "Location")
		FVector FLLocation;	


};