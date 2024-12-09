#include <iostream>

class rationnal{
    private:
    int num;  // Numérateur
    int den;  // Dénominateur
    
    public:
    rationnal(int a, int b){
        num=a;
        den=b;
    }
    
    void print(){
        std::cout<<num<<'/'<<den<<std::endl;
    }

};

int main(){
    rationnal r1(1,2);
    rationnal r2(3,4);
    r1.print();
    r2.print();
    return 0;
}