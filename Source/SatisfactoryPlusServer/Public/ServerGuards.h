// Copyright (c) 2025 X3S2. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ServerGuards.generated.h"

/**
 * Blueprint function library providing server-safe utility functions
 * for Satisfactory Plus server compatibility.
 * 
 * These guards prevent client-only code from executing on dedicated servers.
 */
UCLASS()
class SATISFACTORYPLUSSERVER_API UServerGuards : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Check if the current context has authority (Server or Standalone)
	 * Use this before executing gameplay logic that should only run on the server.
	 * 
	 * @param WorldContext - The world context object
	 * @return true if the caller has authority, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server", Meta = (WorldContext = "WorldContext"))
	static bool HasAuthority(const UObject* WorldContext);

	/**
	 * Check if the current instance is a dedicated server
	 * Use this to prevent client-only code (UI, cosmetics, sounds) from running on server.
	 * 
	 * @param WorldContext - The world context object
	 * @return true if running on a dedicated server, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server", Meta = (WorldContext = "WorldContext"))
	static bool IsDedicatedServer(const UObject* WorldContext);

	/**
	 * Check if the current instance is a client (not server, not standalone)
	 * Use this for client-only code like UI updates or cosmetic effects.
	 * 
	 * @param WorldContext - The world context object
	 * @return true if running as a client, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server", Meta = (WorldContext = "WorldContext"))
	static bool IsClient(const UObject* WorldContext);

	/**
	 * Check if the current instance is running in standalone mode (singleplayer)
	 * 
	 * @param WorldContext - The world context object
	 * @return true if running in standalone mode, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "Satisfactory Plus Server", Meta = (WorldContext = "WorldContext"))
	static bool IsStandalone(const UObject* WorldContext);

	/**
	 * Safe log message that includes server/client context
	 * 
	 * @param Message - The message to log
	 * @param WorldContext - The world context object
	 */
	UFUNCTION(BlueprintCallable, Category = "Satisfactory Plus Server", Meta = (WorldContext = "WorldContext"))
	static void ServerSafeLog(const FString& Message, const UObject* WorldContext);
};
