#include "Node.hpp"
#include <asm-generic/errno.h>
#include <map>
#include <string>


std::map<char, int> OPERATORS_PRIORITY = {
    {'c', 3}, // косинус
    {'s', 3}, // синус
    {'t', 3}, // тангенс
    {'g', 3}, // котангенс
    {'e', 3}, // экспонента e^x
    {'^', 2},
    {'*', 1},
    {'/', 1},
    {'+', 0},
    {'-', 0}
};

std::map<char, TYPE> OPERATORS_TYPE = {
    {'c', COS}, // косинус
    {'s', SIN}, // синус
    {'t', TAN}, // тангенс
    {'g', CTAN}, // котангенс
    {'e', EXP}, // экспонента e^x
    {'^', POW},
    {'*', MULT},
    {'/', DIV},
    {'+', PLUS},
    {'-', MINUS}
};

std::string NUMBERS = ".0123456789";

Node::Node(Node* parent, std::string expression){
    this->parent = parent;
    if(expression == ""){
        type = NUMB;
        value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }else if(is_reduced(expression)){
        VALUE value = calculate(expression);
        type = value.type;
        if(value.type == VAR){
            var = value.var;
        }else{
            this->value = value.value;
        }
        this->left = nullptr;
        this->right = nullptr;
    }else{
        RESULT result = bend_string(expression);
        type = result.type;

        this->left = new Node(this, result.left);
        this->right = new Node(this, result.right);
    }

}

Node::~Node(){
    if(left != nullptr) delete left;
    if(right != nullptr) delete right;
}

bool Node::is_reduced(std::string expression){
    bool result = true;
    for(auto i: expression){
        if(OPERATORS_PRIORITY.find(i) != OPERATORS_PRIORITY.end()) result = false;
    }
    return result;
}

bool Node::is_wrapped(std::string expression){
    if(expression == "") return false;
    if(expression[0] != '(') return false;
    int count_brackets{0};
    for(int i{}; i < expression.size(); ++i){
        if(expression[i] == '(') ++count_brackets;
        else if(expression[i] == ')') --count_brackets;
        else if(count_brackets == 0 && i+1 != expression.size()) return false;
    }
    return true;

}

VALUE Node::calculate(std::string expression){
    VALUE result;
    while(is_wrapped(expression)){
        expression.pop_back();
        expression.erase(0,1);
    }
    if(NUMBERS.find(expression[0]) == std::string::npos){
        result.type = VAR;
        result.var = expression;
    }else{
        result.type = NUMB;
        result.value =  std::stof(expression);
    }
    
    return result;
}

RESULT Node::bend_string(std::string expression){
    RESULT result;

    while(is_wrapped(expression)){
        expression.pop_back();
        expression.erase(0,1);
    }
    char min_operator{-1};
    int operator_index{-1};
    int count_brackets{0};

    for(int i{}; i < expression.size(); ++i){
        if(expression[i]=='(')++count_brackets;
        else if(expression[i]==')') --count_brackets;
        else if(count_brackets > 0) continue;

        if(OPERATORS_PRIORITY.find(expression[i]) == OPERATORS_PRIORITY.end()){
            continue;
        }

        if(min_operator == -1){
            min_operator = expression[i];
            operator_index = i;
        }

        if(OPERATORS_PRIORITY[expression[i]] <= OPERATORS_PRIORITY[min_operator]){
            min_operator = expression[i];
            operator_index = i;
        } 
    }

    result.type = OPERATORS_TYPE[min_operator];
    result.left = expression.substr(0, operator_index);
    result.right = expression.substr(operator_index+1, expression.size()-1);
    return result;
}


Dot::Dot(Dot *  parent, int n){
    this->parent = parent;
    if(n <= 0){
        left = nullptr;
        right = nullptr;
        value = -1;
    }else{
        value = n;
        left = new Dot(this, n-1);
        right = new Dot(this, n-2);
    }
}