// Copyright 2023-2024 Overtorque Creations LLC. All Rights Reserved. Unauthorized copying of this file, via any medium is strictly prohibited


#include "BakonsQolBenchmark.h"

void UBakonsQolBenchmark::Initialize(FSubsystemCollectionBase& Collection) {}
void UBakonsQolBenchmark::Deinitialize() {}

void UBakonsQolBenchmark::StartBenchmark()
{
	BenchStartTimeSeconds = FPlatformTime::Seconds();
}

void UBakonsQolBenchmark::EndBenchmark()
{
	BenchResultSeconds = FPlatformTime::Seconds() - BenchStartTimeSeconds;
	DecideUnit();
}

double UBakonsQolBenchmark::EndBenchmarkWithResult(FString& OutString, EBQolTimeUnit& OutUnit)
{
	EndBenchmark();
	OutUnit = BenchedUnit;
	OutString = GetPrettyBenchmarkResult();
	return GetBenchmarkResult(OutUnit);
}

double UBakonsQolBenchmark::GetBenchmarkResult(EBQolTimeUnit Unit) const
{
	switch( Unit )
	{
		case EBQolTimeUnit::Seconds: return BenchResultSeconds;
		case EBQolTimeUnit::Milliseconds: return BenchResultSeconds * 1000.0f;
		case EBQolTimeUnit::Microseconds: return BenchResultSeconds * 1000000.0f;
		default: return BenchResultSeconds;
	}
}

FString UBakonsQolBenchmark::GetPrettyBenchmarkResult() const
{
	return FString::SanitizeFloat(BenchResultSeconds * UnitMultiplier) + " " + UnitString;
}

void UBakonsQolBenchmark::DecideUnit()
{
	BenchedUnit = EBQolTimeUnit::Microseconds;
	UnitString = "us";
	UnitMultiplier = 1000000.0f;

	if( BenchResultSeconds >= 0.001 ) // Milliseconds
	{
		BenchedUnit = EBQolTimeUnit::Milliseconds;
		UnitString = "ms";
		UnitMultiplier = 1000.0f;
	}
	else if( BenchResultSeconds >= 1.0f ) // Seconds
	{
		BenchedUnit = EBQolTimeUnit::Seconds;
		UnitString = "s";
		UnitMultiplier = 1.0f;
	}
}
