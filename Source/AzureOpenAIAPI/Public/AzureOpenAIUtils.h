// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AzureOpenAIDefinitions.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if PLATFORM_WINDOWS
#include "Runtime/Core/Public/Windows/WindowsPlatformMisc.h"
#endif

#if PLATFORM_MAC
#include "Runtime/Core/Public/Apple/ApplePlatformMisc.h"
#endif

#if PLATFORM_LINUX
#include "Runtime/Core/Public/Linux/LinuxPlatformMisc.h"
#endif

#include "AzureOpenAIUtils.generated.h"

/**
 * 
 */
UCLASS()
class AZUREOPENAIAPI_API UAzureOpenAIUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "AzureOpenAI")
	static void setAzureOpenAIApiEndpoint(FString apiEndpoint);
	static FString getAzureOpenAIApiEndpoint();

	UFUNCTION(BlueprintCallable, Category = "AzureOpenAI")
	static void setAzureOpenAIApiDeploymentName(FString apiDeploymentName);
	static FString getAzureOpenAIApiDeploymentName();

	UFUNCTION(BlueprintCallable, Category = "AzureOpenAI")
	static void setAzureOpenAIApiVersion(FString apiVersion);
	static FString getAzureOpenAIApiVersion();

	UFUNCTION(BlueprintCallable, Category = "AzureOpenAI")
	static void setAzureOpenAIApiKey(FString apiKey);
	static FString getAzureOpenAIApiKey();

	UFUNCTION(BlueprintCallable, Category = "AzureOpenAI")
	static void setUseAzureOpenAIApiKeyFromEnvironmentVars(bool bUseEnvVariable);
	static bool getUseApiKeyFromEnvironmentVars();

	static FString GetEnvironmentVariable(FString key);
	
};
