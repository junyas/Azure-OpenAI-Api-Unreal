// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AzureOpenAIDefinitions.h"
#include "HttpModule.h"
#include "AzureOpenAICallCompletions.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGptResponseRecievedPin, const TArray<FCompletion>&, completions, const FString&, errorMessage, const FCompletionInfo&, completionInfo, bool, Success);

/**
 * 
 */
UCLASS()
class AZUREOPENAIAPI_API UAzureOpenAICallCompletions : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UAzureOpenAICallCompletions();
	~UAzureOpenAICallCompletions();

	EAOACompletionsEngineType engine = EAOACompletionsEngineType::TEXT_DAVINCI_002;
	FString prompt = "";
	FCompletionSettings settings;

	UPROPERTY(BlueprintAssignable, Category = "AzureOpenAI")
		FOnGptResponseRecievedPin Finished;

private:
	AzureOpenAIValueMapping mapping;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AzureOpenAI")
		static UAzureOpenAICallCompletions* AzureOpenAICallCompletions(EAOACompletionsEngineType engine, FString prompt, FCompletionSettings settings);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
};