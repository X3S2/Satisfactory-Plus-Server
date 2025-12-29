// Copyright (c) 2025 X3S2. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServerCompatibilitySubsystem.generated.h"

/**
 * Game Instance Subsystem that manages server compatibility for Satisfactory Plus
 * 
 * This subsystem:
 * - Monitors multiplayer state
 * - Manages replication settings
 * - Provides runtime compatibility checks
 * - Logs server-specific events
 */
UCLASS()
class SATISFACTORYPLUSSERVER_API UServerCompatibilitySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * Get the server compatibility version string
	 * @return Version string (e.g., "1.2.3")
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server")
	FString GetCompatibilityVersion() const { return TEXT("1.2.3"); }

	/**
	 * Check if the server compatibility layer is active
	 * @return true if the subsystem is properly initialized
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server")
	bool IsCompatibilityActive() const { return bIsInitialized; }

	/**
	 * Validate that Satisfactory Plus is loaded and compatible
	 * @return true if all compatibility checks pass
	 */
	UFUNCTION(BlueprintCallable, Category = "Satisfactory Plus Server")
	bool ValidateModCompatibility();

protected:
	/** Whether the subsystem has been successfully initialized */
	UPROPERTY()
	bool bIsInitialized;

	/** Check if SatisfactoryPlus plugin is loaded */
	bool IsSatisfactoryPlusLoaded() const;

	/** Validate version compatibility */
	bool ValidateVersionCompatibility() const;
};
