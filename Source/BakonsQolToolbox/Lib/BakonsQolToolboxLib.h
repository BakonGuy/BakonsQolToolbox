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

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static void PrintToScreenWithTag(const FString& InString, FLinearColor TextColor, float Duration, int Tag);

	// ======= World Functions =======

	/** Returns the type of world this logic is running in */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static EQolWorldType GetWorldType(UObject* WorldContextObject);

	/** Returns true if this logic is running in an Editor world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool RunningInEditorWorld(UObject* WorldContextObject);

	/** Returns true if this logic is running in a PlayInEditor world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"),
		DisplayName = "Running in PIE World")
	static bool RunningInPIEWorld(UObject* WorldContextObject);

	/** Returns true if this logic is running in a Game world */
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static bool RunningInGameWorld(UObject* WorldContextObject, bool IncludePIE);

	// ======= Math Functions =======

	// Calculate the bounds of the spline, does not use a cached value, so treat as an expensive operation
	UFUNCTION(BlueprintPure, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	static void CalcSplineBounds(const USplineComponent* InSpline, FBoxSphereBounds& OutBounds);

	// ======= Bug Workarounds ========

	// Workaround for a bug in chaos collision where child primitives are not updated in the physics scene
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox|Transformation", meta = (Keywords = "Bakon Qol Toolbox"))
	static void SetRelativeLocationAndRotation_ChaosWorkaround(UPrimitiveComponent* target, FVector NewLocation, FRotator NewRotation, ETeleportType Teleport = ETeleportType::None);
};
