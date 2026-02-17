#include "visitor.hpp"
void Program::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Variable_decl::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Function_decl::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Block_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Expr_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Continue_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Break_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Return_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Loop_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Condition_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void Decl_st::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void PrefixNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}
void PostfixNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void BinaryNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void UnaryNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void FunctionNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void LiteralNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void IdentifierNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void ParenthesizedNode::accept(Visitor& visitor) {
    visitor.visit(*this);
}
