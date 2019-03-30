// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class NOAH_API StringParser
{
private:
public:
	StringParser();
	~StringParser();

	static void TableRangeParser(FString str, FVector& position, int32& range);
private:
	static FVector VectorParser(FString str);
	static int32 IntParser(FString str);
};
