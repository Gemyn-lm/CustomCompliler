#pragma once
#include <string>
#include <vector>

const std::string tokenTypeSyntax[] =
{
	"if",
	"while",
	"return",
	"true",
	"false",
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	"&&",
	"||",
	"==",
	"!=",
	">=",
	"<=",
	">",
	"<",
	"+=",
	"-=",
	"*=",
	"/=",
	"=",
	"+",
	"-",
	"*",
	"/",
	"!",
	";",
	","
};

enum TokenType
{
	IDENTIFIER,
	NUMERIC_LITERAL,
	STRING_LITERAL,
	IF,
	WHILE,
	RETURN,
	TRUE,
	FALSE,
	PAREN_L,
	PAREN_R,
	BRACKET_L,
	BRACKET_R,
	CURLY_L,
	CURLY_R,
	AND,
	OR,
	IS_EQUAL,
	IS_NOT_EQUAL,
	GREATER_EQUAL,
	LESSER_EQUAL,
	GREATER,
	LESSER,
	PLUS_EQUAL,
	MINUS_EQUAL,
	MULT_EQUAL,
	DIV_EQUAL,
	EQUAL,
	PLUS,
	MINUS,
	MULT,
	DIVIDE,
	NOT,
	SEMICOLON,
	COMMA,
	END_OF_FILE
};

const std::string DebugTokenType[]
{
	"IDENTIFIER",
	"NUMERIC_LITERAL",
	"STRING_LITERAL",
	"IF",
	"WHILE",
	"RETURN",
	"TRUE",
	"FALSE",
	"PAREN_L",
	"PAREN_R",
	"BRACKET_L",
	"BRACKET_R",
	"CURLY_L",
	"CURLY_R",
	"AND",
	"OR",
	"IS_EQUAL",
	"IS_NOT_EQUAL",
	"GREATER_EQUAL",
	"LESSER_EQUAL",
	"GREATER",
	"LESSER",
	"PLUS_EQUAL",
	"MINUS_EQUAL",
	"MULT_EQUAL",
	"DIV_EQUAL",
	"EQUAL",
	"PLUS",
	"MINUS",
	"MULT",
	"DIVIDE",
	"NOT",
	"SEMICOLON",
	"COMMA",
	"END_OF_FILE"
};



struct Token
{
	std::string value;
	TokenType type;

	Token(std::string _value, TokenType _type)
		: value(_value), type(_type) {
	};

};



std::vector<Token*> Tokenize(const std::string& program);