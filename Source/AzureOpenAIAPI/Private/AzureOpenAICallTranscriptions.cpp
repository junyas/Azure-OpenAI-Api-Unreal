// Copyright Kellan Mythen 2023. All rights Reserved.

#include "AzureOpenAICallTranscriptions.h"
#include "AzureOpenAIUtils.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

UAzureOpenAICallTranscriptions::UAzureOpenAICallTranscriptions()
{
}

UAzureOpenAICallTranscriptions::~UAzureOpenAICallTranscriptions()
{
}

UAzureOpenAICallTranscriptions* UAzureOpenAICallTranscriptions::AzureOpenAICallTranscriptions(FString fileName)
{
	UAzureOpenAICallTranscriptions* BPNode = NewObject<UAzureOpenAICallTranscriptions>();
	BPNode->fileName = fileName + ".wav";
	return BPNode;
}

void UAzureOpenAICallTranscriptions::Activate()
{
	FString _apiKey;
	if (UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars())
		_apiKey = UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZURECOGNITIVESERVICES_API_KEY"));
	else
		_apiKey = UAzureOpenAIUtils::getAzureCognitiveServicesApiKey();
	
	// checking parameters are valid
	if (_apiKey.IsEmpty())
	{
		Finished.Broadcast({}, TEXT("Api key is not set"), false);
	}
	
	// get the absolutePath to the wav file
	FString relativePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() + "BouncedWavFiles/" + fileName);
	FString absolutePath = FPaths::ConvertRelativePathToFull(relativePath);
	
	//FString tempHeader = "Bearer ";
	//tempHeader += _apiKey;
	
	// Create the HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	// Set the request method, URL, and headers
	FString url;
	if (UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars())
		url = UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZURECOGNITIVESERVICES_API_ENDPOINT"));
	else
		url = UAzureOpenAIUtils::getAzureCognitiveServicesApiEndpoint();
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb("POST");
	
	// Set the content type, boundary, and form data
	HttpRequest->SetHeader("Ocp-Apim-Subscription-Key", _apiKey);
	HttpRequest->SetHeader("Content-Type", "audio/wav");
	
	TArray<uint8> UpFileRawData;
	FFileHelper::LoadFileToArray(UpFileRawData, *absolutePath);
	HttpRequest->SetContent(UpFileRawData); 

	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAzureOpenAICallTranscriptions::OnResponse);
	
	HttpRequest->ProcessRequest();
}

void UAzureOpenAICallTranscriptions::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	if (!WasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
		if (Finished.IsBound())
		{
			Finished.Broadcast({}, *Response->GetContentAsString(), false);
		}
		return;
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	UE_LOG(LogTemp, Warning, TEXT("URL:%s\nResponse:\n%s"), *Response->GetURL(), *Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		FString TextValue;
		if (JsonObject->TryGetStringField("DisplayText", TextValue))
		{
			UE_LOG(LogTemp, Log, TEXT("Extracted DisplayText: %s"), *TextValue);
		}
		else
		{
			Finished.Broadcast("", "Failed to get 'DisplayText' field from JSON response", false);
		}

		Finished.Broadcast(TextValue, "", true);
	}
	else
	{
		Finished.Broadcast("", "Failed to parse JSON response", false);
	}
}
