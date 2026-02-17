#pragma once

#include <vector>
#include <unordered_set>

#include "token.hpp"

class Lexer {
public:
    Lexer(const std::string&);
    std::vector<Token> tokenize();
private:
    Token extract_char();
    Token extract_number();
    Token extract_identifier();
    Token extract_operator();

    static const std::string metachars;
    static const std::unordered_set<std::string> operators;
    static const std::unordered_set<std::string> loop;
    static const std::unordered_set<std::string> condition;
    static const std::unordered_set<std::string> jump;
    static const std::unordered_set<std::string> bool_values;
    static const std::unordered_set<std::string> keyword;

    std::string input;
    std::size_t offset;
};