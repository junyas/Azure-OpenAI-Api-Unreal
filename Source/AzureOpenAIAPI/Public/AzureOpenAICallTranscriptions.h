// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "AzureOpenAICallTranscriptions.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTranscriptionResponseRecievedPin, const FString, Transcription, const FString&, errorMessage, bool, Success);
/**
 * 
 */
UCLASS()
class AZUREOPENAIAPI_API UAzureOpenAICallTranscriptions : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:
	UAzureOpenAICallTranscriptions();
	~UAzureOpenAICallTranscriptions();

	FString fileName;
	
	UPROPERTY(BlueprintAssignable, Category = "AzureOpenAI")
	FOnTranscriptionResponseRecievedPin Finished;

private:
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AzureOpenAI")
		static UAzureOpenAICallTranscriptions* AzureOpenAICallTranscriptions(FString fileName);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
	
};
