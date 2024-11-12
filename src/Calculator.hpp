#include "Node.hpp"
#include <map>




class Calculator{
private:
public:
    static float calcul(std::map<std::string, float> &stack, Node* node);
    static void set_stack(std::map<std::string, float> &stack, Node* node);
    static float calculate(std::string expression);
    static int cat(Dot* dot);
};