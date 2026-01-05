//TP 2022/2023: Zadaća 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>

std::vector<std::vector<int>> KreirajSpiralnuMatricu(int red, int kol, int k, bool o){
    if(red<=0 || kol<=0){
        return std::vector<std::vector<int>>();
    }
    std::vector<std::vector<int>>matrica(red, std::vector<int>(kol));
    int i=0, br=k, pom1, pom2;
    if(o){
        pom1 = kol;
        pom2 = red;
    }else{
        pom1=red;
        pom2=kol;
    }
    
    while(1==1){
        for(int x=i; x<pom1-i; x++){
            o ? matrica.at(i).at(x)=k++ : matrica.at(x).at(i)=k++;
            if(k==br+red*kol){
                return matrica;
            }
        }
        for(int x=i+1; x<pom2-i; x++){
            o ? matrica.at(x).at(kol-i-1)=k++ : matrica.at(red-i-1).at(x)=k++;
            if(k==br+red*kol){
                return matrica;
            }
        }
        for(int x=pom1-i-2; x>=i; x--){
            o ? matrica.at(red-i-1).at(x)=k++ : matrica.at(x).at(kol-i-1)=k++;
            if(k==br+red*kol){
                return matrica;
            }
        }
        for(int x=pom2-i-2; x>=i+1; x--){
            o ? matrica.at(x).at(i)=k++ : matrica.at(i).at(x)=k++;
            if(k==br+red*kol){
                return matrica;
            }
            i++;
        }
    }
}

bool DaLiJeSpiralnaMatrica(std::vector<std::vector<int>> mat){
    int n=mat.size()*(mat.at(0).size());
    int prvi = mat.at(0).at(0);
    long int suma1=0;
    for(auto red:mat){
        for(auto broj:red){
            suma1 = suma1 + broj;
        }
    }
    long int suma2=n*0.5*(2*prvi+(n-1));
    return suma2==suma1;
}

int NajvecaSirina(std::vector<std::vector<int>> m){
    int max(0), br(0), i, j;
    for(i=0; i<m.size(); i++){
        for(j=0; j<m.at(i).size(); j++){
            br=0;
            if(m.at(i).at(j)<0){
                br++;
            }
            int x = std::abs(m.at(i).at(j));
            while(x!=0){
                x= x/10;
                br++;
            }
            if(max<br){
                max=br;
            }
        } 
    }
    return max+1;
}

int main ()
{
    int redovi, kolone;
    std::cout<<"Unesite broj redova i kolona matrice: ";
    std::cin>>redovi>>kolone;
    int poc;
    std::cout<<"Unesite pocetnu vrijednost: ";
    std::cin>>poc;
    char spiralna;
    std::cout<<"Unesite L za lijevu, a D za desnu spiralnu matricu: "<<std::endl;
    std::cin>>spiralna;
    int o=spiralna=='D';
    std::vector<std::vector<int>> m = KreirajSpiralnuMatricu(redovi, kolone, poc, o);
    std::cout<<"Kreirana spiralna matrica: "<<std::endl;
    for(std::vector<int> temp : m){
        for(int w : temp){
            std::cout<<std::right<<std::setw(NajvecaSirina(m))<<w;
        }
        std::cout<<'\n';
    }
	return 0;
}
