#pragma once

#include <string>

enum class TokenType {
	IDENTIFIER, KEY_WORD, INT_LITERAL, DOUBLE_LITERAL, BOOL_LITERAL, CHAR_LITERAL, OPERATOR, LPAREN, RPAREN, COMMA, JUMP, LOOP, CONDITION, COMMAND_END, END
};
struct Token {
	TokenType type;
	std::string value;

	bool operator==(TokenType other_type) const {
		return type == other_type;
	}

	bool operator==(const std::string& other_value) const {
		return value == other_value;
	}
};