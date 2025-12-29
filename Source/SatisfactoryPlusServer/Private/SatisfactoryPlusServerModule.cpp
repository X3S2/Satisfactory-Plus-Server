// Copyright (c) 2025 X3S2. All Rights Reserved.

#include "SatisfactoryPlusServerModule.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FSatisfactoryPlusServerModule"

void FSatisfactoryPlusServerModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Module starting (v1.2.3)"));

	// Validate server environment before initialization
	if (!ValidateServerEnvironment())
	{
		UE_LOG(LogTemp, Error, TEXT("[SatisfactoryPlusServer] Server environment validation failed"));
		return;
	}

	// Initialize server-specific patches
	InitializeServerPatches();

	// Setup network replication support
	SetupReplicationSupport();

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Server compatibility layer initialized successfully"));
}

void FSatisfactoryPlusServerModule::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Module shutting down"));
}

void FSatisfactoryPlusServerModule::InitializeServerPatches()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Initializing server patches"));

	// TODO: Implement server-specific patches here
	// - Add HasAuthority checks to gameplay logic
	// - Add IsDedicatedServer guards for client-only code
	// - Patch UI-related functionality to prevent server execution
}

void FSatisfactoryPlusServerModule::SetupReplicationSupport()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Setting up replication support"));

	// TODO: Configure replication for SatisfactoryPlus actors
	// - Ensure all gameplay-relevant actors are replicated
	// - Configure proper replication conditions
	// - Set up RPC (Remote Procedure Call) support where needed
}

bool FSatisfactoryPlusServerModule::ValidateServerEnvironment()
{
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Validating server environment"));

	// Check if running on dedicated server
#if UE_SERVER
	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Running on dedicated server build"));
#endif

	// Check if SatisfactoryPlus is loaded
	// TODO: Add proper dependency check for SatisfactoryPlus plugin

	return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSatisfactoryPlusServerModule, SatisfactoryPlusServer)
