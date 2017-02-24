#include "calnode.h"

//#include <QDebug>

//constructors
CalNode::CalNode(CalNode& cn)
{
    this->c_operator = cn.c_operator;
    this->denominator = cn.denominator;
    this->numerator = cn.numerator;
    this->type_flag = cn.type_flag;
}

CalNode::CalNode(char val)
{
    setNodeValue(val);
}

CalNode::CalNode(int val)
{
    setNodeValue(val);
}

//public functions
bool CalNode::isNumber()
{
    if(type_flag == NUMBER){
        return true;
    }
    else{
        return false;
    }
}

bool CalNode::isOperator()
{
    if(type_flag == OPERATOR){
        return true;
    }
    else{
        return false;
    }
}

void CalNode::setNodeValue(char val)
{
    int t_difference = val - '0';
    if((t_difference >= 0) && (t_difference <=9)){
        setTypeAsNumber();
        numerator = t_difference;
        denominator = 1;
        c_operator = '\0';
    }
    else{
        setTypeAsOperator();
        c_operator = val;
        numerator = 0;
        denominator = 1;
    }

    return;
}

void CalNode::setNodeValue(int val)
{
    setTypeAsNumber();;
    numerator = val;
    denominator = 1;
    c_operator = '\0';
}


//operators

CalNode& CalNode::operator+=(const CalNode& c_node)
{
    int t_denominator = denominator;

    numerator *= c_node.denominator;
    denominator *= c_node.denominator;

    numerator += (c_node.numerator*t_denominator);

    return *this;
}

CalNode& CalNode::operator-=(const CalNode& c_node)
{
    int t_denominator = denominator;

    //qDebug() << "Before *=: " << numerator;

    numerator *= c_node.denominator;

    //qDebug() << "  Before *=: " << numerator;

    denominator *= c_node.denominator;

    //qDebug() << "  Before -=: " << numerator;

    numerator -= (c_node.numerator*t_denominator);

    //qDebug() << "  After -=: " << numerator << endl;

    return *this;

}

CalNode& CalNode::operator*=(const CalNode& c_node)
{
    numerator *= c_node.numerator;
    denominator *= c_node.denominator;

    return *this;
}

CalNode& CalNode::operator/=(const CalNode& c_node)
{
    numerator *= c_node.denominator;
    numerator *= c_node.numerator;

    return *this;
}



//private functions
CalNode::CalNode()
{

}

void CalNode::setTypeAsNumber()
{
    this->type_flag = NUMBER;

    return;
}

void CalNode::setTypeAsOperator()
{
    this->type_flag = OPERATOR;

    return;
}



//operators(not member functions)
CalNode operator+(CalNode& f_node , const CalNode& b_node)
{
    return (f_node += b_node);
}

CalNode operator-(CalNode& f_node , const CalNode& b_node)
{
    return (f_node -= b_node);
}

CalNode operator*(CalNode& f_node , const CalNode& b_node)
{
    return (f_node *= b_node);
}

CalNode operator/(CalNode& f_node , const CalNode& b_node)
{
    return (f_node /= b_node);
}


//operators for pointer------invalid
//CalNode* operator+(CalNode* f_np,const CalNode* b_np)
//{
//    return &((*f_np) + (*b_np));
//}
