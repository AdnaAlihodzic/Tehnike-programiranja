//TP 2022/2023: Zadaća 3, Zadatak 4
#include <iostream>
#include <list>
#include <vector>

int Poglavica(int N, int M, bool ispis=false) {
    std::list<int> plemenskiKrug;
    if(M==0){
        return 0;
    }
    for (int i=1; i<=N; i++) {
        plemenskiKrug.push_back(i);
    }
    auto it=plemenskiKrug.begin();
    while (plemenskiKrug.size() > 1) {
        for (int i=0; i < M-1; i++) {
            ++it;
            if (it==plemenskiKrug.end()) {
                it=plemenskiKrug.begin();
            }
        }
        if(ispis){
            std::cout<<*it<< ", ";
        }
        it=plemenskiKrug.erase(it);
        if(it==plemenskiKrug.end()) {
            it=plemenskiKrug.begin();
        }
    }
    if(ispis){
        std::cout << std::endl;
    }
    return plemenskiKrug.front();
}

int SigurnoMjesto(int M, int N1, int N2) {
    for (int N = N1; N <= N2; N++) {
        int poglavica=Poglavica(N, M);
        if (poglavica==1) {
            return N+1;
        }
    }
    return 0;
}


int main() {
    int N,M,N1,N2;
    std::cout<< "Unesi broj punoljetnih clanova (N): ";
    std::cin>>N;
    std::cout<<"Unesi korak razbrajanja (M): ";
    std::cin>> M;
    std::cout<< "Unesi raspon (N1-N2): ";
    std::cin>>N1>>N2;
    int poglavica=Poglavica(N,M);
    std::cout << "Redni broj osobe koja postaje poglavica: " << poglavica;
    int sigurno_mjesto=SigurnoMjesto(M,N1,N2);
    std::cout << " Sigurno mjesto: " <<sigurno_mjesto;
    return 0;
}