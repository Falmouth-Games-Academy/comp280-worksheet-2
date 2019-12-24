// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "jsonContatiners.generated.h"

/**
 * 
 */
USTRUCT()
struct FJsonScore
{
	GENERATED_BODY()

	FJsonScore( FString mode, int gKills, int pCollected, int lv, int t, int scr) {
	
		levelMode = mode;
		ghostKilled = gKills;
		pillsCollected = pCollected;
		level = lv;
		time = t;
		score = scr;

	}

	UPROPERTY() FString levelMode;
	UPROPERTY()	int ghostKilled;
	UPROPERTY()	int pillsCollected;
	UPROPERTY()	int level;
	UPROPERTY()	int time;
	UPROPERTY()	int score;

};
