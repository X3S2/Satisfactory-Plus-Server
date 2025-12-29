// Copyright (c) 2025 X3S2. All Rights Reserved.

#include "ServerCompatibilitySubsystem.h"
#include "Interfaces/IPluginManager.h"

void UServerCompatibilitySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Initializing Server Compatibility Subsystem v1.2.3"));

	// Validate that we can operate properly
	if (ValidateModCompatibility())
	{
		bIsInitialized = true;
		UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Subsystem initialized successfully"));
	}
	else
	{
		bIsInitialized = false;
		UE_LOG(LogTemp, Error, TEXT("[SatisfactoryPlusServer] Subsystem initialization failed - compatibility validation failed"));
	}
}

void UServerCompatibilitySubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Deinitializing Server Compatibility Subsystem"));
	bIsInitialized = false;
	Super::Deinitialize();
}

bool UServerCompatibilitySubsystem::ValidateModCompatibility()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Validating mod compatibility"));

	// Check if SatisfactoryPlus is loaded
	if (!IsSatisfactoryPlusLoaded())
	{
		UE_LOG(LogTemp, Error, TEXT("[SatisfactoryPlusServer] SatisfactoryPlus plugin not found! This mod requires SatisfactoryPlus v1.2.3"));
		return false;
	}

	// Validate version compatibility
	if (!ValidateVersionCompatibility())
	{
		UE_LOG(LogTemp, Warning, TEXT("[SatisfactoryPlusServer] Version compatibility check failed - may cause issues"));
		// Don't fail completely, just warn
	}

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Compatibility validation passed"));
	return true;
}

bool UServerCompatibilitySubsystem::IsSatisfactoryPlusLoaded() const
{
	TSharedPtr<IPlugin> SFPlusPlugin = IPluginManager::Get().FindPlugin(TEXT("SatisfactoryPlus"));
	
	if (!SFPlusPlugin.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[SatisfactoryPlusServer] SatisfactoryPlus plugin not found"));
		return false;
	}

	if (!SFPlusPlugin->IsEnabled())
	{
		UE_LOG(LogTemp, Error, TEXT("[SatisfactoryPlusServer] SatisfactoryPlus plugin is disabled"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] SatisfactoryPlus plugin found and enabled"));
	return true;
}

bool UServerCompatibilitySubsystem::ValidateVersionCompatibility() const
{
	TSharedPtr<IPlugin> SFPlusPlugin = IPluginManager::Get().FindPlugin(TEXT("SatisfactoryPlus"));
	
	if (!SFPlusPlugin.IsValid())
	{
		return false;
	}

	FString PluginVersion = SFPlusPlugin->GetDescriptor().VersionName;
	FString ExpectedVersion = TEXT("1.2.3");

	if (PluginVersion != ExpectedVersion)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SatisfactoryPlusServer] Version mismatch: Expected %s, found %s"), *ExpectedVersion, *PluginVersion);
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Version match confirmed: %s"), *PluginVersion);
	return true;
}
