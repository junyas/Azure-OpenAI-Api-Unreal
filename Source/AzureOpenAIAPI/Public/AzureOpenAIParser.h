// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "AzureOpenAIDefinitions.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

/**
 * 
 */
class AZUREOPENAIAPI_API AzureOpenAIParser
{
public:
	AzureOpenAIParser();
	AzureOpenAIParser(const FCompletionSettings&);
	AzureOpenAIParser(const FChatSettings&);
	~AzureOpenAIParser();

	FCompletionSettings completionSettings;
	
	FChatSettings chatSettings;

	FCompletion ParseCompletionsResponse(const FJsonObject&);
	FCompletionInfo ParseGPTCompletionInfo(const FJsonObject&);
	FChatCompletion ParseChatCompletion(const FJsonObject&);
	FString ParseTranscriptionCompletion(const FJsonObject&);
	FString ParseGeneratedImage(FJsonObject&);
};
