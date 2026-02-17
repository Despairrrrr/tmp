#include <string>
#include <vector>
#include <stdexcept>

#include "parser.hpp"

#define MIN_PRECEDENCE 0

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), offset(0) {}

node Parser::parse() {
	return parse_declarations_vector();//пускай пока так называется
}

node Parser::parse_declarations_vector() {
	std::vector<decl>decl_vector;
	while (!match(TokenType::END)) {
		decl_vector.push_back(parse_declaration());
	}
	return std::make_shared<Program>(decl_list);
}

decl Parser::parse_declaration() {
	if (match(TokenType::KEY_WORD)) {//тип
		if (std::string type = extract(TokenType::KEY_WORD); match(TokenType::IDENTIFIER)) {
			if (std::string identifier = extract(TokenType::IDENTIFIER); match(TokenType::LRAPEN)) {
				return make_shared<Function_decl>(make_pair(type, identifier), parse_params(), parse_block_statement());
			}
			else {
				offset--;//returning identifier token back
				return make_shared<Variable_decl>(type, parse_vars());//can be using = and without using it
			}
		}
		else {
			throw std::runtime_error("No identifier in declaration");
		}
	}
	else {
		throw std::runtime_error("No type in declaration");
	}
}

std::vector<std::pair<std::string, std::string>> Parser::parse_params() {
	std::vector<std::pair<std::string, std::string>> params;
	if (tokens[offset].value == "(") {
		extract(TokenType::LPAREN);
		while (!(token[offset] == ")")) {
			if (match(TokenType::KEY_WORD)) {
				if (std::string type = extract(TokenType::KEY_WORD); match(TokenType::IDENTIFIER)) {
					params.push_back(make_pair(type, extract(TokenType::IDENTIFIER));
				}
				else{
					throw std::runtime_error("No identifier after the type in parameter");
				}
			}
			else {
				throw std::runtime_error("No type after LPAREN ( token");
			}

			if (!match(TokenType::COMMA) && !(token[offset].value == ")")) {
				throw std::runtime_error("After each parameter should be either COMMA token or RPAREN token");
			}
			if (match(TokenType::COMMA)) {
				extract(TokenType::COMMA);
			}
		}
	}
	else {
		throw std::runtime_error("No LPAREN ( in function's parameter declaration");
	}
	extract(TokenType::RPAREN);
	return params;
}

st parse_block_statement() {
	std::vector<st> statements;
	if (tokens[offset].value == "{") {
		extract(TokenType::LPAREN);
		while (!(token[offset] == "}")) {
			statements.push_back(parse_statement());
			if (match(TokenType::END)) {
				throw std::runtime_error("Block Statement is not complete");
			}
		}
	}
	else {
		throw std::runtime_error("block statement should start with { and not with " + tokens[offset].value);
	}
	return std::make_shared<Block_st>(statements);
}

st parse_statement() {
	//jump, conditional, loop, decl_st, expr
	if (match(TokenType::JUMP)) {
		return parse_loop_st();
	}
	else if (match(TokenType::CONDITION)) {
		return parse_jump_st();
	}
	else if (match(TokenType::LOOP)) {
		return parse_conditional_st();
	}  
	else if (match(TokenType::KEY_WORD)) {
		return parse_decl_st();
	}
	else{
		return std::make_shared<Expr_st>(parse_binary_expr(MIN_PRECEDENCE));
	}
}
std::vector<std::pair<std::string, expr>> parse_vars() {
	std::vector<std::pair<std::string, expr>> all_vars_in_line;
	expr var_value;//using it as local(bus)
	std::string var_name;//dont need to initialize it in cycle, for optimization
	bool new_comma_added = false;//it will show 
	while (!match(TokenType::END)) {
		if (match(TokenType::IDENTIFIER)) {
			if (var_name = extract(TokenType::IDENTIFIER); tokens[offset] == "=") {
				extract(TokenType::OPERATOR);
				var_value = std::make_shared<Expr_st>(parse_binary_expr(MIN_PRECEDENCE));
			}
			all_vars_in_line.push_back(make_pair(var_name, var_value));
			new_comma_added = false;
			if (match(TokenType::COMMA)) {
				extract(TokenType::COMMA);
				comma_added = true;//если vard_added = false, то тогда все ок и для правильной оконцовки еще нужна ;
				continue;
			}
			else if (match(TokenType::COMMAND_END) && !comma_added) {

			}
		}
		else {
			throw std::runtime_error("Token "+ tokens[offset].value + " is not a variable name");
		}
		if()
		//if(match(TokenType::END))
	}
	if (match(TokenType::COMMAND_END)) {
		extract(TokenType::COMMAND_END);
		return all_vars_in_line;
	}
	throw std::runtime_error("No COMMAND_END Token. It's probable END Token: " + tokens[offset].value);
	//нужно отметить
	//например для int x = 4; должен быть вектор из одной пары. Также могут быть такие примеры int a; Когда значений нет, Я так понимаю в таком случае для пары с ключом a указатель должен быть nullptr
}
st parse_loop_st() {

}
st parse_jump_st() {

}
st parse_conditional_st() {

}
st parse_decl_st() {

}
st parse_expr_st() {

}
bool Parser::match(TokenType expected_type) const {//проверяет совпадает ли тип текущего токена с передаваемым ожидаемым типом токена
	return tokens[offset] == expected_type;//здесь используется переопределенный оператор равно из файла token.hpp 
}

//эта функция вовзращает значение текущего токена и увеличивает offse
std::string Parser::extract(TokenType expected_type) {//извлекает строку с ожидаемым типом токена
	if (!match(expected_type)) {//если тип текущего токена не совпадает с expected_type, то выбрасывается исключение, ибо мы уже проверяли и тип должен совпасть
		throw std::runtime_error("Unexpected token " + tokens[offset].value);
	}
	return tokens[offset++].value;//возвращаем значение токена(строку) и смещаемся на следующий токен
}