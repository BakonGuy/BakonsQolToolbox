// Copyright 2023-2024 Overtorque Creations LLC. All Rights Reserved. Unauthorized copying of this file, via any medium is strictly prohibited


#include "BakonsQolBenchmark.h"

void UBakonsQolBenchmark::Initialize(FSubsystemCollectionBase& Collection) {}
void UBakonsQolBenchmark::Deinitialize() {}

void UBakonsQolBenchmark::StartBenchmark()
{
	BenchStartTime = FPlatformTime::Seconds();
}

void UBakonsQolBenchmark::EndBenchmark(FString& ResultString)
{
	const double BenchEndTime = FPlatformTime::Seconds();
	BenchResult = BenchEndTime - BenchStartTime;;

	ResultString = GetPrettyBenchmarkResult();
}

double UBakonsQolBenchmark::GetBenchmarkResult() const
{
	return BenchResult;
}

FString UBakonsQolBenchmark::GetPrettyBenchmarkResult() const
{
	// Figure the best unit for result to be displayed (us, ms, or s)
	FString Unit = "us";
	double Multiplier = 1000000.0f;

	if( BenchResult >= 0.001 ) // Milliseconds
	{
		Unit = "ms";
		Multiplier = 1000.0f;
	}
	else if( BenchResult >= 1.0f ) // Seconds
	{
		Unit = "s";
		Multiplier = 1.0f;
	}

	return FString::SanitizeFloat(BenchResult * Multiplier) + " " + Unit;
}
