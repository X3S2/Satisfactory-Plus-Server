// Copyright (c) 2025 X3S2. All Rights Reserved.

#include "ServerGuards.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

bool UServerGuards::HasAuthority(const UObject* WorldContext)
{
	if (!WorldContext)
	{
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return false;
	}

	// In Standalone or Server mode, we have authority
	return World->GetNetMode() != NM_Client;
}

bool UServerGuards::IsDedicatedServer(const UObject* WorldContext)
{
	if (!WorldContext)
	{
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return false;
	}

	return World->GetNetMode() == NM_DedicatedServer;
}

bool UServerGuards::IsClient(const UObject* WorldContext)
{
	if (!WorldContext)
	{
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return false;
	}

	return World->GetNetMode() == NM_Client;
}

bool UServerGuards::IsStandalone(const UObject* WorldContext)
{
	if (!WorldContext)
	{
		return false;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!World)
	{
		return false;
	}

	return World->GetNetMode() == NM_Standalone;
}

void UServerGuards::ServerSafeLog(const FString& Message, const UObject* WorldContext)
{
	FString Context;
	
	if (IsDedicatedServer(WorldContext))
	{
		Context = TEXT("[SERVER]");
	}
	else if (IsClient(WorldContext))
	{
		Context = TEXT("[CLIENT]");
	}
	else if (IsStandalone(WorldContext))
	{
		Context = TEXT("[STANDALONE]");
	}
	else
	{
		Context = TEXT("[UNKNOWN]");
	}

	UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] %s %s"), *Context, *Message);
}
