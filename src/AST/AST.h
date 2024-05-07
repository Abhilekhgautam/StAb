#ifndef AST_H 
#define AST_H

#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Type.h>
#include <llvm-18/llvm/IR/Value.h>

#include <memory>
#include <string>
#include <vector>

#include "../includes/STAB.h"
#include "../includes/location.hpp"

using namespace llvm;

namespace STAB {
    class codeGenContext;

    using StatementVec = std::vector<Statement*>;
    using ExpressionVec = std::vector<Expression*>;
    using variableVec = std::vector<VariableDeclaration*>;

    enum NodeType {
        Expr,
        Var,
        Fn,
        Integer,
        Identifier
    };

    // Base of every Node:
    class Node {
    public:
        virtual ~Node() = default;

        virtual Value* codegen(codeGenContext& ctx) = 0;

        virtual NodeType getNodeType() = 0;

        virtual std::string getValString(){ return "node";}

        virtual void Accept(Visitor& v) = 0;

        void parseError(location& loc){
            // todo: generate a good parsing error..
        }

    };

    class Expression: public Node {
    public:
        virtual ~Expression() = default;
        std::string getValString() override {return "expression";}
        void Accept(Visitor& v) override {v.VisitExpression(this);}
    };

    class Statement: public Expression {
    public:
        virtual ~Statement() = default;
        NodeType getNodeType() override {return NodeType::Expr;}
        std::string getValString() override {return "statement";}
        void Accept(Visitor& v) override {v.VisitExpression(this);}
    };

    class Integer: public Expression {
    public:
        Integer(int value):value(value){}
        ~Integer() = default;
        NodeType getNodeType() override {return NodeType::Expr;}
        std::string getValString() override {return std::to_string(value);}
        void Accept(Visitor& v) override {v.VisitInteger(this);}

        Value* codegen(codeGenContext& ctx) override;
    private:
        int value;
    };

    class Identifier : public Expression
    {
    public:
        Identifier(const std::string &name)
                : name(name){}

        virtual ~Identifier() = default;

        Value* codegen(codeGenContext& ctx) override;
        NodeType getNodeType() override { return NodeType::Identifier; }
        std::string getValString() override{ return "identifier reference: " + name;}
        void Accept(Visitor &v) override { v.VisitIdentifier(this); }

        std::string getName() const { return name; }

    private:
        std::string name;
    };

    class ExpressionStatement : public Statement
    {
    public:
        explicit ExpressionStatement(Expression *expression)
                : expression(expression) {}
        virtual ~ExpressionStatement() { delete expression; }

        Value* codegen(codeGenContext &ctx) override;
        NodeType getNodeType() override { return NodeType::Expr; }
        Expression *getExpression() { return expression; }
        std::string getValString() override { return "expression statement "; }
        void Accept(Visitor &v) override { v.VisitExpressionStatement(this); }

    private:
        Expression* expression{nullptr};
    };
}
#endif
