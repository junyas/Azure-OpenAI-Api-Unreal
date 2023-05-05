// Copyright Kellan Mythen 2023. All rights Reserved.

#include "AzureOpenAICallChat.h"
#include "AzureOpenAIUtils.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "AzureOpenAIParser.h"

UAzureOpenAICallChat::UAzureOpenAICallChat()
{
}

UAzureOpenAICallChat::~UAzureOpenAICallChat()
{
}

UAzureOpenAICallChat* UAzureOpenAICallChat::AzureOpenAICallChat(FChatSettings chatSettingsInput)
{
	UAzureOpenAICallChat* BPNode = NewObject<UAzureOpenAICallChat>();
	BPNode->chatSettings = chatSettingsInput;
	return BPNode;
}

void UAzureOpenAICallChat::Activate()
{
	FString _apiKey;
	if (UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars())
		_apiKey = UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZUREOPENAI_API_KEY"));
	else
		_apiKey = UAzureOpenAIUtils::getApiKey();
	
	// checking parameters are valid
	if (_apiKey.IsEmpty())
	{
		Finished.Broadcast({}, TEXT("Api key is not set"), false);
	}	else
	{
	
		auto HttpRequest = FHttpModule::Get().CreateRequest();

		FString apiMethod;
		switch (chatSettings.model)
		{
		case EAOAChatEngineType::GPT_3_5_TURBO:
			apiMethod = "gpt-3.5-turbo";
			break;
		case EAOAChatEngineType::GPT_4:
			apiMethod = "gpt-4";
			break;
		case EAOAChatEngineType::GPT_4_32k:
			apiMethod = "gpt-4-32k";
			break;
		}
		
		//TODO: add aditional params to match the ones listed in the curl response in: https://platform.openai.com/docs/api-reference/making-requests
	
		// convert parameters to strings
		FString tempHeader = "Bearer ";
		tempHeader += _apiKey;

		// set headers
		// original FString url = FString::Printf(TEXT("https://api.openai.com/v1/chat/completions"));
		FString url;
		if (UAzureOpenAIUtils::getUseApiKeyFromEnvironmentVars())
			//url = FString::Printf(TEXT("https://jushimod-openai-sandbox.openai.azure.com/openai/deployments/jushimodChatGPT/chat/completions?api-version=2023-03-15-preview"));
			url = UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZUREOPENAI_API_ENDPOINT"))+TEXT("openai/deployments/")+UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZUREOPENAI_API_DEPLOYMENTNAME"))+TEXT("chat/completions?")+UAzureOpenAIUtils::GetEnvironmentVariable(TEXT("AZUREOPENAI_API_VERSION"));
		else
			url = UAzureOpenAIUtils::getApiEndpoint()+TEXT("openai/deployments/")+UAzureOpenAIUtils::getApiDeploymentName()+TEXT("chat/completions?")+UAzureOpenAIUtils::getApiVersion();

		UE_LOG(LogTemp, Log, TEXT("URL:%s"), url);

		HttpRequest->SetURL(url);
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetHeader(TEXT("Authorization"), tempHeader);

		//build payload
		TSharedPtr<FJsonObject> _payloadObject = MakeShareable(new FJsonObject());
		_payloadObject->SetStringField(TEXT("model"), apiMethod);
		_payloadObject->SetNumberField(TEXT("max_tokens"), chatSettings.maxTokens);

		
		// convert role enum to model string
		if (!(chatSettings.messages.Num() == 0))
		{
			TArray<TSharedPtr<FJsonValue>> Messages;
			FString role;
			for (int i = 0; i < chatSettings.messages.Num(); i++)
			{
				TSharedPtr<FJsonObject> Message = MakeShareable(new FJsonObject());
				switch (chatSettings.messages[i].role)
				{
				case EAOAChatRole::USER:
					role = "user";
					break;
				case EAOAChatRole::ASSISTANT:
					role = "assistant";
					break;
				case EAOAChatRole::SYSTEM:
					role = "system";
					break;
				}
				Message->SetStringField(TEXT("role"), role);
				Message->SetStringField(TEXT("content"), chatSettings.messages[i].content);
				Messages.Add(MakeShareable(new FJsonValueObject(Message)));
			}
			_payloadObject->SetArrayField(TEXT("messages"), Messages);
		}

		// convert payload to string
		FString _payload;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&_payload);
		FJsonSerializer::Serialize(_payloadObject.ToSharedRef(), Writer);

		// commit request
		HttpRequest->SetVerb(TEXT("POST"));
		HttpRequest->SetContentAsString(_payload);

		if (HttpRequest->ProcessRequest())
		{
			HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAzureOpenAICallChat::OnResponse);
		}
		else
		{
			Finished.Broadcast({}, ("Error sending request"), false);
		}
	}
}

void UAzureOpenAICallChat::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	// print response as debug message
	if (!WasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error processing request. \n%s \n%s"), *Response->GetContentAsString(), *Response->GetURL());
		if (Finished.IsBound())
		{
			Finished.Broadcast({}, *Response->GetContentAsString(), false);
		}

		return;
	}

	TSharedPtr<FJsonObject> responseObject;
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(reader, responseObject))
	{
		bool err = responseObject->HasField("error");

		if (err)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
			Finished.Broadcast({}, TEXT("Api error"), false);
			return;
		}

		AzureOpenAIParser parser(chatSettings);
		FChatCompletion _out = parser.ParseChatCompletion(*responseObject);

		Finished.Broadcast(_out, "", true);
	}
}

