#include "Tokenizer.hpp"
#include <iostream>

using namespace std;


int GetTokenTypeCount()
{
	return sizeof(tokenTypeSyntax) / sizeof(std::string);
}

Token* AssignType(const string& token)
{
	int t = 0;
	for (size_t i = 0; i < GetTokenTypeCount(); i++)
	{
		if (token == tokenTypeSyntax[i])
		{
			t = i + 3;
			break;
		}
	}
	return new Token(token, (TokenType)t);
}

bool IsLetter(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool IsDigit(char c)
{
	return (c >= '0' && c <= '9');
}

int CheckForIdentifier(const string& program, int currentIndex)
{
	int resultLength = 0;

	if (IsLetter(program[currentIndex]))
	{
		resultLength++;
		currentIndex++;

		while (IsLetter(program[currentIndex]) || IsDigit(program[currentIndex]))
		{
			resultLength++;
			currentIndex++;
		}
	}
	else
	{
		return 0;
	}

	return resultLength;
}

int CheckForNumericLiteral(const string& program, int currentIndex)
{
	int resultLength = 0;

	while (IsDigit(program[currentIndex]))
	{
		resultLength++;
		currentIndex++;
	}


	return resultLength;
}

int CheckForStringLiteral(const string& program, int currentIndex)
{
	int resultLength = 0;

	if (program[currentIndex] == '\"')
	{
		resultLength++;
		currentIndex++;

		while (program[currentIndex] != '\"')
		{
			resultLength++;
			currentIndex++;
		}
		resultLength++;
	}



	return resultLength;
}

int VerifySyntax(const string& program, int currentIndex, int syntaxTypeIndex)
{
	string currentSyntax = tokenTypeSyntax[syntaxTypeIndex];

	int resultLength = 0;

	for (size_t i = 0; currentSyntax[i] != '\0';)
	{
		if (program[currentIndex] == currentSyntax[i])
		{
			i++;
			currentIndex++;
			resultLength++;
		}
		else
		{
			return 0;
		}
	}

	return resultLength;
}

bool ParseToken(const string& program, int& currentIndex, Token** outResult)
{
	while (program[currentIndex] == ' ' || program[currentIndex] == '\t' || program[currentIndex] == '\n')
		currentIndex++;

	bool isTokenCorrect = false;
	for (int i = 0; i < GetTokenTypeCount(); i++)
	{
		if (int length = VerifySyntax(program, currentIndex, i))
		{
			isTokenCorrect = true;
			*outResult = AssignType(program.substr(currentIndex, length));
			currentIndex += length;
			return true;
		}
	}
	if (int length = CheckForIdentifier(program, currentIndex))
	{
		isTokenCorrect = true;
		*outResult = new Token(program.substr(currentIndex, length), TokenType::IDENTIFIER);
		currentIndex += length;
		return true;
	}
	if (int length = CheckForNumericLiteral(program, currentIndex))
	{
		isTokenCorrect = true;
		*outResult = new Token(program.substr(currentIndex, length), TokenType::NUMERIC_LITERAL);
		currentIndex += length;
		return true;
	}
	if (int length = CheckForStringLiteral(program, currentIndex))
	{
		isTokenCorrect = true;
		*outResult = new Token(program.substr(currentIndex, length), TokenType::NUMERIC_LITERAL);
		currentIndex += length;
		return true;
	}

	if (currentIndex >= program.size())
	{
		*outResult = new Token("\0", TokenType::END_OF_FILE);
		return true;
	}
	if (!isTokenCorrect)
	{
		cout << "Unexpected token at position " << currentIndex << endl;
		return false;
	}

	return true;
}

vector<Token*> Tokenize(const string& program)
{
	vector<Token*> result;

	for (int i = 0; program[i] != '\0';)
	{
		Token* currentToken = nullptr;
		if (ParseToken(program, i, &currentToken))
		{
			result.push_back(currentToken);
		}
		else
		{
			return result;
		}
	}

	return result;
}
