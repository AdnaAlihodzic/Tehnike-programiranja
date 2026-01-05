//TP 2022/2023: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <functional>
#include <utility>

static double eps=1e-10;

std::function<double(double)> LagrangeovaInterpolacija(std::vector<std::pair<double,double>> v)
{
    for(int i=0; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            if(fabs(v.at(i).first-v.at(j).first) < eps ) throw std::domain_error("Neispravni cvorovi");
        }
    }
    return [v](double x) {
        double suma=0;
        int n=v.size();
        for(int i=0; i<n; i++) {
            double proizvod=1;
            for(int j=0; j<n; j++) {
                if(i!=j) {
                    proizvod=proizvod*(x - v.at(j).first)/(v.at(i).first - v.at(j).first);
                }
            }
            suma=suma+(v.at(i).second * proizvod);
        }
        return suma;
    };
}


std::function<double(double)> LagrangeovaInterpolacija(std::function<double(double)>fun, double xmin, double xmax, double dx){
    if(xmax>xmax || dx<=0){
        throw std::domain_error("Nekorektni parametri");
    } 
    std::vector<std::pair<double, double>> vektor;
    double i=xmin;
    while(i<xmax){
        std::pair<double, double> p1(i, fun(i));
        vektor.push_back(p1);
        i=i+dx;
    }
    if(std::fabs(i-xmax)<eps){
        std::pair<double, double>p1(i, fun(i));
        vektor.push_back(p1);
    }
    return LagrangeovaInterpolacija(vektor);
}

double funkcija(double x){
    double s=x*x;
    double sinus=sin (x);
    double logaritam=log (x+1);
    return s+sinus+logaritam;
}


int main ()
{
    try{
        while(true){
            int opcija;
            std::cout <<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): " ;
            std::cin >> opcija;
            if(!std::cin) {
                break;
            } 
            else if(opcija==1) {
                std::cout << "Unesite broj cvorova: ";
                int broj;
                std::cin >> broj;
                if(broj<=0) {
                    std::cout << "Broj cvorova mora biti pozitivan broj!" << std::endl;
                    break;
                }
                std::vector<std::pair<double,double>> v(broj);
                std::cout << "Unesite cvorove kao parove x y: ";
                double min=0,max=0;
                for(int i=0; i<broj; i++) {
                    std::pair<double,double> p;
                    std::cin>>p.first>>p.second;
                    v.at(i)=p;
                    if(i==0){
                        min=p.first;
                        max=p.first;
                    }
                    if(p.first<min){ 
                        min=p.first;
                    }
                    if(p.first>max){ 
                        max=p.first;
                    }
                }
                auto P=LagrangeovaInterpolacija(v);
                while(true) {
                    std::cout << "Unesite argument (ili \"kraj\" za kraj): " ;
                    double arg;
                    std::cin>>arg;
                    if(!std::cin) {
                        break;
                    } else{
                        std::cout<<"f("<<arg << ") = " <<P(arg);
                        if(arg < min || arg > max) std::cout<< " [ekstrapolacija]";
                        std::cout<<std::endl;
                    }
                }
            } else if(opcija==2) {
                std::cout << "Unesite krajeve intervala i korak: ";
                double pocetak,kraj,korak;
                std::cin>>pocetak>>kraj>>korak;
                auto Q = LagrangeovaInterpolacija(funkcija,pocetak,kraj,korak);
                while(true){
                    std::cout<< "Unesite argument (ili \"kraj\" za kraj): " ;
                    double argument;
                    std::cin>>argument;
                    if(!std::cin){
                        break;
                    } else{
                        std::cout <<"f("<<argument << ") = " << funkcija(argument) << " P("<<argument << ") = "<< Q(argument);
                        if(argument<pocetak || argument>kraj) { 
                        std::cout<< " [ekstrapolacija]";
                        }
                        std::cout<<std::endl;
                    }
                }
            } else{
                std::cout<< "Nepoznat slucaj!" << std::endl;
                break;
            }
            if(!std::cin) {
                break;
            }
        }
    } catch(std::domain_error e) {
        std::cout<<"IZUZETAK: "<< e.what() << "!" << std::endl;
    }
    return 0;
}
