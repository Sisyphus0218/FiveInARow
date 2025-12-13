#pragma once

#include "Head.h"

class BoardCoord;

class BoardNotation
{
private:
	char colChar;
	int rowNum;

public:
	BoardNotation();
	BoardNotation(char letter, int number);
	~BoardNotation() = default;

	char GetColChar() const;
	int GetRowNum() const;
	bool IsValid() const;
	BoardCoord ToCoord() const;
};

