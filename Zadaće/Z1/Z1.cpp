//TP 2022/2023: Zadaća 1, Zadatak 1
#include <iostream>
#include <vector>
#include <stdexcept>
#include <array>
#include <cmath>


int MultiplikativniDigitalniKorijen(long long int broj, int baza) {
    if (baza<2) {
        throw std::domain_error("Neispravna baza");
    }
    else if(broj<0) {
        broj *= -1;
    }
    else if(broj==0){
        return 0;
    }
    else{
        long long int rez=1;
        while(broj>0){
            rez *=broj%baza;
            broj /=baza;
        }
        if(rez>=baza){
            return MultiplikativniDigitalniKorijen(rez, baza); 
        }
        return rez;
}
}

enum class TretmanNegativnih{IgnorirajZnak, Odbaci, PrijaviGresku};


std::array<std::vector<long long int>, 10> RazvrstajBrojeve(std::vector<long long int> brojevi, enum TretmanNegativnih t) {
    std::array<std::vector<long long int>, 10>mat;
    for (long long int broj : brojevi) {
        if(broj<0){
            switch(t){
                case TretmanNegativnih::Odbaci:
                    continue;
                case TretmanNegativnih::IgnorirajZnak:
                    broj=std::fabs(broj);
                    break;
                case TretmanNegativnih::PrijaviGresku:
                    throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
            }
        }
        mat.at(MultiplikativniDigitalniKorijen(broj, 10))
                .push_back(broj);
    }
    return mat;
}

int main() {
    std::vector<long long int> brojevi;
    bool negativni(false);
    std::cout<<"Unesite brojeve (bilo koji ne-broj oznacava kraj): "<<std::endl;
    while(1){
        long long int br;
        std::cin>>br;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
        if(br<0){
            negativni=true;
        }
        brojevi.push_back(br);
    }
    if(negativni){
        std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!";
    }
    else{
        std::array<std::vector<long long int>,10>mat=RazvrstajBrojeve(brojevi, TretmanNegativnih::IgnorirajZnak);
        std::cout<<"Rezultati razvrstavanja po multiplikativnom digitalnom korijenu: "<<std::endl;
        for(int i=0; i<mat.size(); i++){
            if(mat.at(i).size()>0){
                std::cout<<i<<": ";
                for(auto broj: mat.at(i)){
                    std::cout<<broj<<" ";
                }
                std::cout<<std::endl;
            }
        }
    }
    return 0;
}

