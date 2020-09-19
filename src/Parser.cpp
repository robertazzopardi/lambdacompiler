#include "Parser.h"
#include "Assembly.h"

namespace parser
{
    Parser::Parser()
    {
        // lines = filesLines;
    }

    void Parser::parseLines(std::vector<std::string> filesLines)
    {
        for (auto &&line : filesLines)
        {
            // lex the words on the line
            std::vector<lexer::Token> words = lexer::Lexer::lex(line);

            // create tree with shunting yard algorithm
            tree::Tree *tree = new tree::Tree();
            tree->curr = shuntingYardPostFix(words);

            // print the tree for debugging
            tree->printPostorder(tree->curr);
            std::cout << std::endl;

            // pretty print tree
            // tree->printTreeHelper(tree);

            // create assembly file
            // assembly::Assembly assembler;
            // assembler.createAssembly(tree->curr);
        }

        // std::vector<lexer::Token> words;
        // for (auto &&line : filesLines)
        // {
        //     std::vector<lexer::Token> tokens = lexer::Lexer::lex(line);
        //     words.insert(words.end(), tokens.begin(), tokens.end());
        // }

        // // create tree with shunting yard algorithm
        // tree::Tree *tree = new tree::Tree();
        // tree->curr = shuntingYardPostFix(words);

        // // print the post order tree
        // tree->printPostorder(tree->curr);
        // // tree->printPreorder(tree->curr);
        // std::cout << std::endl;

        // pretty print tree
        // tree->printTreeHelper(tree);

        // create assembly file
        // assembly::Assembly assembler;
        // assembler.createAssembly(tree->curr);
    }

    // template <class T>
    node::Node<lexer::Token> *Parser::shuntingYardPostFix(std::vector<lexer::Token> tokens)
    {
        stack::stack<lexer::Token> operator_stack;
        stack::stack<node::Node<lexer::Token> *> output_stack;

        for (auto &&token : tokens)
        {
            // std::cout << token << std::endl;
            if (lexer::Lexer::isInteger(token.value))
            {
                output_stack.push(new node::Node<lexer::Token>(token));
            }

            // else if (token.attribute == lexer::Attribute::print)
            // {
            //     operator_stack.push(token);

            //     // if (output_stack.size() > 1)
            //     // {
            //     //     node::Node<lexer::Token> *e = output_stack.pop();
            //     //     output_stack.push(new node::Node<lexer::Token>(token, e));
            //     // }
            //     // else
            //     // {
            //     //     operator_stack.push(token);
            //     // }
            // }

            else if (lexer::Lexer::isOperator(token.value) || lexer::Lexer::isBracket(*token.value.c_str()))
            {
                if (!lexer::Lexer::isLeftBracket(*token.value.c_str()))
                {
                    while (!operator_stack.empty() && ((lexer::Lexer::isRightBracket(*token.value.c_str()) && !lexer::Lexer::isLeftBracket(*operator_stack.top().value.c_str())) || (lexer::operators[operator_stack.top().value].precedence > lexer::operators[token.value].precedence) || ((lexer::operators[operator_stack.top().value].precedence == lexer::operators[token.value].precedence) && (lexer::operators[token.value].associates == lexer::Associates::left_to_right))))
                    {
                        lexer::Token op = operator_stack.pop();
                        node::Node<lexer::Token> *e2 = output_stack.pop();
                        node::Node<lexer::Token> *e1 = output_stack.pop();
                        output_stack.push(new node::Node<lexer::Token>(op, e1, e2));
                    }
                    // If we popped until '(' because token is ')', toss both parens
                    if (lexer::Lexer::isRightBracket(*token.value.c_str()))
                        operator_stack.pop();
                }
                // Everything except ')' --> stack
                if (!lexer::Lexer::isRightBracket(*token.value.c_str()))
                    operator_stack.push(token);
            }
            else
            {
                // std::cout << "";
            }
        }

        while (!operator_stack.empty())
        {
            lexer::Token op = operator_stack.pop();
            node::Node<lexer::Token> *e2 = output_stack.pop();
            node::Node<lexer::Token> *e1 = output_stack.pop();
            output_stack.push(new node::Node<lexer::Token>(op, e1, e2));
        }

        // while (!operator_stack.empty())
        // {
        //     if (output_stack.size() > 1)
        //     {
        //         lexer::Token op = operator_stack.pop();
        //         node::Node<lexer::Token> *e2 = output_stack.pop();
        //         node::Node<lexer::Token> *e1 = output_stack.pop();
        //         output_stack.push(new node::Node<lexer::Token>(op, e1, e2));
        //     }
        //     else
        //     {
        //         lexer::Token op = operator_stack.pop();
        //         auto n = output_stack.pop();
        //         output_stack.push(new node::Node<lexer::Token>(op, n));
        //     }
        // }

        return output_stack.pop();
    }

    // void Parser::shuntingYardPreFix(std::vector<std::string> tokens, tree::Tree *tree)
    // {
    //     stack<std::string> output_stack;
    //     stack<std::string> operatorStack;
    //     std::reverse(tokens.begin(), tokens.end());
    //     for (auto &&token : tokens)
    //     {
    //         if (lexer::isInteger(token))
    //         {
    //             output_stack.push(token);
    //         }
    //         else if (lexer::isOperator(token) || lexer::isBracket(*token.c_str()))
    //         {
    //             if (!lexer::isRightBracket(*token.c_str()))
    //             {
    //                 while (!operatorStack.empty() && ((lexer::isLeftBracket(*token.c_str()) && !lexer::isRightBracket(*operatorStack.top().c_str())) || (lexer::operators[operatorStack.top()].precedence > lexer::operators[token].precedence) || ((lexer::operators[operatorStack.top()].precedence == lexer::operators[token].precedence) && (lexer::operators[token].associates == lexer::Associates::right_to_left))))
    //                 {
    //                     output_stack.push(operatorStack.pop());
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
    //     // Anything left on the operator stack just gets moved to the output_stack
    //     while (!operatorStack.empty())
    //     {
    //         output_stack.push_back(operatorStack.pop());
    //     }
    //     std::reverse(output_stack.begin(), output_stack.end());
    //     for (auto &&i : output_stack)
    //     {
    //         std::cout << i;
    //     }
    // }
} // namespace parser