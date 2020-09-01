#include "Parser.h"

namespace parser
{
    Parser::Parser(std::vector<std::string> filesLines)
    {
        lines = filesLines;
    }

    void Parser::parseLines()
    {
        for (auto &&line : lines)
        {
            parseLine(line);
        }
    }

    void Parser::parseLine(std::string line)
    {
        std::vector<lexer::Token> words = lexer::Lexer::lex(line);

        tree::Tree *tree = new tree::Tree();
        tree->curr = shuntingYardPostFix(words);

        tree->printPreorder(tree->curr);
        std::cout << std::endl;

        // tree->printTreeHelper(tree);
    }

    // template <class T>
    node::Node<lexer::Token> *Parser::shuntingYardPostFix(std::vector<lexer::Token> tokens)
    {
        stack::stack<lexer::Token> op_stack;
        stack::stack<node::Node<lexer::Token> *> exp_stack;

        for (auto &&token : tokens)
        {
            if (lexer::Lexer::isInteger(token.value))
            {
                exp_stack.push_back(new node::Node<lexer::Token>(token));
            }
            else if (lexer::Lexer::isOperator(token.value) || lexer::Lexer::isBracket(*token.value.c_str()))
            {
                if (!lexer::Lexer::isLeftBracket(*token.value.c_str()))
                {
                    while (!op_stack.empty() && ((lexer::Lexer::isRightBracket(*token.value.c_str()) && !lexer::Lexer::isLeftBracket(*op_stack.top().value.c_str())) || (lexer::operators[op_stack.top().value].precedence > lexer::operators[token.value].precedence) || ((lexer::operators[op_stack.top().value].precedence == lexer::operators[token.value].precedence) && (lexer::operators[token.value].associates == lexer::Associates::left_to_right))))
                    {
                        // output.push_back(op_stack.pop());
                        lexer::Token op = op_stack.pop();
                        node::Node<lexer::Token> *e2 = exp_stack.pop();
                        node::Node<lexer::Token> *e1 = exp_stack.pop();
                        exp_stack.push(new node::Node<lexer::Token>(op, e1, e2));
                    }
                    // If we popped until '(' because token is ')', toss both parens
                    if (lexer::Lexer::isRightBracket(*token.value.c_str()))
                        op_stack.pop();
                }
                // Everything except ')' --> stack
                if (!lexer::Lexer::isRightBracket(*token.value.c_str()))
                    op_stack.push(token);
            }
            else
            {
                std::cout << "";
            }
        }
        while (!op_stack.empty())
        {
            lexer::Token op = op_stack.pop();
            node::Node<lexer::Token> *e2 = exp_stack.pop();
            node::Node<lexer::Token> *e1 = exp_stack.pop();
            exp_stack.push(new node::Node<lexer::Token>(op, e1, e2));
        }

        return exp_stack.pop();
    }

    // void Parser::shuntingYardPreFix(std::vector<std::string> tokens, tree::Tree *tree)
    // {
    //     stack<std::string> output;
    //     stack<std::string> operatorStack;
    //     std::reverse(tokens.begin(), tokens.end());
    //     for (auto &&token : tokens)
    //     {
    //         if (lexer::isInteger(token))
    //         {
    //             output.push(token);
    //         }
    //         else if (lexer::isOperator(token) || lexer::isBracket(*token.c_str()))
    //         {
    //             if (!lexer::isRightBracket(*token.c_str()))
    //             {
    //                 while (!operatorStack.empty() && ((lexer::isLeftBracket(*token.c_str()) && !lexer::isRightBracket(*operatorStack.top().c_str())) || (lexer::operators[operatorStack.top()].precedence > lexer::operators[token].precedence) || ((lexer::operators[operatorStack.top()].precedence == lexer::operators[token].precedence) && (lexer::operators[token].associates == lexer::Associates::right_to_left))))
    //                 {
    //                     output.push(operatorStack.pop());
    //                 }
    //                 // If we popped until '(' because token is ')', toss both parens
    //                 if (lexer::isLeftBracket(*token.c_str()))
    //                 {
    //                     operatorStack.pop();
    //                 }
    //             }
    //             // Everything except ')' --> stack
    //             if (!lexer::isLeftBracket(*token.c_str()))
    //             {
    //                 operatorStack.push(token);
    //             }
    //         }
    //         else
    //         {
    //             std::cout << "";
    //         }
    //     }
    //     // Anything left on the operator stack just gets moved to the output
    //     while (!operatorStack.empty())
    //     {
    //         output.push_back(operatorStack.pop());
    //     }
    //     std::reverse(output.begin(), output.end());
    //     for (auto &&i : output)
    //     {
    //         std::cout << i;
    //     }
    // }
} // namespace parser