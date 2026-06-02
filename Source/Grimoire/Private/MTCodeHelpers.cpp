// Fill out your copyright notice in the Description page of Project Settings.


#include "Grimoire/Public/MTCodeHelpers.h"
#include "Framework/Application/SlateApplication.h"

bool UMTCodeHelpers::RestoreBackupIfCorrupted(const FString& MainSlot, const FString& BackupSlot)
{
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames/");
	FString MainPath = SaveDir + MainSlot + TEXT(".sav");
	FString BackupPath = SaveDir + BackupSlot + TEXT(".sav");

	IFileManager& FM = IFileManager::Get();
	int64 Size = FM.FileSize(*MainPath);

	if (Size <= 0 || !FM.FileExists(*MainPath))
	{
		if (FM.FileExists(*BackupPath))
		{
			return FM.Copy(*MainPath, *BackupPath, true, true) == COPY_OK;
		}
		
		return false;
	}
	
	return true;
}

FVector2D UMTCodeHelpers::GetWindowPosition()
{
	if (FSlateApplication::IsInitialized())
	{
		TSharedPtr<SWindow> Window = FSlateApplication::Get().GetActiveTopLevelWindow();
		if (Window.IsValid())
		{
			return Window->GetPositionInScreen();
		}
	}
	return FVector2D(100, 100);
}

void UMTCodeHelpers::SetWindowPosition(FVector2D Position)
{
	if (FSlateApplication::IsInitialized())
	{
		TSharedPtr<SWindow> Window = FSlateApplication::Get().GetActiveTopLevelWindow();
		if (Window.IsValid())
		{
			Window->MoveWindowTo(Position);
		}
	}
}

FVector2D UMTCodeHelpers::GetMonitorSize()
{
	FDisplayMetrics Metrics;
	FDisplayMetrics::RebuildDisplayMetrics((Metrics));

	FPlatformRect Rect = Metrics.PrimaryDisplayWorkAreaRect;
	return FVector2D(
		Rect.Right - Rect.Left,
		Rect.Bottom - Rect.Top
	);
}

TArray<FVector2D> UMTCodeHelpers::NormalizeAndSortVector2DArray(TArray<FVector2D> Points)
{
	for(FVector2D& Link : Points)
	{
		if (Link.X > Link.Y)
		{
			Swap(Link.X, Link.Y);
		}
	}
	
	Points.Sort([](const FVector2D& A, const FVector2D& B)
	{
		return (A.X < B.X) || (A.X == B.X && A.Y < B.Y);
	});

	return Points;
}

TArray<float> UMTCodeHelpers::SortFloatArrayAscending(const TArray<float> InputArray)
{
	TArray<float> SortedArray = InputArray;
	SortedArray.Sort();
	return SortedArray;
}