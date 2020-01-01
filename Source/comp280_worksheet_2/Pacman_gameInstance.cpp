// Fill out your copyright notice in the Description page of Project Settings.

#include "Pacman_gameInstance.h"
#include "Engine.h"
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include "Http_Request.h"
#include "Misc/DateTime.h"
#include "Internationalization/Regex.h"

#include <iostream>
#include <regex>

void UPacman_gameInstance::SubmitScore(FString username, FString levelMode, int ghostKilled, int pillsCollected, int level, int time, int score)
{
	
	FString page = "submit_score";

	FJsonScore scoreContatiner(username, levelMode, ghostKilled, pillsCollected, level, time, score);
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

void UPacman_gameInstance::GetLeaderboard(FString gameModeName)
{

	FString page = "leaderboard?game_mode=" + gameModeName;
	leaderboard_gameMode_name = gameModeName;

	CreateNewHttpRequest();
	TSharedRef<IHttpRequest> request = httpRequest->GET_Request(page);
	request->OnProcessRequestComplete().BindUObject(this, &UPacman_gameInstance::GetLeaderboard_responce);
	httpRequest->SendRequest(request);

	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Request sent");

}

void UPacman_gameInstance::GetLeaderboard_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful)
{

	if (!wasSuccessful && (!request.IsValid() || !response.IsValid()))
	{
		if (response.IsValid())
			errorCode = FString::FromInt(response.Get()->GetResponseCode());
		else
			errorCode = "Faild to connect to server...";

		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Error: Reciving data ???");
		recivedLeaderboardData.Broadcast(false);
		return;
	}

	jsonScores.Empty();

	FRegexPattern regexPattern = FRegexPattern("[{]+[ -z | ~]*[^\\[\\]][}]+");
	FRegexMatcher regex = FRegexMatcher(regexPattern, response.Get()->GetContentAsString());

	while (regex.FindNext())
	{
		FJsonScore score;
		GetStructFromString<FJsonScore>(regex.GetCaptureGroup(0), score);
		UE_LOG(LogTemp, Warning, TEXT("in data %s"), *regex.GetCaptureGroup(0));
		jsonScores.Add(score);
	}

	recivedLeaderboardData.Broadcast(true);

}

void UPacman_gameInstance::LoadGameSettings()
{

}

void UPacman_gameInstance::LoadGameSettings_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful) 
{
	if (!wasSuccessful && (!request.IsValid() || !response.IsValid()))
	{
		recivedGameSettingData.Broadcast(false);
		return;
	}

	recivedGameSettingData.Broadcast(true);
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
