//TP 2022/2023: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>

void RastavaBroja(int n, int& p, int& q) {
    if (n == 0) {
        p = 0;
        q = 1;
        return;
    }
    double broj=abs(n);
    p = q = 1;
    if(n<0){
        p=-1;
    }
    if(std::sqrt(broj)==std::floor(std::sqrt(broj))){
        q *=std::sqrt(broj);
        return;
    }
    int i;
    for(i=2; i<=broj; i++){
        double temp;
        temp=broj/i;
        if(((int)temp-temp==0) && (sqrt(temp)-(int)sqrt(temp)==0)){
            p *= i;
            q *= sqrt(temp);
            break;
        }
    }
}

void RastavaBroja(int n, int& p, int& q);

int main() {
    int n, p, q;
    std::cout << "Unesi broj: "<<std::endl;
    std::cin >> n;
    RastavaBroja(n, p, q);
    std::cout << n << " = ";
    std::cout <<p << "*" << q << "^2" << std::endl;
    return 0;
}