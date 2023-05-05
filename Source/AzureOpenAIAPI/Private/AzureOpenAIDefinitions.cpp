// Copyright 2021 Kellan Mythen. All Rights Reserved.

#include "AzureOpenAIDefinitions.h"

AzureOpenAIValueMapping::AzureOpenAIValueMapping()
{
	engineTypes.Add(EAOACompletionsEngineType::DAVINCI, TEXT("DAVINCI"));
	engineTypes.Add(EAOACompletionsEngineType::CURIE, TEXT("CURIE"));
	engineTypes.Add(EAOACompletionsEngineType::BABBAGE, TEXT("BABBAGE"));
	engineTypes.Add(EAOACompletionsEngineType::ADA, TEXT("ADA"));
	engineTypes.Add(EAOACompletionsEngineType::TEXT_DAVINCI_002, TEXT("TEXT-DAVINCI-002"));
	engineTypes.Add(EAOACompletionsEngineType::TEXT_CURIE_001, TEXT("TEXT-CURIE-001"));
	engineTypes.Add(EAOACompletionsEngineType::TEXT_BABBAGE_001, TEXT("TEXT-BABBAGE-001"));
	engineTypes.Add(EAOACompletionsEngineType::TEXT_ADA_001, TEXT("TEXT-ADA-001"));
	engineTypes.Add(EAOACompletionsEngineType::TEXT_DAVINCI_002, TEXT("TEXT-DAVINCI-003"));

	imageSizes.Add(EAOAImageSize::SMALL, TEXT("256x256"));
	imageSizes.Add(EAOAImageSize::MEDIUM, TEXT("512x512"));
	imageSizes.Add(EAOAImageSize::LARGE, TEXT("1024x1024"));
	
}

