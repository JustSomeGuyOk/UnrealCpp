// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

// event, actor object type with variable, attribute type with its variable, float value for new health, float value pass to delete or whatever
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREALCPP_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	/*
	EditAnywhere - edit in BP editor and per-instance in level.
	VisibleAnywhere - "read-only" in editor and level. Use for components.
	EditDefaultsOnly - hide variable per-insance, edit in BP editor only
	VisibleDefaultsOnly - "Read-only" access for variable, only in BP editor. Uncommon.
	EditInstanceOnly - allow only editing of instance. eg, when placed in level
	--
	BlueprintReadOnly - read only in the Blueprint scripting. does not affect "details" -panel
	BlueprintReadWrite - read-write access in Blueprints
	--
	Category - "" - display only for detail panels and blueprint context menu.
	*/

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Attributes")
	float Health;

public:	

	UFUNCTION(BluePrintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BluePrintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);		
};
