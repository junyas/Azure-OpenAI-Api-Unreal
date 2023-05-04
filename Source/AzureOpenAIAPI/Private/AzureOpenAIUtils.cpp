// Copyright Kellan Mythen 2023. All rights Reserved.


#include "AzureOpenAIUtils.h"
#include "AzureOpenAIDefinitions.h"
#include "AzureOpenAIAPI.h"
#include "Modules/ModuleManager.h"

void UAzureOpenAIUtils::setAzureOpenAIApiKey(FString apiKey)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._apiKey = apiKey;
}

FString UAzureOpenAIUtils::getApiKey()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._apiKey;
}

void UAzureOpenAIUtils::	setUseAzureOpenAIApiKeyFromEnvironmentVars(bool bUseEnvVariable)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._useApiKeyFromEnvVariable = bUseEnvVariable;
}

bool UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars()
{

	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._useApiKeyFromEnvVariable;
}

FString UAzureOpenAIUtils::GetEnvironmentVariable(FString key)
{
	FString result;
#if PLATFORM_WINDOWS
	result = FWindowsPlatformMisc::GetEnvironmentVariable(*key);
#endif
#if PLATFORM_MAC
	result = FApplePlatformMisc::GetEnvironmentVariable(*key); 
#endif

#if PLATFORM_LINUX
	result = FLinuxPlatformMisc::GetEnvironmentVariable(*key);
#endif
	return result;
}

