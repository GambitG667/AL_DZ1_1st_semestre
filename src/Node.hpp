#include <string>


enum TYPE{
    COS,
    SIN,
    TAN,
    CTAN,
    EXP, // экспонента
    POW, // возведение в степень
    MULT,
    DIV,
    PLUS,
    MINUS,
    VAR,
    NUMB
};

struct VALUE{
    TYPE type;
    float value;
    std::string var;
};

struct RESULT{
    TYPE type;
    std::string left;
    std::string right;
};


class Dot{
public:
    Dot * parent;
    Dot * left;
    Dot * right;
    int value;
    Dot(Dot* parent, int n);
};

class Node{
private:
    bool is_reduced(std::string expression);
    bool is_wrapped(std::string expression);
    VALUE calculate(std::string expression);
    RESULT bend_string(std::string expression);
public:
    TYPE type;
    Node* parent;
    Node* left;
    Node* right;
    float value=0;
    std::string var;
    
    Node(Node* parent, std::string );
    ~Node();
};

