// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Online/HTTP/Public/Http.h"

/**
 * 
 */
class COMP280_WORKSHEET_2_API HTTP_Request
{
public:
	HTTP_Request();
	HTTP_Request(FString base_url, FString root_path);
	~HTTP_Request();

private:

	FHttpModule* http;
	FString baseUrl = "127.0.0.1:8000";
	FString rootPath = "";

	/// @Param Request: the page to request.
	TSharedRef<IHttpRequest> GetRequestHeaders(FString p_request);

public:
	TSharedRef<IHttpRequest> GET_Request(FString page_request);		// use to recive data from db
	TSharedRef<IHttpRequest> POST_Request(FString page_request, FString jsonStr);				// use to send data to db

	void SendRequest(TSharedRef<IHttpRequest> request);
};
