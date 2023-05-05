// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAzureOpenAIAPIModule : public IModuleInterface
{
	friend class UAzureOpenAIUtils;
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FString _apiEndpoint = "";
	FString _apiVersion = "";
	FString _apiKey = "";
	/** use API Key true:from Environment Variable or false:defined in Blueprint */
	bool _useApiKeyFromEnvVariable = false;
};
