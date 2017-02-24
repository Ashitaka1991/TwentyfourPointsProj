#ifndef CALNODE_H
#define CALNODE_H


class CalNode
{
public:

    CalNode(CalNode& cn);
    CalNode(char val);
    CalNode(int val);

    int numerator;
    int denominator;
    char c_operator;

    bool isNumber();
    bool isOperator();
    void setNodeValue(char val);
    void setNodeValue(int val);

    CalNode& operator+=(const CalNode& c_node);
    CalNode& operator-=(const CalNode& c_node);
    CalNode& operator*=(const CalNode& c_node);
    CalNode& operator/=(const CalNode& c_node);

private:
    CalNode();

    enum{NUMBER = 0 , OPERATOR};

    int type_flag;
    void setTypeAsNumber();
    void setTypeAsOperator();

};

CalNode operator+(CalNode& f_node , const CalNode& b_node);
CalNode operator-(CalNode& f_node , const CalNode& b_node);
CalNode operator*(CalNode& f_node , const CalNode& b_node);
CalNode operator/(CalNode& f_node , const CalNode& b_node);

//operators for pointer------invalid
//CalNode* operator+(CalNode* f_np,const CalNode* b_np);

#endif // CALNODE_H
