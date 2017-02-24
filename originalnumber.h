#ifndef ORIGINALNUMBER_H
#define ORIGINALNUMBER_H


class OriginalNumber
{
public:
    OriginalNumber();
    ~OriginalNumber();

    void generateNewNumbers();
    int getNum_1();
    int getNum_2();
    int getNum_3();
    int getNum_4();

private:
    int num_quantity;
    int num_1;
    int num_2;
    int num_3;
    int num_4;

    int generateRandomLine();
    void getNumbers(int);
    void initialRandomFunction();
    void initialRandomBase();
};

#endif // ORIGINALNUMBER_H
