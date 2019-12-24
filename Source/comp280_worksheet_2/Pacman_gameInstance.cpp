// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman_gameInstance.h"
#include "Engine.h"
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include "jsonContatiners.h"
#include "Http_Request.h"
#include "Misc/DateTime.h"

void UPacman_gameInstance::SubmitScore(FString levelMode, int ghostKilled, int pillsCollected, int level, int time, int score)
{
	
	FString page = "submit_score";

	FJsonScore scoreContatiner(levelMode, ghostKilled, pillsCollected, level, time, score);
	FString jsonString;

	GetStringFromStruct<FJsonScore>(scoreContatiner, jsonString);
	
	CreateNewHttpRequest();
	TSharedRef<IHttpRequest> request = httpRequest->POST_Request(page, jsonString);
	request->OnProcessRequestComplete().BindUObject(this, &UPacman_gameInstance::ScoreSubmited_responce);
	httpRequest->SendRequest(request);

	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Cyan, TEXT("Submited Score!"));
}

void UPacman_gameInstance::ScoreSubmited_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful) 
{
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Score Submited Responce");

	if (!wasSuccessful && (!request.IsValid() || !response.IsValid()))
	{
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Error: ???");
		return;
	}

	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, response.Get()->GetContentAsString());
}

void UPacman_gameInstance::UpdateFPS()
{

}

void UPacman_gameInstance::UpdateFPS_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful) 
{

}


#pragma region HTTP

void UPacman_gameInstance::CreateNewHttpRequest()
{
	if (httpRequest == NULL)
		httpRequest = new HTTP_Request(httpUrl, httpRootPath);
}

#pragma endregion

#pragma region Json

template <typename StructType>
void UPacman_gameInstance::GetStringFromStruct(StructType data_struct, FString& outputString)
{

	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &data_struct, outputString, 0, 0);

}

template <typename StructType>
void UPacman_gameInstance::GetStructFromString(FString json, StructType& data_struct)
{
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(json, &data_struct, 0, 0);

}

#pragma endregion
