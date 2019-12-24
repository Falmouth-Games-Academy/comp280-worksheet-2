// Fill out your copyright notice in the Description page of Project Settings.


#include "Pacman_gameInstance.h"
#include "Json.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include "jsonContatiners.h"

void UPacman_gameInstance::SubmitScore(FString levelMode, int ghostKilled, int pillsCollected, int level, int time, int score)
{
	FJsonScore scoreContatiner(levelMode, ghostKilled, pillsCollected, level, time, score);
	FString jsonString;

	GetStringFromStruct<FJsonScore>(scoreContatiner, jsonString);

}

void UPacman_gameInstance::UpdateFPS()
{

}

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
