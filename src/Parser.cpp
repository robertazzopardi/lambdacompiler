#include "Parser.h"
#include "Assembly.h"

namespace parser
{
    Parser::Parser()
    {
    }

    void Parser::parseLines(std::vector<std::string> filesLines)
    {
        std::vector<tree::Tree *> trees;

        for (auto &&line : filesLines)
        {
            std::vector<lexer::Token> tokens = lexer::Lexer::lex(line);

            // create tree with shunting yard algorithm
            tree::Tree *tree = new tree::Tree();
            tree->root = shuntingYardPostFix(tokens);

            tree->setTreeNodeParents(tree->root);

            // tree->printPostorder(tree->root);

            std::cout << std::endl
                      << std::endl;

            trees.push_back(tree);
        }

        // create assembly file
        assembly::Assembly assembler;
        assembler.createAssembly(trees);
    }

    node::Node<lexer::Token> *Parser::shuntingYardPostFix(std::vector<lexer::Token> tokens)
    {
        stack::stack<lexer::Token> operator_stack;
        stack::stack<node::Node<lexer::Token> *> output_stack;

        for (auto &&token : tokens)
        {
            if (token.attribute == lexer::Attribute::floatpt || token.attribute == lexer::Attribute::integer)
            {
                output_stack.push(new node::Node<lexer::Token>(token));
            }
            else if (token.attribute == lexer::Attribute::func)
            {
                if (output_stack.size() > 1)
                {
                    node::Node<lexer::Token> *e = output_stack.pop();
                    output_stack.push(new node::Node<lexer::Token>(token, e));
                }
                else
                {
                    operator_stack.push(token);
                }
            }
            else if (token.attribute == lexer::Attribute::op || token.attribute == lexer::Attribute::lparen || token.attribute == lexer::Attribute::rparen)
            {
                if (token.attribute != lexer::Attribute::lparen)
                {
                    while (!operator_stack.empty() && ((token.attribute == lexer::Attribute::rparen && operator_stack.top().attribute != lexer::Attribute::lparen) || (lexer::operators[*operator_stack.top().value.c_str()].precedence > lexer::operators[*token.value.c_str()].precedence) || ((lexer::operators[*operator_stack.top().value.c_str()].precedence == lexer::operators[*token.value.c_str()].precedence) && (lexer::operators[*token.value.c_str()].associates == lexer::Associates::left_to_right))))
                    {
                        lexer::Token op = operator_stack.pop();
                        node::Node<lexer::Token> *e2 = output_stack.pop();
                        node::Node<lexer::Token> *e1 = output_stack.pop();
                        output_stack.push(new node::Node<lexer::Token>(op, e1, e2));
                    }
                    // If we popped until '(' because token is ')', toss both parens
                    if (token.attribute == lexer::Attribute::rparen)
                        operator_stack.pop();
                }
                // Everything except ')' --> stack
                if (token.attribute != lexer::Attribute::rparen)
                    operator_stack.push(token);
            }
            else
            {
                // std::cout << "";
            }
        }

        // add remaining operators from the operator stack
        addRemainingOperators(operator_stack, output_stack);

        return output_stack.pop();
    }

    void Parser::addRemainingOperators(stack::stack<lexer::Token> &operator_stack, stack::stack<node::Node<lexer::Token> *> &output_stack)
    {
        while (!operator_stack.empty())
        {
            if (output_stack.size() > 1)
            {
                lexer::Token op = operator_stack.pop();
                node::Node<lexer::Token> *e2 = output_stack.pop();
                node::Node<lexer::Token> *e1 = output_stack.pop();
                output_stack.push(new node::Node<lexer::Token>(op, e1, e2));
            }
            else
            {
                lexer::Token op = operator_stack.pop();
                auto n = output_stack.pop();
                output_stack.push(new node::Node<lexer::Token>(op, n));
            }
        }
    }
} // namespace parser