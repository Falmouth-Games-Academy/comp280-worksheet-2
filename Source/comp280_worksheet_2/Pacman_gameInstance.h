// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pacman_gameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMP280_WORKSHEET_2_API UPacman_gameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void SubmitScore(FString levelMode, int ghostKilled, int pillsCollected, int level, int time, int score);
	
	UFUNCTION(BlueprintCallable)
		void UpdateFPS();

private:

	// json
	template<typename StructType>
	void GetStringFromStruct(StructType data_struct, FString& outputString);

	template <typename StructType>
	void GetStructFromString(FString json, StructType& data_struct);

};
