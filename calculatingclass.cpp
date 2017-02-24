#include "calculatingclass.h"

#include "calnode.h"
#include "calculateexpressionalgorithm.h"
#include "calculateexpressionbyconvertingtosuffix.h"

#include <QDebug>

CalculatingClass::CalculatingClass()
{
    cal_alg = new CalculateExpressionByConvertingToSuffix();
}

CalculatingClass::~CalculatingClass()
{
    clearClass();
    delete cal_alg;
}


//public functions
void CalculatingClass::setNodesValue(QString formula_c)
{
    //Is the node value of QString a char?
//    foreach(QChar t_c,formula_s){
//        setNodeValue((char)(t_c.unicode()));
//    }

    if(formula_c.length() == 1){
        setNodeValue((char)(formula_c.at(0).unicode()));
    }
    else{
        setNodeValue(formula_c.toInt());
    }

    //testContainerAsDebug();
}

void CalculatingClass::clearClass()
{
//    foreach (CalNode *tn, nodes_vector) {
//        delete tn;
//    }


    qDeleteAll(nodes_vector);
    nodes_vector.clear();
    suf_list.clear();

    return;
}

bool CalculatingClass::isValid()
{
    //test block
    //testContainerAsDebug();

    qDebug() << "value: " << cal_alg->calculateExpression(nodes_vector) << endl;


    return true;
}

int CalculatingClass::calculateWithPostfixAlgorithm()
{
    return cal_alg->calculateExpression(nodes_vector);

}

int CalculatingClass::calculateWithAnalyzingTreeAlgorithm()
{
    return 0;
}


QStringList& CalculatingClass::getSuffixExpression()
{
    QString t_exp;
    t_exp = cal_alg->getConvertedExpression();

    suf_list = t_exp.split(",");
    suf_list.pop_back();

//    foreach(QString ts,suf_list){
//        qDebug() << ts;
//    }

    return suf_list;
}


//private functions
void CalculatingClass::setNodeValue(char input_c)
{
    nodes_vector.push_back(new CalNode(input_c));

    return;
}

void CalculatingClass::setNodeValue(int input_v)
{
    nodes_vector.push_back(new CalNode(input_v));

    return;
}

void CalculatingClass::testContainerAsDebug()
{
    foreach (CalNode* t_n , nodes_vector) {
        if(t_n->isNumber()){
            qDebug() << "Type: Number ; " << "Numerator: " << t_n->numerator << "Denominator: " << t_n->denominator << endl;
        }
        else{
            qDebug() << "Type: Opreator ; " << t_n->c_operator << endl;
        }
    }

    return;
}
