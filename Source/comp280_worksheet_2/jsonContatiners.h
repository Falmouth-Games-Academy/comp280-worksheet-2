// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/DateTime.h"
#include "jsonContatiners.generated.h"

/**
 * 
 */
USTRUCT()
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

	UPROPERTY() FString username;
	UPROPERTY() FString level_mode;
	UPROPERTY()	int ghost_killed;
	UPROPERTY()	int pills_collected;
	UPROPERTY()	int level;
	UPROPERTY()	int time;
	UPROPERTY()	int score;
	UPROPERTY()	int date_submitted;

};
