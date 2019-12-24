// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Pacman_gameInstance.generated.h"

class HTTP_Request;

/**
 * 
 */
UCLASS()
class COMP280_WORKSHEET_2_API UPacman_gameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void SubmitScore(FString username, FString levelMode, int ghostKilled, int pillsCollected, int level, int time, int score);
	
	UFUNCTION(BlueprintCallable)
		void UpdateFPS();

private:

	// http
	FString httpUrl = "127.0.0.1:8000";
	FString httpRootPath = "pacman/";
	HTTP_Request* httpRequest;

	void CreateNewHttpRequest();

	void ScoreSubmited_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful);
	void UpdateFPS_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful);

	// json
	template<typename StructType>
	void GetStringFromStruct(StructType data_struct, FString& outputString);

	template <typename StructType>
	void GetStructFromString(FString json, StructType& data_struct);

};
