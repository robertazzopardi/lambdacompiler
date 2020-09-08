#include "Parser.h"

namespace parser
{
    Parser::Parser(std::vector<std::string> filesLines)
    {
<<<<<<< HEAD
        lines = filesLines;
    }

    void Parser::parseLines()
=======
        p::Parser::parseLine(line);
    }
}

void p::Parser::parseLine(std::string line)
{
    std::vector<std::string> words = removeDupWord(line);

    class tr::Tree *tree = new tr::Tree();
    // n::Node<std::string> *parsedNode = shuntingYardPostFix(words);
    tree->curr = shuntingYardPostFix(words);
    // tree->curr = parsedNode;

    tree->printPreorder(tree->curr);
    std::cout << std::endl;
    // printTreeHelper(tree);
}

void p::Parser::printTreeHelper(tr::Tree *tree)
{
    int h = tree->getDepth(tree->curr);
    for (size_t i = 1; i <= h; i++)
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
    {
        for (auto &&line : lines)
        {
            parseLine(line);
        }
    }

<<<<<<< HEAD
    void Parser::parseLine(std::string line)
    {
        std::vector<lexer::Token> words = lexer::Lexer::lex(line);

        tree::Tree *tree = new tree::Tree();
        tree->curr = shuntingYardPostFix(words);
=======
template <class T>
void p::Parser::formatPrintTree(const n::Node<T> *node, int level, int depth)
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
        // std::cout << "x";
        for (size_t j = 0; j < std::pow(2, depth - level - 1); j++)
            std::cout << " ";

        formatPrintTree(node->rightNode, level - 1, depth);
    }
}

// std::string trim(const std::string &str)
// {
//     size_t first = str.find_first_not_of(' ');
//     if (std::string::npos == first)
//     {
//         return str;
//     }
//     size_t last = str.find_last_not_of(' ');
//     return str.substr(first, (last - first + 1));
// }

std::vector<std::string> p::Parser::removeDupWord(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);
    std::vector<std::string> out;
    // Traverse through all words
    std::string token;
    while (ss >> token)
        out.push_back(token);

    //---------------
    std::vector<std::string> split;
    for (auto &&text : out)
    {
        if (text.find('(') != std::string::npos)
        {
            while (text.find('(') != std::string::npos)
            {
                split.push_back(text.substr(0, 1));
                text = text.substr(1, text.length());
            }
            split.push_back(text);

        } // found
        else if (text.find(')') != std::string::npos)
        {
            std::reverse(text.begin(), text.end());
            while (text.find(')') != std::string::npos)
            {
                split.push_back(text.substr(text.length() - 1, text.length()));
                text = text.substr(0, text.length() - 1);
            }
            split.push_back(text);
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f

        tree->printPreorder(tree->curr);
        std::cout << std::endl;

        // tree->printTreeHelper(tree);
    }

    // template <class T>
    node::Node<lexer::Token> *Parser::shuntingYardPostFix(std::vector<lexer::Token> tokens)
    {
<<<<<<< HEAD
        stack::stack<lexer::Token> op_stack;
        stack::stack<node::Node<lexer::Token> *> exp_stack;

        for (auto &&token : tokens)
=======
        return base_type::empty();
    }
};

template <class T>
n::Node<T> *p::Parser::shuntingYardPostFix(std::vector<T> tokens)
{
    stack<std::string> op_stack;
    stack<n::Node<std::string> *> exp_stack;

    for (auto &&token : tokens)
    {
        if (c::isInteger(token))
        {
            exp_stack.push_back(new n::Node<std::string>(token));
        }
        else if (c::isOperator(token) || c::isBracket(*token.c_str()))
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
        {
            if (lexer::Lexer::isInt(token.value))
            {
<<<<<<< HEAD
                exp_stack.push_back(new node::Node<lexer::Token>(token));
            }
            else if (lexer::Lexer::isOperator(token.value) || lexer::Lexer::isBracket(*token.value.c_str()))
=======
                while (!op_stack.empty() && ((c::isRightBracket(*token.c_str()) && !c::isLeftBracket(*op_stack.top().c_str())) || (c::operators[op_stack.top()].precedence > c::operators[token].precedence) || ((c::operators[op_stack.top()].precedence == c::operators[token].precedence) && (c::operators[token].associates == c::Associates::left_to_right))))
                {
                    // output.push_back(op_stack.pop());
                    std::string op = op_stack.pop();
                    class n::Node<std::string> *e2 = exp_stack.pop();
                    class n::Node<std::string> *e1 = exp_stack.pop();
                    exp_stack.push(new n::Node<std::string>(op, e1, e2));
                }
                // If we popped until '(' because token is ')', toss both parens
                if (c::isRightBracket(*token.c_str()))
                    op_stack.pop();
            }
            // Everything except ')' --> stack
            if (!c::isRightBracket(*token.c_str()))
                op_stack.push(token);
        }
        else
        {
            std::cout << "";
        }
    }
    while (!op_stack.empty())
    {
        std::string op = op_stack.pop();
        class n::Node<std::string> *e2 = exp_stack.pop();
        class n::Node<std::string> *e1 = exp_stack.pop();
        exp_stack.push(new n::Node<std::string>(op, e1, e2));
        // output.push_back(stack.pop());
    }

    return exp_stack.pop();
}

void p::Parser::shuntingYardPreFix(std::vector<std::string> tokens, tr::Tree *tree)
{
    stack<std::string> output;
    stack<std::string> operatorStack;

    std::reverse(tokens.begin(), tokens.end());

    for (auto &&token : tokens)
    {
        if (c::isInteger(token))
        {
            output.push(token);
        }
        else if (c::isOperator(token) || c::isBracket(*token.c_str()))
        {
            if (!c::isRightBracket(*token.c_str()))
>>>>>>> 8a8888b9ebd72cf75f87fa2c2fd842bcfc7f736f
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