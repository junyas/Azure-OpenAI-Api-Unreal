// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AzureOpenAIDefinitions.h"
#include "HttpModule.h"
#include "AzureOpenAICallChat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnResponseRecievedPin, const FChatCompletion, message, const FString&, errorMessage, bool, Success);
/**
 * 
 */
UCLASS()
class AZUREOPENAIAPI_API UAzureOpenAICallChat : public UBlueprintAsyncActionBase
{
public:
	GENERATED_BODY()

public:
	UAzureOpenAICallChat();
	~UAzureOpenAICallChat();

	FChatSettings chatSettings;

	UPROPERTY(BlueprintAssignable, Category = "AzureOpenAI")
	FOnResponseRecievedPin Finished;

private:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AzureOpenAI")
		static UAzureOpenAICallChat* AzureOpenAICallChat(FChatSettings chatSettings);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
	
};