#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

#include "../include/Parser.hpp"
#include "../include/Constants.hpp"
#include "../include/Tree.hpp"

p::Parser::Parser()
{
}

void p::Parser::parseLine(std::string line)
{
    std::vector<std::string> words = removeDupWord(line);

    class tr::Tree *tree = new tr::Tree();
    calculate(words, tree);

    tree->printPreorder(tree->curr);
    std::cout << std::endl;
}

std::string trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> p::Parser::removeDupWord(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);
    std::vector<std::string> out;
    // Traverse through all words
    do
    {
        // Read a word
        std::string word;
        ss >> word;

        // Print the read word
        // cout << word << endl;
        out.push_back(word);
        // While there is more to read
    } while (ss);

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

        } // found
        else if (isOperator(text))
        {

            split.push_back(text);
        }
        else if (isInteger(text))
        {
            split.push_back(text);
        } // not found
        else
        {
            // std::cout << text;
            for (auto &&i : text)
            {
                std::stringstream ss;
                std::string s;
                // char c = 'a';
                ss << i;
                ss >> s;
                split.push_back(s);
            }
        }
    }

    return split;
}

bool p::Parser::isInteger(const std::string &s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

bool p::Parser::isOperator(std::string val)
{
    return c::operators.count(val) > 0;
    // return find(c::SIGNS.begin(), c::SIGNS.end(), val) != c::SIGNS.end();
}

bool p::Parser::isBracket(const char &val)
{
    return c::LB == val || c::RB == val;
}

bool p::Parser::isLeftBracket(const char &val)
{
    return c::LB == val;
}

bool p::Parser::isRightBracket(const char &val)
{
    return c::RB == val;
}

std::string p::Parser::pop(std::vector<std::string> vec)
{
    auto x = std::move(vec.back());
    vec.pop_back();
    return x;
}

template <typename T>
struct stack : public std::vector<T>
{
    using base_type = std::vector<T>;
    T push(const T &x)
    {
        base_type::push_back(x);
        return x;
    }
    const T &top() { return base_type::back(); }
    T pop()
    {
        T x = std::move(top());
        base_type::pop_back();
        return x;
    }
    bool empty() { return base_type::empty(); }
};

void p::Parser::calculate(std::vector<std::string> tokens, tr::Tree *tree)
{
    // enum class Associates
    // {
    //     none,
    //     left_to_right,
    //     right_to_left
    // };
    // struct info
    // {
    //     int precedence;
    //     Associates associates;
    // };
    // std::map<std::string, info> operators{{"^", {4, Associates::right_to_left}},
    //                                       {"*", {3, Associates::left_to_right}},
    //                                       {"/", {3, Associates::left_to_right}},
    //                                       {"+", {2, Associates::left_to_right}},
    //                                       {"-", {2, Associates::left_to_right}}};
    std::vector<std::string> output;
    stack<std::string> stack;

    for (auto token : tokens) // Shunting Yard takes a single linear pass through the tokens

        //.........................................................................
        if (isInteger(token))
        {
            output.push_back(token);
        }

        //.........................................................................
        else if (isOperator(token) or isBracket(*token.c_str()))
        {

            if (!isLeftBracket(*token.c_str()))
            {
                // pop --> output
                //   : until '(' if token is ')'
                //   : while prec(token) > prec(top)
                //   : while prec(token) == prec(top) AND assoc(token) is left-to-right
                while (!stack.empty() and ((isRightBracket(*token.c_str()) and !isLeftBracket(*stack.top().c_str())) or (c::operators[stack.top()].precedence > c::operators[token].precedence) or ((c::operators[stack.top()].precedence == c::operators[token].precedence) and (c::operators[token].associates == c::Associates::left_to_right))))
                {
                    output.push_back(stack.pop());
                }

                // If we popped until '(' because token is ')', toss both parens
                if (isRightBracket(*token.c_str()))
                {
                    stack.pop();
                }
            }

            // Everything except ')' --> stack
            if (!isRightBracket(*token.c_str()))
            {
                stack.push(token);
            }
        }

        //.........................................................................
        else
            std::cout << "";

    // Anything left on the operator stack just gets moved to the output

    while (!stack.empty())
    {
        output.push_back(stack.pop());
    }

    for (auto &&i : output)
    {
        std::cout << i;
    }

    std::cout
        << "  ";
    // tree->curr = tree->createExpressionTree(tokens);
    std::cout << "              ";
}

// if (std::find(tokens.begin(), tokens.end(), "(") == tokens.end() && std::find(tokens.begin(), tokens.end(), ")") == tokens.end())
// {
//     auto count = tokens.size() - std::count_if(tokens.begin(), tokens.end(), [](auto a) { return isInteger(a); });
//     int j = 0;
//     for (size_t i = 0; i < count; i++)
//     {
//         tree->cmsrLeft(tokens[j++]);
//         tree->setValue(tokens[j++]);
//         tree->createRight();
//         tree->moveRight();
//         if (i + 1 == count)
//         {
//             tree->setValue(tokens[j]);
//             break;
//         }
//     }
//     while (tree->curr->parent != nullptr)
//     {
//         tree->moveAbove();
//     }
// }
// else
// {
//     std::vector<std::string> nums;
//     std::vector<std::string>::iterator iter1 = tokens.begin();
//     while ((iter1 = std::find_if(iter1, tokens.end(), [](auto a) { return isInteger(a); })) != tokens.end())
//     {
//         std::cout << *iter1;

//         // tree->setNumbers(tree->curr, *iter1);

//         // iter1++;
//         nums.push_back(*iter1++);
//     }

//     // tree->setNumbers(tree->curr, nums);

//     while (tree->curr->parent != nullptr)
//     {
//         tree->moveAbove();
//     }
//     std::cout << " ";
//     // /////////////////////////////////////////////////////////////////////////////////////////
//     // std::cout << std::count_if(tokens.begin(), tokens.end(), [](auto a) { return isSign(*a.c_str()); });
//     int depth = std::count_if(tokens.begin(), tokens.end(), [](auto a) { return isSign(*a.c_str()); });
//     // std::cout << depth << std::endl;
//     std::vector<std::string>::iterator iter = tokens.begin();
//     int i = 0;
//     int numOfSigns = 0;
//     bool isRight = false;
//     while ((iter = std::find_if(iter, tokens.end(), [](auto a) { return isSign(*a.c_str()) || isBracket(*a.c_str()); })) != tokens.end())
//     {
//         // Do something with iter
//         // std::cout << (*iter);
//         int index = iter - tokens.begin();
//         std::cout << i;
//         if (*iter == "(")
//         {
//             if (isRight && tree->curr->left == nullptr && tree->curr->right == nullptr)
//             {

//                 tree->createLeft();
//                 tree->moveLeft();
//                 isRight = false;
//             }
//             else if (tree->curr->left == nullptr && tree->curr->right == nullptr)
//             { //left bracket
//                 tree->createLeft();

//                 tree->curr->left->data = nums[i++];
//                 tree->createRight();
//                 tree->curr->right->data = nums[i++];
//                 // i--;
//             }
//             else if (tree->curr->left != nullptr && tree->curr->right != nullptr && tree->curr->parent != nullptr && tree->curr->parent->data.empty())
//             {
//                 tree->moveAbove();
//             }
//             else if (tree->curr->right != nullptr && isInteger(tree->curr->right->data))
//             {
//                 // tree->moveAbove();

//                 if (tree->curr->left == nullptr)
//                 {
//                     tree->createLeft();
//                     tree->curr->left->data = tree->curr->data;
//                     tree->curr->data = "";
//                 }
//             }
//             else
//             { //shift
//                 tree->moveRight();
//                 tree->createLeft();
//                 // tree->moveAbove();
//                 tree->curr = tree->rightRotation(tree->curr);
//             }
//         }
//         else if (*iter == ")")
//         { //right bracket
//             if (tree->curr->parent == nullptr)
//             {
//                 tree->curr->parent = new tr::Node();
//                 tree->curr->parent->left = tree->curr;
//                 tree->moveAbove();
//             }
//             else if (tree->curr->data.empty() && tree->curr->right != nullptr && tree->curr->right->data.empty())
//             {
//                 //nothing
//             }
//             else if (tree->curr->data.empty())
//             {
//                 tree->setValue(nums[i++]);
//             }

//             else if (tree->curr->parent != nullptr && tree->curr->parent->data.empty())
//             {
//                 tree->moveAbove();
//             }

//             // else if (tree->curr->right != nullptr && isSign(*tree->curr->data.c_str()) && tree->curr->parent != nullptr && tree->curr->parent->left != nullptr)
//             // {
//             //     class tr::Node *tmp = new tr::Node();
//             //     tmp->left = tree->curr;

//             //     tree->curr = tmp;
//             // }
//             else if (tree->curr->right != nullptr)
//             {

//                 tree->moveRight();
//             }
//         }
//         else
//         { //sign
//             //value is set
//             if (tree->curr->left != nullptr && tree->curr->right != nullptr && tree->curr->left->data.empty() && tree->curr->right->data.empty())
//             {

//                 class tr::Node *tmp = new tr::Node();
//                 tmp->data = *iter;
//                 tmp->left = new tr::Node();
//                 tmp->left->data = nums[i++];
//                 tmp->right = new tr::Node();
//                 tmp->right->data = nums[i++];

//                 tree->curr->left = tmp;
//             }
//             else if (tree->curr->left != nullptr && tree->curr->right != nullptr && !tree->curr->left->data.empty() && !tree->curr->right->data.empty())
//             {
//                 tree->setValue(*iter);
//             }
//             else if (tree->curr->left != nullptr && tree->curr->right != nullptr && !tree->curr->left->data.empty() && tree->curr->right->data.empty())
//             {
//                 tree->setValue(*iter);
//                 tree->moveRight();
//             }

//             else if (tree->curr->left == nullptr && tree->curr->right == nullptr)
//             {
//                 tree->setValue(*iter);
//                 tree->createLeft();
//                 tree->curr->left->data = nums[i++];
//                 tree->createRight();
//                 tree->curr->right->data = nums[i++];
//                 // i--;
//             }
//             else if (tree->curr->left != nullptr && tree->curr->right == nullptr)
//             {
//                 // std::cout << "ds";

//                 tree->setValue(*iter);

//                 tree->createRight();
//                 // tree->curr->right->data = nums[i++];
//                 tree->moveRight();
//                 isRight = true;
//                 // i--;
//             }
//             else
//             {
//                 // std::cout << *iter << " iter";
//                 tree->setValue(*iter);
//             }
//         }

//         iter++;
//     }

//     while (tree->curr->parent != nullptr)
//     {
//         tree->moveAbove();
//     }

//     // std::vector<std::string> nums;
//     // std::vector<std::string>::iterator iter1 = tokens.begin();
//     // while ((iter1 = std::find_if(iter1, tokens.end(), [](auto a) { return isInteger(a); })) != tokens.end())
//     // {
//     //     std::cout << *iter1;

//     //     // tree->setNumbers(tree->curr, *iter1);

//     //     iter1++;
//     //     // nums.push_back(*iter1++);
//     // }

//     // // tree->setNumbers(tree->curr, nums);

//     // while (tree->curr->parent != nullptr)
//     // {
//     //     tree->moveAbove();
//     // }
//     std::cout << "    ";