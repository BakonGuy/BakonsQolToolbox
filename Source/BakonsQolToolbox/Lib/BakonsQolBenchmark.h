// Copyright 2023-2024 Overtorque Creations LLC. All Rights Reserved. Unauthorized copying of this file, via any medium is strictly prohibited

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BakonsQolBenchmark.generated.h"

UENUM(BlueprintType)
enum class EBQolTimeUnit : uint8 { Seconds, Milliseconds, Microseconds };

UCLASS()
class BAKONSQOLTOOLBOX_API UBakonsQolBenchmark : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	void StartBenchmark();

	// Just ends the benchmark
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	void EndBenchmark();

	// Ends the benchmark and returns the result in the best unit
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	double EndBenchmarkWithResult(FString& OutString, EBQolTimeUnit& OutUnit);

	// Return the benchmark result in your chosen unit
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	double GetBenchmarkResult(EBQolTimeUnit Unit = EBQolTimeUnit::Seconds) const;

	// Return the benchmark result in a pretty string format
	UFUNCTION(BlueprintCallable, Category = "Bakons Qol Toolbox", meta = (Keywords = "Bakon Qol Toolbox"))
	FString GetPrettyBenchmarkResult() const;

private:
	// Pretty Results
	void DecideUnit();
	EBQolTimeUnit BenchedUnit = EBQolTimeUnit::Seconds;
	double UnitMultiplier = 1.0f;
	FString UnitString = "s";

	// Actual Results
	double BenchStartTimeSeconds = 0.0f;
	double BenchResultSeconds = 0.0f;
};
