// Copyright 2023-2024 Overtorque Creations LLC. All Rights Reserved. Unauthorized copying of this file, via any medium is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BakonsQolBenchmark.generated.h"

/**
 * 
 */
UCLASS()
class BAKONSQOLTOOLBOX_API UBakonsQolBenchmark : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	void StartBenchmark();

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	void EndBenchmark(FString& ResultString);

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	double GetBenchmarkResult() const;

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	FString GetPrettyBenchmarkResult() const;

private:
	double BenchStartTime;
	double BenchResult;
};
