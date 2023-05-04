// Copyright Kellan Mythen 2023. All rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AzureOpenAIDefinitions.h"
#include "HttpModule.h"
#include "AzureOpenAICallDALLE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDalleResponseRecievedPin, const TArray<FString>&, generatedImageUrls, const FString&, errorMessage, bool, Success);

/**
 * 
 */
UCLASS()
class AZUREOPENAIAPI_API UAzureOpenAICallDALLE : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UAzureOpenAICallDALLE();
	~UAzureOpenAICallDALLE();

	EOAImageSize imageSize = EOAImageSize::LARGE;
	FString prompt = "";
	int32 numImages = 1;
	FCompletionSettings settings;

	UPROPERTY(BlueprintAssignable, Category = "AzureOpenAI")
		FOnDalleResponseRecievedPin Finished;

private:
	AzureOpenAIValueMapping mapping;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AzureOpenAI")
		static UAzureOpenAICallDALLE* AzureOpenAICallDALLE(EOAImageSize imageSize, FString prompt, int32 numImages);

	virtual void Activate() override;
	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);
};
