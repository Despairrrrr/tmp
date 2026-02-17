#pragma once
#include <string>
#include <vector>
#include <memory>              
#include <utility>
#include <variant>

class Visitor;

struct ASTNode {
	virtual void accept(Visitor&) = 0;
	virtual ~ASTNode() = default;
};

using node = std::shared_ptr<ASTNode>;

/////////////////////////////////////////////

struct Declaration : public ASTNode {
	virtual void accept(Visitor&) = 0;
	virtual ~Declaration() = default;
};
using decl = std::shared_ptr<Declaration>;

struct Statement : public ASTNode {
	virtual void accept(Visitor&) = 0;
	virtual ~Statement() = default;
};
using st = std::shared_ptr<Statement>;


struct Expression : public ASTNode {
	virtual void accept(Visitor&) = 0;
	virtual ~Expression() = default;
};
using expr = std::shared_ptr<Expression>;
////////////////////////////////////////////////

struct Program : public ASTNode {
	std::vector<decl> decl_list;
	Program(const std::vector<decl>& decl_list) : decl_list(decl_list) {}
	void accept(Visitor&);
};

/////////////////////////////////////////////
struct Variable_decl : public Declaration {
	std::string type;
	std::vector<std::pair<std::string, expr>>vars;
	Variable_decl(const std::string& type, const std::vector<std::pair<string, expr>>& vars)
		: type(type), vars(vars){}
	void accept(Visitor&);
};

struct Function_decl : public Declaration {
	std::pair<std::string, std::string> type_and_name;
	std::vector<std::pair<std::string, std::string>>params;
	st block_statement;
	Function_decl(const std::pair<std::string, std::string> type_and_name,
		const std::vector<std::pair<std::string,std::string>>& params,
		const st& block_statement)
		: type(type), params(params), block_statement(block_statement) {}
	void accept(Visitor&);
};

////////////////////////////////////////////////

struct Block_st : public Statement {
	std::vector<st> body;//instructions
	Block_st(const std::vector<st>& body):body(body){}
	void accept(Visitor&);
};

struct Expr_st : public Statement {
	expr Expr;
	Expr_st(const expr& Expr) :Expr(Expr) {}
	void accept(Visitor&);
};

struct Jump_st : public Statement {
	virtual void accept(Visitor&) = 0;
	virtual ~Jump_st() = default;
};
struct Continue_st : public Jump_st {
	void accept(Visitor&);
};
struct Break_st : public Jump_st {
	void accept(Visitor&);
};
struct Return_st : public Jump_st {
	expr Expr;
	Return_st(const expr& Expr)
		: Expr(Expr) {}
	void accept(Visitor&);
}

struct Loop_st : public Statement {
	expr Expr;//can be renamed to condition
	st loop_body;
	Loop_st(const expr& Expr, const st& loop_body)
		: Expr(Expr), loop_body(loop_body) {}
	void accept(Visitor&);
};
struct Condition_st : public Statement {
	expr Expr;//это условие у них на двоих
	st if_bs;//if block statement(if_instructions)
	st else_bs;
	Condition_st(const expr& Expr, const st& if_bs, const st& else_bs)
		: name(name), loop_body(loop_body) {}
	void accept(Visitor&);
};
/*
struct Decl_st : public Statement {
	std::string type;
	std::vector<std::pair<std::string, expr>> vars;
	Decl_st(const string& type, const std::vector<std::pair<std::string, expr>>& vars)
		: type(type), vars(vars) {}
	void accept(Visitor&);
};
*/
struct Decl_st : public Statement {
	decl var_decl;
	Decl_st(const decl& var_decl)
		: var_decl(var_decl) {}
	void accept(Visitor&);
};

////////////////////////////////////////////////////////

struct BinaryNode : public Expression {
	std::string op;
	expr left_branch, right_branch;

	BinaryNode(const std::string& op, const expr& left_branch, const expr& right_branch)
		: op(op), left_branch(left_branch), right_branch(right_branch) {}
	void accept(Visitor&);
};

struct UnaryNode : public Expression {
	virtual void accept(Visitor&) = 0;
	virtual ~UnaryNode() = default;
};
struct PrefixNode : public UnaryNode {
	std::string op;//-- or ++
	expr branch;

	PrefixNode(const std::string& op, const expr& branch)
		: op(op), branch(branch) {}
	void accept(Visitor&);
};

struct PostfixNode : public UnaryNode {
	std::string op;//-- or ++
	expr branch;

	PostfixNode(const std::string& op, const expr& branch)
		: op(op), branch(branch) {}
	void accept(Visitor&);
};
struct FunctionNode : public Expression {
	std::string name;
	std::vector<expr> branches;

	FunctionNode(const std::string& name, const std::vector<node>& branches)
		: name(name), branches(branches) {}
	void accept(Visitor&);
};


struct LiteralNode : public Expression {//ValueNode
	std::bad_variant_access<int, double, char, bool> value;
	LiteralNode(int value): value(value) {}
	LiteralNode(double value): value(value) {}
	LiteralNode(char value) : value(value) {}
	LiteralNode(bool value) : value(value) {}
	void accept(Visitor&);
};

struct IdentifierNode : public Expression {
	std::string name;

	IdentifierNode(const std::string& name)
		: name(name) {}
	void accept(Visitor&);
};

struct ParenthesizedNode : public ASTNode {
	expr Expr;

	ParenthesizedNode(const expr& Expr) : Expr(Expr) {}
	void accept(Visitor&);
};

