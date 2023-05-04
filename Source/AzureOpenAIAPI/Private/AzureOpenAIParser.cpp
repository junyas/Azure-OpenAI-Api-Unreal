// Copyright Kellan Mythen 2023. All rights Reserved.

#include "AzureOpenAIParser.h"
#include "AzureOpenAIUtils.h"
#include "Dom/JsonObject.h"


// Constructor
AzureOpenAIParser::AzureOpenAIParser(const FCompletionSettings& settings)
	: completionSettings(settings)
{
}

AzureOpenAIParser::AzureOpenAIParser(const FChatSettings& settings)
	: chatSettings(settings)
{
}

//De-constructor
AzureOpenAIParser::~AzureOpenAIParser()
{
}

// parses a single Completion.
FCompletion AzureOpenAIParser::ParseCompletionsResponse(const FJsonObject& json)
{
	FCompletion res = {};
	
	res.text = json.GetStringField(TEXT("text")) + completionSettings.injectRestartText;
	res.index = json.GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	
	return res;
}

// parses the response info
FCompletionInfo AzureOpenAIParser::ParseGPTCompletionInfo(const FJsonObject& json)
{
	FCompletionInfo res = {};

	res.id = json.GetStringField("id");
	res.object = json.GetStringField("object");
	res.created = FDateTime::FromUnixTimestamp(json.GetNumberField("created"));
	res.model = json.GetStringField("model");

	return res;
}

// parses a single Generated messasge.
FChatCompletion AzureOpenAIParser::ParseChatCompletion(const FJsonObject& json)
{
	FChatCompletion res = {};

	FChatLog message;
	message.role = EOAChatRole::ASSISTANT;
	TArray<TSharedPtr<FJsonValue>> choices = json.GetArrayField("choices");
	TSharedPtr<FJsonValue> choice = choices[0];
	TSharedPtr<FJsonObject> messageObject = choice->AsObject()->GetObjectField("message");
	message.content = messageObject->GetStringField("content");
	//res.index = json.GetIntegerField(TEXT("index"));
	json.TryGetStringField(TEXT("finish_reason"), res.finishReason);
	res.message = message;
	
	return res;
}

FString AzureOpenAIParser::ParseTranscriptionCompletion(const FJsonObject& json)
{
	return json.GetStringField("text");
}

// parses a single Generated Image.
FString AzureOpenAIParser::ParseGeneratedImage(FJsonObject& json)
{
	FString res = "";
	res = json.GetStringField(TEXT("url"));

	return res;
}
