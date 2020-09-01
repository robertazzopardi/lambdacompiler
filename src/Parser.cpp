#include "Parser.h"

namespace parser
{
    Parser::Parser(std::vector<std::string> filesLines)
    {
        Parser::lines = filesLines;
    }

    void Parser::parseLines()
    {
        for (auto &&line : lines)
        {
            Parser::parseLine(line);
        }
    }

    void Parser::parseLine(std::string line)
    {
        std::vector<token::Token> words = removeDupWord(line);

        tree::Tree *tree = new tree::Tree();
        tree->curr = shuntingYardPostFix(words);

        tree->printPreorder(tree->curr);
        std::cout << std::endl;

        // printTreeHelper(tree);
    }

    void Parser::printTreeHelper(tree::Tree *tree)
    {
        int h = tree->getDepth(tree->curr);
        for (size_t i = 1; i <= h; i++)
        {
            if (i > 1)
            {
                std::cout << std::endl;
                for (size_t j = 0; j < std::pow(2, h - i) - 1; j++)
                    std::cout << "  ";
            }
            else
            {
                for (size_t j = 0; j < std::pow(2, h - i) - 1; j++)
                    std::cout << " ";
            }

            formatPrintTree(tree->curr, i, h);
        }
        std::cout << "\n"
                  << std::endl;
    }

    template <class T>
    void Parser::formatPrintTree(const node::Node<T> *node, int level, int depth)
    {
        if (node == nullptr)
            return;

        if (level == 1)
        {
            std::cout << node->data;
        }
        else if (level > 1)
        {
            formatPrintTree(node->leftNode, level - 1, depth);

            for (size_t j = 0; j < std::pow(2, depth - level - 1); j++)
                std::cout << " ";

            formatPrintTree(node->rightNode, level - 1, depth);
        }
    }

    // std::vector<std::string> Parser::splitString(std::string line)
    // {
    //     // Used to split string at spaces;
    //     std::vector<std::string> out;
    //     std::istringstream iss(line);
    //     for (std::string s; iss >> s;)
    //         out.push_back(s);
    //     return out;
    // }

    std::vector<token::Token> Parser::removeDupWord(std::string str)
    {

        //////////////////////////////////////////////////////////////////////////////////
        // std::vector<std::string> split;
        std::vector<token::Token> tokens;
        for (auto &&text : lexer::Lexer::splitString(str))
        {
            if (text.find('(') != std::string::npos)
            {
                while (text.find('(') != std::string::npos)
                {
                    token::Token token(lexer::Attribute::lparen, text.substr(0, 1));
                    tokens.push_back(token);
                    text = text.substr(1, text.length());
                }
                token::Token token(lexer::Attribute::lparen, text);
                tokens.push_back(token);

            } // found
            else if (text.find(')') != std::string::npos)
            {
                std::reverse(text.begin(), text.end());
                while (text.find(')') != std::string::npos)
                {
                    token::Token token(lexer::Attribute::rparen, text.substr(text.length() - 1, text.length()));
                    tokens.push_back(token);
                    text = text.substr(0, text.length() - 1);
                }
                token::Token token(lexer::Attribute::rparen, text);
                tokens.push_back(token);

            } // found
            else if (lexer::Lexer::isOperator(text))
            {
                // TODO:
                token::Token token(lexer::Attribute::opadd, text);
                tokens.push_back(token);
            }
            else if (lexer::Lexer::isInteger(text))
            {
                token::Token token(lexer::Attribute::integer, text);
                tokens.push_back(token);
            }
            else
            {
                // not found
                for (auto &&i : text)
                {
                    std::stringstream ss;
                    std::string s;
                    ss << i;
                    ss >> s;
                    std::cout << s;

                    token::Token token(lexer::Attribute::integer, s);

                    tokens.push_back(token);
                }
            }
        }

        return tokens;
    }

    // template <class T>
    node::Node<token::Token> *Parser::shuntingYardPostFix(std::vector<token::Token> tokens)
    {
        stack::stack<token::Token> op_stack;
        stack::stack<node::Node<token::Token> *> exp_stack;

        for (auto &&token : tokens)
        {
            if (lexer::Lexer::isInteger(token.value))
            {
                exp_stack.push_back(new node::Node<token::Token>(token));
            }
            else if (lexer::Lexer::isOperator(token.value) || lexer::Lexer::isBracket(*token.value.c_str()))
            {
                if (!lexer::Lexer::isLeftBracket(*token.value.c_str()))
                {
                    while (!op_stack.empty() && ((lexer::Lexer::isRightBracket(*token.value.c_str()) && !lexer::Lexer::isLeftBracket(*op_stack.top().value.c_str())) || (lexer::operators[op_stack.top().value].precedence > lexer::operators[token.value].precedence) || ((lexer::operators[op_stack.top().value].precedence == lexer::operators[token.value].precedence) && (lexer::operators[token.value].associates == lexer::Associates::left_to_right))))
                    {
                        // output.push_back(op_stack.pop());
                        token::Token op = op_stack.pop();
                        node::Node<token::Token> *e2 = exp_stack.pop();
                        node::Node<token::Token> *e1 = exp_stack.pop();
                        exp_stack.push(new node::Node<token::Token>(op, e1, e2));
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
            token::Token op = op_stack.pop();
            node::Node<token::Token> *e2 = exp_stack.pop();
            node::Node<token::Token> *e1 = exp_stack.pop();
            exp_stack.push(new node::Node<token::Token>(op, e1, e2));
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