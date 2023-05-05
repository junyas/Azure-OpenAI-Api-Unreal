// Copyright Kellan Mythen 2023. All rights Reserved.


#include "AzureOpenAIUtils.h"
#include "AzureOpenAIDefinitions.h"
#include "AzureOpenAIAPI.h"
#include "Modules/ModuleManager.h"

//
// 
//
void UAzureOpenAIUtils::setUseAzureOpenAIApiKeyFromEnvironmentVars(bool bUseEnvVariable)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._useApiKeyFromEnvVariable = bUseEnvVariable;
}

bool UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars()
{

	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._useApiKeyFromEnvVariable;
}

//
// Azure OpenAI
//
void UAzureOpenAIUtils::setAzureOpenAIApiEndpoint(FString apiEndpoint)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureOpenAIAPIEndpoint = apiEndpoint;
}

FString UAzureOpenAIUtils::getAzureOpenAIApiEndpoint()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureOpenAIAPIEndpoint;
}

void UAzureOpenAIUtils::setAzureOpenAIApiDeploymentName(FString apiDeploymentName)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureOpenAIAPIDeploymentName = apiDeploymentName;
}

FString UAzureOpenAIUtils::getAzureOpenAIApiDeploymentName()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureOpenAIAPIDeploymentName;
}

void UAzureOpenAIUtils::setAzureOpenAIApiVersion(FString apiVersion)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureOpenAIAPIVersion = apiVersion;
}

FString UAzureOpenAIUtils::getAzureOpenAIApiVersion()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureOpenAIAPIVersion;
}

void UAzureOpenAIUtils::setAzureOpenAIApiKey(FString apiKey)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureOpenAIAPIKey = apiKey;
}

FString UAzureOpenAIUtils::getAzureOpenAIApiKey()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureOpenAIAPIKey;
}

//
// Azure Cognitive Services
//
void UAzureOpenAIUtils::setAzureCognitiveServicesApiEndpoint(FString apiEndpoint)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureCognitiveServicesAPIEndpoint = apiEndpoint;
}

FString UAzureOpenAIUtils::getAzureCognitiveServicesApiEndpoint()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureCognitiveServicesAPIEndpoint;
}

void UAzureOpenAIUtils::setAzureCognitiveServicesApiKey(FString apiKey)
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	mod._AzureCognitiveServicesAPIKey = apiKey;
}

FString UAzureOpenAIUtils::getAzureCognitiveServicesApiKey()
{
	FAzureOpenAIAPIModule& mod = FModuleManager::Get().LoadModuleChecked<FAzureOpenAIAPIModule>("AzureOpenAIAPI");
	return mod._AzureCognitiveServicesAPIKey;
}

//
// common util that access environment variables of each platform
//
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

