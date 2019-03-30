// Fill out your copyright notice in the Description page of Project Settings.

#include "Noah.h"
#include "StringParser.h"

StringParser::StringParser()
{

}

StringParser::~StringParser()
{
}

void StringParser::TableRangeParser(FString str, FVector& position, int32& range)
{
	//ex) X,Y,Z 위치로서 "X12 Y34 Z56 / I200" 같은 형태의 값이 들어와야한다.

	FString strPos;
	FString strRange;
	bool bRange = false;
	for (int32 i = 0; i < str.Len(); ++i) {
		if (str[i] == '/') {
			bRange = true;
			continue;
		}
		else if (str[i] == ' ') {
			continue;
		}

		if (bRange) {
			strRange += str[i];
		}
		else {
			strPos += str[i];
		}
	}

	position = VectorParser(strPos);
	range = IntParser(strRange);
}

FVector StringParser::VectorParser(FString str)
{
	//ex) X,Y,Z 위치로서 "X12 Y34 Z56" 같은 형태의 값이 들어와야한다.

	FVector position(0, 0, 0);
	FString tempStr;
	for (int32 i = 0; i < str.Len(); ++i) {
		switch (str[i]) {
		case 'X':
			position.X = FCString::Atof(*tempStr);
			tempStr.Empty();
			break;
		case 'Y':
			position.Y = FCString::Atof(*tempStr);
			tempStr.Empty();
			break;
		case 'Z':
			position.Z = FCString::Atof(*tempStr);
			tempStr.Empty();
			break;
		case ' ':
			continue;
		default:
			tempStr += str[i];
			break;
		}
	}
	return position;
}

int32 StringParser::IntParser(FString str)
{
	//ex) "I32"와 같은 값이 들어와야 한다.

	int32 num = 0;
	FString tempStr;
	for (int32 i = 0; i < str.Len(); ++i) {
		switch (str[i]) {
		case 'I':
			num = FCString::Atoi(*tempStr);
			break;
		case ' ':
			continue;
		default:
			tempStr += str[i];
			break;
		}
	}
	return num;
}