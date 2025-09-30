// Copyright Overtorque Creations LLC. All Rights Reserved.

#include "BakonsQolToolboxLib.h"

#include "Engine/Engine.h"
#include "Interfaces/IPluginManager.h"

UBakonsQolToolboxLib::UBakonsQolToolboxLib(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

FString UBakonsQolToolboxLib::GetPluginVersion(const FString& PluginModuleName)
{
	IPluginManager& PluginManager = IPluginManager::Get();
	TArray<TSharedRef<IPlugin>> Plugins = PluginManager.GetDiscoveredPlugins();
	for( const TSharedRef<IPlugin>& Plugin : Plugins )
	{
		if( Plugin->GetName() == PluginModuleName )
		{
			const FPluginDescriptor& Descriptor = Plugin->GetDescriptor();
			FString Version = Descriptor.VersionName;
			return Version;
		}
	}
	return "Not Found";
}

void UBakonsQolToolboxLib::PrintToScreenWithTag(const FString& InString, FLinearColor TextColor, float Duration, int Tag)
{
	if( !GEngine ) return;
	GEngine->AddOnScreenDebugMessage(Tag, Duration, TextColor.ToFColor(true), InString);
}

EQolWorldType UBakonsQolToolboxLib::GetWorldType(UObject* WorldContextObject)
{
	if( !WorldContextObject ) return None;

	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if( !World ) return None;

	// Map EWorldType to EQolWorldType
	switch( World->WorldType )
	{
		case EWorldType::Editor:
			return Editor;
		case EWorldType::EditorPreview:
			return EditorPreview;
		case EWorldType::PIE:
			return PIE;
		case EWorldType::Game:
			return Game;
		case EWorldType::GamePreview:
			return GamePreview;
		default:
			return None;
	}
}

bool UBakonsQolToolboxLib::RunningInEditorWorld(UObject* WorldContextObject, bool bIncludeTools)
{
	#if WITH_EDITOR
	if( !WorldContextObject ) return false;
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if( !World ) return false;

	return (World->WorldType == EWorldType::Editor) || (bIncludeTools && World->WorldType == EWorldType::EditorPreview);
	#else
	return false;
	#endif
}

bool UBakonsQolToolboxLib::RunningInEditorTool(UObject* WorldContextObject)
{
	#if WITH_EDITOR
	if( !WorldContextObject ) return false;
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if( !World ) return false;

	return World->WorldType == EWorldType::EditorPreview;
	#else
	return false;
	#endif
}

bool UBakonsQolToolboxLib::RunningInPIEWorld(UObject* WorldContextObject)
{
	#if WITH_EDITOR
	if( !WorldContextObject ) return false;
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if( !World ) return false;

	// UE 5.4+ PIE WorldType seems broken, there doesn't seem to be a way to retrieve if we're in PIE mode or not. Even the level prefix is not there.
	// It does return as Editor though, so we will substitute that for now.
	#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 4
	return World->WorldType == EWorldType::Editor;
	#else
		return World->IsPlayInEditor();
	#endif
	// UE 5.4+

	#else
	return false;
	#endif
}

bool UBakonsQolToolboxLib::RunningInGameWorld(UObject* WorldContextObject, bool IncludePIE)
{
	if( !WorldContextObject ) return false;
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
	if( !World ) return false;

	return (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::GamePreview || (IncludePIE && RunningInPIEWorld(WorldContextObject)));
}

void UBakonsQolToolboxLib::CalcSplineBounds(const USplineComponent* InSpline, FBoxSphereBounds& OutBounds)
{
	if( !IsValid(InSpline) ) return;
	OutBounds = InSpline->CalcBounds(InSpline->GetComponentTransform());
}

void UBakonsQolToolboxLib::SetRelativeLocationAndRotation_ChaosWorkaround(UPrimitiveComponent* target, FVector NewLocation, FRotator NewRotation, ETeleportType Teleport)
{
	// Set target transform normally
	target->SetRelativeLocationAndRotation(NewLocation, NewRotation, false, nullptr, Teleport);

	// Bump all children prims to force them to update in the physics scene
	TArray<USceneComponent*> ChildArray;
	target->GetChildrenComponents(true, ChildArray);
	ChildArray.Reserve(ChildArray.Num());
	for( int i = 0; i < ChildArray.Num(); ++i )
	{
		UPrimitiveComponent* iChild = Cast<UPrimitiveComponent>(ChildArray[i]);
		if( IsValid(iChild) )
		{
			FTransform ActualTransform = iChild->GetRelativeTransform();
			FVector BumpLocation = ActualTransform.GetLocation() + FVector::UpVector;
			iChild->SetRelativeLocationAndRotation(BumpLocation, ActualTransform.GetRotation());
			iChild->SetRelativeLocationAndRotation(ActualTransform.GetLocation(), ActualTransform.GetRotation());
		}
	}
}
