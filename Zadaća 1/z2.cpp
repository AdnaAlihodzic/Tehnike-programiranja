//TP 2022/2023: Zadaća 1, Zadatak 2
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

std::vector<std::vector<double>> UsrednjavajuciFilter(std::vector<std::vector<double>> mat, int N){
    if(N<0){
        throw std::domain_error("Neispravan red filtriranja");
    }
    std::vector<std::vector<double>> rez(mat.size());
    for(int i=0; i<mat.size(); i++){
        rez.at(i) = std::vector<double>(mat.at(i).size());
        for(int j=0; j<mat.at(i).size(); j++){
            double suma=0.0;
            int br = 0;
            int x=i-N;
            while(x<=i+N){
                int y=j-N;
                while(y<=j+N){
                    if(x>=0 && x<mat.size() && y>=0 && y<mat.at(x).size()){
                        suma += mat.at(x).at(y);
                        br++;
                    }
                    y++;
                }
                x++;
            }
            suma=suma/br;
            if(br==0){
                rez.at(i).at(j)=0;
            }
            else{
                rez.at(i).at(j)=suma;
            }
        }
    }
    return rez;
}        

int main ()
{
    try{ 
        int M, L, N;
        std:: cout<<"Unesite broj redova i kolona matrice: ";
        std::cin>>M>>L;
        std::vector<std::vector<double>> mat(M, std::vector<double>(L));
        std::cout<<"Unesite elemente matrice: ";
        for(int i=0; i<M; i++){
            for(int j=0; j<L; j++){
                std::cin>>mat.at(i).at(j);
            }
        }
        std::cout<<"Unesite red filtriranja: ";
        std::cin>>N;
    
        

        std::vector<std::vector<double>> rezultat = UsrednjavajuciFilter(mat, N);
        std::cout<<"Matrica nakon filtriranja: "<<std::endl;
        for(std::vector<double> N:rezultat){
            for(double el:N){
                std::cout<<std::right<<std::setw(7)<<std::fixed<<std::setprecision(2)<<el;
            }
            std::cout<<std::endl;
        }
    } catch(std::domain_error e){
        std::cout<<"\nGRESKA: "<<e.what()<<"!";
    }
	return 0;
}