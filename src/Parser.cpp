#include "Parser.h"
#include "Assembly.h"

namespace parser
{
    std::string Parser::filename = "";
    std::map<std::string, bool> Parser::flags = {
        {"-asm", false},
        {"-run", false}};

    Parser::Parser()
    {
        // lines = filesLines;
    }

    void Parser::parseLines(std::vector<std::string> filesLines)
    {
        for (auto &&line : filesLines)
        {
            parseLine(line);
        }
    }

    void Parser::parseLine(std::string line)
    {
        std::vector<lexer::Token> words = lexer::Lexer::lex(line);

        tree::Tree *tree = new tree::Tree();
        tree->curr = shuntingYardPostFix(words);

        // tree->printPreorder(tree->curr);
        // std::cout << std::endl;

        assembly::Assembly assembler;
        assembler.createAssembly(tree->curr);

        // tree->printTreeHelper(tree);
    }

    // template <class T>
    node::Node<lexer::Token> *Parser::shuntingYardPostFix(std::vector<lexer::Token> tokens)
    {
        stack::stack<lexer::Token> op_stack;
        stack::stack<node::Node<lexer::Token> *> exp_stack;

        for (auto &&token : tokens)
        {
            if (lexer::Lexer::isInt(token.value))
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

    void Parser::parseArgs(int argc, char *argv[])
    {
        // check if there is enough args
        if (argc == 1)
        {
            std::cout << "Too Few Arguements" << std::endl;
            exit(0);
        }

        std::vector<std::string> invalidFlags;
        // loop trailing args
        for (size_t i = 1; i < argc; i++)
        {
            std::string arg(argv[i]);

            // look for file to be compiled
            // if found set filename
            auto extensionFound = arg.find(".lambda");
            if (extensionFound != std::string::npos)
            {
                Parser::filename = arg;
            }

            // check if flags are valid
            auto it = Parser::flags.find(arg);
            if (it != Parser::flags.end())
            {
                it->second = true;
            }
            else
            {
                if (arg != filename)
                {
                    invalidFlags.push_back(arg);
                }
            }
        }

        if (filename == "")
        {
            std::cout << "Expected A .lambda File" << std::endl;
        }
        else if (invalidFlags.size() != 0)
        {
            std::cout << (invalidFlags.size() == 1 ? "Invalid Arguement: " : "Invalid Arguements: ");
            for (auto &&i : invalidFlags)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            // std::cout << "fine" << std::endl;
        }
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