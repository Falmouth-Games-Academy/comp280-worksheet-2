// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "jsonContatiners.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FJsonScore
{
	GENERATED_BODY()

	FJsonScore(){}
	FJsonScore( FString uname, FString mode, int gKills, int pCollected, int lv, int t, int scr) {	
		// TODO: these need to match nameing scheme on python server :)
		username = uname;
		level_mode = mode;
		ghost_killed = gKills;
		pills_collected = pCollected;
		level = lv;
		time = t;
		score = scr;
		date_submitted = FDateTime::UtcNow().ToUnixTimestamp();

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString username;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString level_mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int ghost_killed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int pills_collected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	int date_submitted;

};
