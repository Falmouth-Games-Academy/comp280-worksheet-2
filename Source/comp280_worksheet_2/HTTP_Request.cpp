// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP_Request.h"

HTTP_Request::HTTP_Request()
{
	http = &FHttpModule::Get();
}

HTTP_Request::HTTP_Request(FString base_url, FString root_path) : HTTP_Request::HTTP_Request()
{

	baseUrl = base_url;
	rootPath = root_path;

}

HTTP_Request::~HTTP_Request() {}

TSharedRef<IHttpRequest> HTTP_Request::GetRequestHeaders(FString p_request)
{

	if (http == NULL) http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> request = http->CreateRequest();
	request->SetURL(baseUrl + "/" + rootPath + p_request);
	// Set headers
	request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	return request;
}

TSharedRef<IHttpRequest> HTTP_Request::GET_Request(FString page_request)
{

	TSharedRef<IHttpRequest> request = GetRequestHeaders(page_request);
	request->SetVerb("GET");

	return request;

}

TSharedRef<IHttpRequest> HTTP_Request::POST_Request(FString page_request, FString jsonStr)
{

	TSharedRef<IHttpRequest> request = GetRequestHeaders(page_request);
	request->SetVerb("POST");
	request->SetContentAsString(jsonStr);

	return request;

}

void HTTP_Request::SendRequest(TSharedRef<IHttpRequest> request)
{
	request->ProcessRequest();
}
