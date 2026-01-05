//TP 2022/2023: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

class Padavine{
    private:
    int max_pad;
    std::vector<int> registrirane_pad;
    bool Provjera(){
        int v=std::count_if(std::begin(registrirane_pad), std::end(registrirane_pad), std::bind(std::less<int>(), std::placeholders::_1,0));
        if(max_pad<0 || v>0){ 
            return false;
        }
        return true;
    }
    public:
    Padavine(int max_kolicina){
        if(max_kolicina<=0){
            throw std::range_error("Ilegalna maksimalna kolicina");
        }
        max_pad=max_kolicina;
    }
    void RegistrirajPadavine(int k){
        if(k<0 || k>max_pad){ 
            throw std::range_error("Ilegalna kolicina padavina");
        }
        registrirane_pad.push_back(k);
    }
    int DajBrojRegistriranihPadavina() const{
        return registrirane_pad.size();
    }
    void BrisiSve(){
        registrirane_pad.clear();
    }
    int DajMinimalnuKolicinuPadavina()const{
        if(registrirane_pad.size()!=0) {
            return *(std::min(std::begin(registrirane_pad),std::end(registrirane_pad)));
        } 
        else{ 
            throw std::range_error("Nema registriranih padavina");
        }
    }
    int DajMaksimalnuKolicinuPadavina()const{
        if(registrirane_pad.size()!=0) {
            return *(std::max(std::begin(registrirane_pad),std::end(registrirane_pad)));
        } else{ 
            throw std::range_error("Nema registriranih padavina");
        }
    }
    int DajBrojDanaSaPadavinamaVecimOd(int a) const{
        if(registrirane_pad.empty()){
            throw std::range_error("Nema registriranih padavina");
        }
        return std::count_if(registrirane_pad.begin(), registrirane_pad.end(), std::bind(std::greater<int>(), std::placeholders::_1, a));
    }
    void Ispisi() const;
    int operator[](int indeks) const{
        if(indeks>=1 && indeks<=registrirane_pad.size()){
            return registrirane_pad[indeks-1];
        }
        else{
            throw std::range_error("Neispravan indeks");
        }
    }
    friend Padavine &operator ++(Padavine &padavine);
    friend Padavine operator ++(Padavine &padavine, int);
    friend Padavine operator +(const Padavine &padavine, int x);
    friend Padavine operator +(int x, const Padavine &padavine);
    friend Padavine operator -(const Padavine &pad_X, const Padavine &pad_Y);
    friend Padavine operator -(const Padavine &padavine);
    friend Padavine operator -(const Padavine &padavine, int x);
    friend Padavine operator -(int x,const Padavine &padavine);
    friend Padavine &operator +=(Padavine &padavine, int x){
        padavine = padavine+x;
        return padavine;
    }
    friend Padavine &operator -=(Padavine &padavine, int x){
        padavine = padavine-x;
        return padavine;
    }
    friend Padavine &operator -=(Padavine &pad_X, Padavine &pad_Y){
        pad_X = pad_X-pad_Y;
        return pad_X;
    }
    friend bool operator == (const Padavine &pad_X, const Padavine &pad_Y);
    friend bool operator !=(const Padavine &pad_X, const Padavine &pad_Y);
};

void Padavine::Ispisi() const{
    std::vector<int> ispis(registrirane_pad);
    std::sort(ispis.rbegin(), ispis.rend());
    for(const auto& pad:ispis){
        std::cout<<pad<<std::endl;
    }
}

Padavine &operator ++(Padavine &padavine){
    std::transform(std::begin(padavine.registrirane_pad), std::end(padavine.registrirane_pad), std::begin(padavine.registrirane_pad), std::bind(std::plus<int>(), std::placeholders::_1, 1));
    padavine.max_pad=padavine.max_pad+1;
    return padavine;
}
Padavine operator ++(Padavine &padavine, int){
    Padavine rezultat=padavine;
    ++padavine;
    return rezultat;
}
Padavine operator +(const Padavine &padavine, int x){   
    int elem=padavine.max_pad+x;
    Padavine priv(elem);
    priv.registrirane_pad.resize(padavine.registrirane_pad.size());
    std::transform(std::begin(padavine.registrirane_pad), std::end(padavine.registrirane_pad), std::begin(priv.registrirane_pad), std::bind(std::plus<int>(), std::placeholders::_1, x));
    if(priv.Provjera()){ 
        return priv;
    }
    else{
        throw std::domain_error("Nekorektan rezultat operacije");
    }
}
Padavine operator +(int x, const Padavine &padavine){
    Padavine priv=padavine+x;
    if(priv.Provjera()){
        return priv;
    }
    else{
        throw std::domain_error("Nekorektan rezultat operacije");
    }
}
Padavine operator -(const Padavine &padavine, int x){
    int elem=padavine.max_pad-x;
    Padavine priv(elem);
    priv.registrirane_pad.resize(padavine.registrirane_pad.size());
    std::transform(std::begin(padavine.registrirane_pad), std::end(padavine.registrirane_pad), std::begin(priv.registrirane_pad), std::bind(std::minus<int>(), std::placeholders::_1, x));
    if(priv.Provjera()){
        return priv;
    }
    else{
        throw std::domain_error("Nekorektan rezultat operacije");
    }
}
Padavine operator -(int x, const Padavine &padavine){
    Padavine priv(x);
    priv.registrirane_pad.resize(padavine.registrirane_pad.size());
    std::transform(std::begin(padavine.registrirane_pad), std::end(padavine.registrirane_pad), std::begin(priv.registrirane_pad), std::bind(std::minus<int>(), x, std::placeholders::_1));
    if(priv.Provjera()){
        return priv;
    }
    else{
        throw std::domain_error("Nekorektan rezultat operacije");
    }
}
Padavine operator -(const Padavine &pad_X, const Padavine &pad_Y){
    if(pad_X.registrirane_pad.size()==pad_Y.registrirane_pad.size()) {
        Padavine priv(pad_X.max_pad);
        priv.registrirane_pad.resize(pad_X.registrirane_pad.size());
        std::transform(std::begin(pad_X.registrirane_pad), std::end(pad_X.registrirane_pad), std::begin(pad_Y.registrirane_pad), std::begin(priv.registrirane_pad), std::bind(std::minus<int>(), std::placeholders::_1, std::placeholders::_2));
        if(priv.Provjera()){
            return priv;
        }
        else{
            throw std::domain_error("Nekorektan rezultat operacije");
        }
    } 
    else{
        throw std::domain_error("Nesaglasni operandi");
    }
}
Padavine operator -(const Padavine &padavine){
    Padavine priv(padavine.max_pad);
    priv.registrirane_pad.resize(padavine.registrirane_pad.size());
    std::transform(std::begin(padavine.registrirane_pad), std::end(padavine.registrirane_pad), std::begin(priv.registrirane_pad), std::bind(std::minus<int>(), padavine.max_pad, std::placeholders::_1));
    return priv;
}
bool operator ==(const Padavine &pad_X, const Padavine &pad_Y){
    if(pad_X.registrirane_pad.size()==pad_Y.registrirane_pad.size()) {
        return std::equal(std::begin(pad_X.registrirane_pad), std::end(pad_X.registrirane_pad), std::begin(pad_Y.registrirane_pad), std::bind(std::equal_to<int>(), std::placeholders::_1, std::placeholders::_2));
    } 
    else{
        return false;
    }
}
bool operator !=(const Padavine &pad_X, const Padavine &pad_Y){
    return !(pad_X==pad_Y);
}
int main (){
    Padavine first(10);
    Padavine second(5);
    for(int i=0; i<4; i++){
        first.RegistrirajPadavine(i*4+5-i);
        second.RegistrirajPadavine(i+4);
    }
    first.Ispisi();
    std::cout<<std::endl;
    second.Ispisi();
    Padavine mix(first);
    mix+=5;
    mix.Ispisi();
    second++;
    second.Ispisi();
    mix=mix-second;
    mix.Ispisi();
    Padavine razlika=first-mix;
    razlika.Ispisi();
    std::cout<<"Maksimalna od druge: "<<second.DajMaksimalnuKolicinuPadavina()<<std::endl;
    std::cout<<"Minimalna od druge: "<<second.DajMinimalnuKolicinuPadavina()<<std::endl;
    std::cout<<"Broj dana sa padavinama vecim od 5: "<<razlika.DajBrojDanaSaPadavinamaVecimOd(5)<<"dana"<<std::endl;
    std::cout<<"Broj registriranih u prvoj: "<<first.DajBrojRegistriranihPadavina()<<std::endl;
    first.BrisiSve();
    second.BrisiSve();
	return 0;
}
