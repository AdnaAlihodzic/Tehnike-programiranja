//TP 2022/2023: Zadaća 1, Zadatak 4
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

std::string pretvori_u_Velika(std::string sl){
    for(auto& slova: sl){
        slova = ::toupper(slova);
    }
    return sl;
}

std::string Cenzura(std::string rec, std::vector<std::string> banned) {
    for(auto slova: banned){
        for(auto z:slova){
            if(!isalnum(z)){
                throw std::logic_error("Neispravna riječ");
            }
        }
    }

    for(int i=0; i<rec.length(); i++){
        std::string rijec="";
        if(isalnum(rec.at(i)) && (i==0 || !isalnum(rec.at(i-1)))){
            int j=i;
            while(j<rec.length() && isalnum(rec.at(j))){
                rijec.push_back(rec.at(j));
                j++;
            }
            for(auto zr:banned){
                if(pretvori_u_Velika(zr)==pretvori_u_Velika(rijec)){
                    for(int k=i; k<j; k++){
                        rec.at(k)='*';
                    }
                }
            }
        }
    }
    return rec;
}


int main ()
{
    std::string rec;
    std::cout<< "Unesite recenicu: " <<std::endl;
    std::getline(std::cin, rec);
    std::vector<std::string>z_rijeci;
    std::cout<< "Unesite zabranjene rijeci (. za kraj): " <<std::endl;
    do{
        std::string unos;
        std::cin>>unos;
        if(unos=="."){
            break;
        }
        z_rijeci.push_back(unos);
    }while(true);

    bool check(true);
    for(auto slova:z_rijeci){
        for(auto z: slova){
            if(!isalnum(z)){
                check=false;
            }
        }
    }

    if(check){
        std::string cenzurisana_recenica = Cenzura(rec, z_rijeci);
        std::cout<<"Cenzurisana recenica: "<<cenzurisana_recenica<<std::endl;
    }
    else{
        std::cout<<"GRESKA: Nelegalne zabranjene rijeci!"<<std::endl;
    }
	return 0;
}
