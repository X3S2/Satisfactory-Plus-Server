// Copyright (c) 2025 X3S2. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Satisfactory Plus Server Compatibility Module
 * 
 * Provides dedicated server support and multiplayer compatibility for Satisfactory Plus v1.2.3
 * without modifying original gameplay, balancing, or content.
 * 
 * Features:
 * - Server authority checks (HasAuthority)
 * - Dedicated server guards (IsDedicatedServer)
 * - Network replication support
 * - Client-only code isolation
 * - Cross-platform server compatibility (Windows/Linux)
 */
class FSatisfactoryPlusServerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Initialize server-specific hooks and patches */
	void InitializeServerPatches();
	
	/** Setup replication support for multiplayer */
	void SetupReplicationSupport();
	
	/** Validate server environment and dependencies */
	bool ValidateServerEnvironment();
};
