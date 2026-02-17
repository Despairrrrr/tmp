#include <string>
#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <cctype>

#include "lexer.hpp"

Lexer::Lexer(const std::string& input) : input(input), offset(0) {}
//
std::vector<Token> Lexer::tokenize() {
	std::vector<Token> tokens;
	for (; input[offset];) {
		if (std::isblank(input[offset]) {//whitespace, \n, \t
			++offset;
		} else if (std::isdigit(input[offset]) || input[offset] == '.') {//number, in function it will be defined either as INT or  DOUBLE
			tokens.push_back(extract_number());
		}
		else if (input[offset] == '\'') {//нужно будет добавить исключение в случае если больше одного символа в ''     -      CHAR_LITERAL
			tokens.push_back(extract_char());//Ќјѕ»—ј“№ Ё“” ‘”Ќ ÷»ё!!!!!!!!!!!!
		}
		else if (std::isalpha(input[offset]) || input[offset] == '_') {//identifier и не только, в этой ветке также провер€етс€ ключевое слово или нет
			tokens.push_back(extract_identifier());
		} else if (metachars.contains(input[offset])) {//operator
			tokens.push_back(extract_operator());
		} else if (input[offset] == '(' || input[offset] == '{') {
			//желательно конечно в функции фиксировать с какой с кобкой мы зашли сюда, если кругла€ есть, то ждем закрывающую круглую
			// может быть как флаг
			string s;
			s.push_back(input[offset]);
			tokens.push_back(Token{TokenType::LPAREN, s});
			++offset;
		} else if (input[offset] == ')' || input[offset] == '}') {
			string s;
			s.push_back(input[offset]);
			tokens.push_back(Token{ TokenType::RPAREN, s});
			++offset;
		} else if (input[offset] == ',') {
			++offset;
			tokens.push_back(Token{TokenType::COMMA, ","});
		}
		else if (input[offset] == ';') {
			++offset;
			tokens.push_back(Token{ TokenType::COMMAND_END, ";" });
		}
		else {
			throw std::runtime_error("Unknown symbol");
		}
	}
	tokens.push_back(Token{TokenType::END, ""});
	return tokens;
}
Token Lexer::extract_char() {
	std::size_t i = 1;//будем начинать не с '
	for (; input[offset + i] != '\''; ++i) {//ищем закрывающую '
		if (i > 3 || (i > 2 && input[offset + 1] != '\\')) {
			throw std::runtime_error("excessive char");
		}
	}
	//'' пустой чар
	if (i == 1) {
		throw std::runtime_error("no char");//в ' ' нет символа
	}
	if (input[offset + 1] == '\\' && i == 2) {//те '\' . Ќаверное нужно еще расписать про двойной \ ;
				throw std::runtime_error("no char");//в ' ' нет символа, должен быть спецсимвол
	}
	Token token{ TokenType::CHAR_LITERAL, std::string(input, offset, i) };
	offset += i;
	return token;
}
Token Lexer::extract_identifier() {
	std::size_t i = 0;
	for (; std::isalnum(input[offset + i]) || input[offset + i] == '_'; ++i);
	if (loop.contains(std::string(input, offset, i))) {
		Token token{ TokenType::LOOP, std::string(input, offset, i) };
		continue;
	}
	else if (condition.contains(std::string(input, offset, i))) {
		Token token{ TokenType::CONDITION, std::string(input, offset, i) };
		continue;
	}
	else if (jump.contains(std::string(input, offset, i))) {
		Token token{ TokenType::JUMP, std::string(input, offset, i) };
		continue;
	}
	else if (keyword.contains(std::string(input, offset, i))) {//TYPE
		Token token{ TokenType::KEY_WORD, std::string(input, offset, i) };
		continue;
	}
	else if (bool_values.contains(std::string(input, offset, i))) {
		Token token{ TokenType::BOOL_LITERAL, std::string(input, offset, i) };
		continue;
	}
	else {
		Token token{ TokenType::IDENTIFIER, std::string(input, offset, i) };
	}
	offset += i;
	return token;
}

Token Lexer::extract_number() {
	bool is_double = 0;//if 0, then it is INT_LITERAL, otherwhise it is DOUBLE_LITERAL
	std::size_t i = 0;
	for(; std::isdigit(input[offset + i]); ++i);
	auto int_len = i;
	if (input[offset + i] == '.') {//2.9
		is_double = 1;
		++i;
		auto j = i;
		for (; std::isdigit(input[offset + i]); ++i);
		if (i - j == 0 && int_len == 0) {
			throw std::runtime_error("Missing int and float part of number");
		}
	}
	if(is_double){//дробное
		Token token{ TokenType::DOUBLE_LITERAL, std::string(input, offset, i) };
	}
	else {
		Token token{ TokenType::INT_LITERAL, std::string(input, offset, i) };
	}
	offset += i;
	return token;
}

Token Lexer::extract_operator() {
	size_t i = 0;
	std::string op;
	for (; metachars.contains(input[offset + i]); ++i) {
		op += input[offset + i];
		if (!operators.contains(op)) {
			if (i == 0) {
				throw std::runtime_error("Invalid operator");
			}
			op.pop_back();
			break;
		}
	}
	Token token{TokenType::OPERATOR, op};
	offset += i;
	return token;
}

const std::string Lexer::metachars = "+-*/^(){};,|&=!<>";//ƒќЋ∆≈Ќ Ћ» Ѕџ“№ «јѕя“јя?
const std::unordered_set<std::string> Lexer::operators = { "+", "-", "*", "/", "^", "&&", "==", "!=", "++", "--", "=", "||", ";", "&", ",", "<<", ">>" };//«јѕя“јя?
const std::unordered_set<std::string> Lexer::keywords = { "int", "double", "bool", "char"};//дл€ типов
const std::unordered_set<std::string> Lexer::bool_values = { "true", "false" };
const std::unordered_set<std::string> Lexer::loop = { "while"};//к черту for, не хочу лишний раз усложн€ть жизнь
const std::unordered_set<std::string> Lexer::jump = { "return", "continue", "break" };
const std::unordered_set<std::string> Lexer::conditions = { "if", "else" };
//вроде нужна функци€ дл€ обработки char значени€, то есть того,что в ' '
//static нужно здесь добавл€ть???