// Copyright Overtorque Creations LLC. All Rights Reserved.

#pragma once

#include "Components/SplineComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BakonsQolToolboxLib.generated.h"

UENUM(BlueprintType)
enum EQolWorldType
{
	None,
	Editor,
	EditorPreview,
	PIE,
	Game,
	GamePreview
};

UCLASS()
class UBakonsQolToolboxLib : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	// ======= Misc Functions =======

	// Return the version string of a plugin as shown in plugin manager (expensive operation as it loops all plugins)
	UFUNCTION(BlueprintPure, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static FString GetPluginVersion(const FString& PluginModuleName);

	// (Wrapper function for AddonScreenDebugMessage that makes it easier to use, and is blueprint friendly)
	// Prints a message to the screen, overwrites any existing message with the same tag
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static void PrintToScreenWithTag(const FString& InString, FLinearColor TextColor = FLinearColor::White, float Duration = 2.0f, int Tag = 0);

	// ======= World Functions =======

	/** Returns the type of world this logic is running in */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static EQolWorldType GetWorldType(UObject* WorldContextObject);

	/** Returns true if this logic is running in an Editor world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool RunningInEditorWorld(UObject* WorldContextObject, bool bIncludeTools = false);

	/** Returns true if this logic is running in an Editor tool */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool RunningInEditorTool(UObject* WorldContextObject);

	/** Returns true if this logic is running in a PlayInEditor world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
		DisplayName = "Running in PIE World")
	static bool RunningInPIEWorld(UObject* WorldContextObject);

	/** Returns true if this logic is running in a Game world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool RunningInGameWorld(UObject* WorldContextObject, bool IncludePIE = true);

	// ======= Math Functions =======

	// Calculate the bounds of the spline, does not use a cached value, so treat as an expensive operation
	UFUNCTION(BlueprintPure, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static void CalcSplineBounds(const USplineComponent* InSpline, FBoxSphereBounds& OutBounds);

	// Apply a child transform as a relative transform to a parent transform
	UFUNCTION(BlueprintPure, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static void ApplyTransform(const FTransform& Parent, const FTransform& Child, FTransform& Result)
	{
		Result = FTransform(Parent.TransformRotation(Child.GetRotation()), Parent.TransformPosition(Child.GetLocation()));
	}

	// ======= Bug Workarounds ========

	// Workaround for a bug in chaos collision where child primitives are not updated in the physics scene
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox|Transformation", meta = (Keywords = "Bakon Qol Toolbox"))
	static void SetRelativeLocationAndRotation_ChaosWorkaround(UPrimitiveComponent* target, FVector NewLocation, FRotator NewRotation, ETeleportType Teleport = ETeleportType::None);
};
