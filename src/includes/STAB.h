//
// Created by abhilekh on 5/7/24.
//

#ifndef STAB_STAB_H
#define STAB_STAB_H

namespace STAB{
    class Expression;
    class Statement;
    class Return;
    class FunctionDeclaration;
    class Conditional;
    class Integer;
    class Identifier;
    class UnaryOperator;
    class BinaryOp;
    class CompOperator;
    class Block;
    class ExpressionStatement;
    class Assignment;
    class FnCall;
    class VariableDeclaration;
    class Conditional;
    class WhileLoop;

    class Visitor
    {
    public:
        virtual void VisitExpression(Expression *expr) = 0;
        virtual void VisitInteger(Integer *expr) = 0;
        virtual void VisitIdentifier(Identifier *expr) = 0;
        virtual void VisitUnaryOperator(UnaryOperator *expr) = 0;
        virtual void VisitBinaryOp(BinaryOp *expr) = 0;
        virtual void VisitCompOperator(CompOperator *expr) = 0;
        virtual void VisitBlock(Block *expr) = 0;
        virtual void VisitStatement(Statement *stmt) = 0;
        virtual void VisitReturnStatement(Return *retstmt) = 0;
        virtual void VisitFunctionDeclaration(FunctionDeclaration *fndecl) = 0;
        virtual void VisitExpressionStatement(ExpressionStatement *expr) = 0;
        virtual void VisitAssigment(Assignment *expr) = 0;
        virtual void VisitFnCall(FnCall *expr) = 0;
        virtual void VisitVariablenDeclaration(VariableDeclaration *expr) = 0;
        virtual void VisitConditional(Conditional *expr) = 0;
        virtual void VisitWhileLoop(WhileLoop *expr) = 0;
    };
}

#endif //STAB_STAB_H
