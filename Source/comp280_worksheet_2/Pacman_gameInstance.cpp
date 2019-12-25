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
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, "Error: Reciving data ???");
		return;
	}

	// get only the responce responce data
	//TArray<FString> responce = SplitString(response.Get()->GetContentAsString(), "[");
	//responce = SplitString(responce[0], "]");
	//responce = SplitString(re)

	TArray<FJsonScore> jsonScores;

	FRegexPattern regexPattern = FRegexPattern("[{]+[ -z | ~]*[}]+");
	FRegexMatcher regex = FRegexMatcher(regexPattern, response.Get()->GetContentAsString());

	while (regex.FindNext())
	{
		FJsonScore score;
		GetStructFromString<FJsonScore>(regex.GetCaptureGroup(0), score);
		UE_LOG(LogTemp, Warning, TEXT("in data %s"), *regex.GetCaptureGroup(0));
		jsonScores.Add(score);
	}

	recivedLeaderboardData.Broadcast(jsonScores);

}

void UPacman_gameInstance::UpdateFPS()
{

}

void UPacman_gameInstance::UpdateFPS_responce(FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful) 
{

}

TArray<FString> UPacman_gameInstance::SplitString(FString strToSplit, FString chr)
{

	bool searching = true;
	int index = 0;

	TArray<FString> splitStrings;

	FString* LHS = new FString();

	while (searching)
	{
		searching = strToSplit.Split(chr, LHS, &strToSplit);
		splitStrings.Add(*LHS);
	}

	return splitStrings;

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
