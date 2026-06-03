// Fill out your copyright notice in the Description page of Project Settings.


#include "Grimoire/Public/MTCodeHelpers.h"
#include "Framework/Application/SlateApplication.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"

bool UMTCodeHelpers::SaveGameWithChecksum(USaveGame* SaveGameObject, FString SlotName, int32 UserIndex)
{
	if (!SaveGameObject) return false;
	
	TArray<uint8> ObjectBytes;
	if (!UGameplayStatics::SaveGameToMemory(SaveGameObject, ObjectBytes)) return false;
	
	FSaveHeader Header;
	Header.PayloadSize = static_cast<uint32>(ObjectBytes.Num());
	Header.Checksum = FCrc::MemCrc32(ObjectBytes.GetData(), ObjectBytes.Num());
	
	TArray<uint8> FinalData;
	FMemoryWriter Writer(FinalData);
	Writer << Header;

	if (ObjectBytes.Num() > 0)
	{
		Writer.Serialize(ObjectBytes.GetData(), ObjectBytes.Num());	
	}
	
	Writer.Close();
	return UGameplayStatics::SaveDataToSlot(FinalData, SlotName, UserIndex);
}

USaveGame* UMTCodeHelpers::LoadGameWithSanityCheck(FString SlotName, int32 UserIndex)
{
	TArray<uint8> RawData;
	if (!UGameplayStatics::LoadDataFromSlot(RawData, SlotName, UserIndex)) return nullptr;
	
	FMemoryReader Reader(RawData);
	FSaveHeader Header;
	Reader << Header;
	
	UE_LOG(LogTemp, Warning, TEXT("Magic=%u Version=%u Payload=%u"),
	Header.MagicNumber,
	Header.SaveVersion,
	Header.PayloadSize);

	if (RawData.Num() < sizeof(FSaveHeader))
	{
		return nullptr;
	}
	else if (Header.MagicNumber != Magic || Header.SaveVersion != Version)
	{
		USaveGame* LegacySave = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);

		if (LegacySave)
		{
			SaveGameWithChecksum(LegacySave, SlotName, UserIndex);
		}
		return LegacySave;
	}
	
	const int64 Remaining = Reader.TotalSize() - Reader.Tell();
	if (Header.PayloadSize > static_cast<uint32>(Remaining))
	{
		return nullptr;
	}
	
	TArray<uint8> BodyBytes;
	BodyBytes.SetNumUninitialized(Header.PayloadSize);

	if (Header.PayloadSize > 0)
	{
		Reader.Serialize(BodyBytes.GetData(), Header.PayloadSize);
	}
	
	const uint32 ActualCrc = FCrc::MemCrc32(BodyBytes.GetData(), BodyBytes.Num());
	if (ActualCrc != Header.Checksum)
	{
		return nullptr;
	}

	return UGameplayStatics::LoadGameFromMemory(BodyBytes);
}

void UMTCodeHelpers::CopyTempSave()
{
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames/");
	FString TempPath = SaveDir + "TempSave" + TEXT(".sav");
	FString MainPath = SaveDir + "PlayerSave" + TEXT(".sav");
	FString BackupPath = SaveDir + "PlayerSaveArchive" + TEXT(".sav");
	
	IFileManager& FM = IFileManager::Get();

	FM.Copy(*MainPath, *TempPath, true, true);
	FM.Delete(*TempPath);
}

void UMTCodeHelpers::RestoreBackup()
{
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames/");
	FString MainPath = SaveDir + "PlayerSave" + TEXT(".sav");
	FString BackupPath = SaveDir + "PlayerSaveArchive" + TEXT(".sav");

	IFileManager& FM = IFileManager::Get();

	FM.Copy(*MainPath, *BackupPath, true, true);

}

void UMTCodeHelpers::ArchivePlayerSave()
{
	FString SaveDir = FPaths::ProjectSavedDir() / TEXT("SaveGames/");
	FString MainPath = SaveDir + "PlayerSave" + TEXT(".sav");
	FString BackupPath = SaveDir + "PlayerSaveArchive" + TEXT(".sav");
	
	TArray<uint8> RawData;
	if (!UGameplayStatics::LoadDataFromSlot(RawData, TEXT("PlayerSave"), 0))
		return;

	FMemoryReader Reader(RawData);
	FSaveHeader Header;
	Reader << Header;

	if (Header.MagicNumber != Magic || Header.SaveVersion != Version)
		return;

	const int64 Remaining = Reader.TotalSize() - Reader.Tell();
	if (Header.PayloadSize > static_cast<uint32>(Remaining))
		return;

	TArray<uint8> BodyBytes;
	BodyBytes.SetNumUninitialized(Header.PayloadSize);
	if (Header.PayloadSize > 0)
		Reader.Serialize(BodyBytes.GetData(), Header.PayloadSize);

	const uint32 ActualCrc = FCrc::MemCrc32(BodyBytes.GetData(), BodyBytes.Num());
	if (ActualCrc != Header.Checksum)
		return;
	
	IFileManager& FM = IFileManager::Get();

	FM.Copy(*BackupPath, *MainPath, true, true);
}

void UMTCodeHelpers::ClearUserSettingsCache()
{
	if (GConfig)
	{
		GConfig->EmptySection(TEXT("WindowSettings"), GGameUserSettingsIni);
		GConfig->Flush(false, GGameUserSettingsIni);
	}
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