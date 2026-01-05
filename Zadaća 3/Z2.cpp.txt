//TP 2022/2023: Zadaća 3, Zadatak 2
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <cctype>

void malaslova(std::string& s){
    for(auto& c : s){
        c=std::tolower(c);
    }
}

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string,int,int>>> Rez;
typedef std::set<std::tuple<std::string,int,int>> Clan;

std::map<std::string, std::set<std::tuple<std::string, int, int>>> KreirajIndeksPojmova(Knjiga k){
    std::map<std::string, std::set<std::tuple<std::string, int, int>>> rez;
    for(auto it=k.begin(); it!=k.end(); it++){
        std::string dokument=it->first;
        for(int i=0; i<it->second.size(); i++){
            std::string s=it->second.at(i);
            std::string rijec;
            for(int j=0; j<s.length(); j++){
                while(j<s.length() && (!isalpha(s.at(j)) && !isdigit(s.at(j)))){ 
                    j++;
                }
                int start=j;
                while(j<s.length() && (isalpha(s.at(j)) || isdigit(s.at(j)))){ 
                    j++;
                }
                rijec=s.substr(start, j-start);
                malaslova(rijec);
                if(!rez.count(rijec)){
                    std::set<std::tuple<std::string, int, int>> skup;
                    std::tuple<std::string, int, int> tup={dokument, i+1, start};
                    skup.insert(tup);
                    rez.insert({rijec, skup});
                }else{
                    std::tuple<std::string, int, int> tup={dokument, i + 1, start};
                    auto itr=rez.find(rijec);
                    itr->second.insert(tup);
                }
            }
        }
    }
    return rez;
}


std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(const std::string& s, const Rez& index){
    auto it=index.find(s);
    if(it==index.end()){
        throw std::logic_error("Pojam nije nadjen");
    }
    return it->second;
}

void IspisiIndeksPojmova(std::map<std::string, std::set<std::tuple<std::string,int,int>>> a){
    for(auto it=a.begin(); it!=a.end(); it++){
        auto pom=it->second;
        std::cout<<it->first<< ": ";
        for(auto it2=pom.begin(); it2!=pom.end(); it2++){
            if(it2!=pom.begin()) std::cout << ", ";
            std::cout << std::get<0>(*it2) << "/" << std::get<1>(*it2) << "/" << std::get<2>(*it2);
        }
        std::cout << std::endl;
    }
}

void IspisiSkupa(const std::set<std::tuple<std::string, int, int>>& skup){
    for(const auto& elem:skup){
        std::cout<<std::get<0>(elem)<<"/"<<std::get<1>(elem)<<"/"<< std::get<2>(elem)<<" ";
    }
    std::cout<<std::endl;
}

int main ()
{
    std::map<std::string, std::vector<std::string>> mapa;
    while(true){
    std::cout<<"\nUnesite naziv poglavlja: ";
    std::string poglavlje;
    std::getline(std::cin, poglavlje);
    if(poglavlje == ".")break;
    std::vector<std::string> vek;
    int i = 0;
    while(true){
        std::cout<< "\nUnesite sadrzaj stranice " <<i+1<<": ";
        std::string str;
        std::getline(std::cin, str);
        if(str=="."){ 
            break;
        }
        vek.push_back(str);
        i++;
    }
    mapa.insert({poglavlje, vek});
}
std::cout<<std::endl;
std::cout<<"Kreirani indeks pojmova: ";
auto index_poglavlja=KreirajIndeksPojmova(mapa);
std::cout<<std::endl;
IspisiIndeksPojmova(index_poglavlja);

while(true){
    std::cout << "Unesite rijec:"<<std::endl;
    std::string rijec;
    std::getline(std::cin, rijec);
    if(rijec=="."){ 
        break;
    }
    try{
        auto a=PretraziIndeksPojmova(rijec, index_poglavlja);
        IspisiSkupa(a);
    } catch(std::logic_error& e){
        std::cout<<"Unesena rijec nije nadjena!"<<std::endl;
    }
}
return 0;
}

