#pragma once

#include <vector>
#include <unordered_map>

#include "token.hpp"
#include "ast.hpp"

#include <memory>//not sure if these two last libraries are needed
#include <stdexcept>

class Parser {
public:
    Parser(const std::vector<Token>&);
    node parse();

private:

    node parse_declarations_vector();
    decl parse_declaration();
    std::vector<std::pair<std::string, std::string>> parse_params();
    std::vector<std::pair<std::string, expr>> parse_vars();

    st parse_block_statement();   
    st parse_statement();

    st parse_loop_st();
    st parse_jump_st();
    st parse_conditional_st();
    st parse_decl_st();
    
    expr parse_binary_expression(int);
    expr parse_base_expression();
    expr parse_literal_expression();
    expr parse_parenthesized_expression();
    std::vector<expr> parse_function_interior_expr();

    // Placeholder functions
    bool match(TokenType) const;
    std::string extract(TokenType);
    static const std::unordered_map<std::string, int> operators;

    std::vector<Token> tokens;
    size_t offset;
};