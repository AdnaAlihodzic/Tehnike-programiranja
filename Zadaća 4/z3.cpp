//TP 2022/2023: ===TITLE===
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>

class ApstraktnoVozilo{
    private:
    int tezina;
    public:
    ApstraktnoVozilo(int tezina):tezina(tezina){}
    int DajTezinu() const { 
        return tezina;
    }
    virtual ~ApstraktnoVozilo(){}
    virtual int DajUkupnuTezinu() const=0;
    virtual ApstraktnoVozilo* DajKopiju() const=0;
    virtual void IspisiPodatke() const=0;
};


class Automobil: public ApstraktnoVozilo{
    private:
    std::vector<int> t_putnika;
    public:
    Automobil(int tezina, std::vector<int> tezine_p):ApstraktnoVozilo(tezina), t_putnika(tezine_p){}
    ~Automobil(){}
    Automobil(int tezina, std::initializer_list<int> elem): ApstraktnoVozilo(tezina){
        for(const auto& putnik:elem){
            t_putnika.push_back(putnik);
        }
    }
    int DajUkupnuTezinu() const override{
        int ukupna_t=DajTezinu();
        std::for_each(std::begin(t_putnika), std::end(t_putnika), [&ukupna_t](int x){
            ukupna_t=ukupna_t+x; 
        });
        return ukupna_t;
    }
    ApstraktnoVozilo *DajKopiju() const override{
        return new Automobil(*this);
    }
    void IspisiPodatke() const override{
        std::cout << "Vrsta vozila: Automobil"<<std::endl;
        std::cout<<"Vlastita tezina: "<< DajTezinu() << " kg"<<std::endl;
        std::cout<<"Tezine putnika: ";
        std::cout <<t_putnika.at(0) <<" kg" << std::endl;
        for(int i=1; i<t_putnika.size();i++){
            std::cout << ", "<< t_putnika.at(i) <<" kg";
        }
        std::cout << "\nUkupna tezina: " << DajUkupnuTezinu() <<" kg"<< std::endl;
    }
};


class Kamion: public ApstraktnoVozilo{
    private:
    int tezina_tereta;
    public:
    Kamion(int tezina, int tezina_tereta): ApstraktnoVozilo(tezina), tezina_tereta(tezina_tereta){}
    ~Kamion(){}
    int DajUkupnuTezinu() const override {
        return tezina_tereta+DajTezinu();
    }
    ApstraktnoVozilo *DajKopiju() const override{
        return new Kamion(*this);
    }
    
    void IspisiPodatke() const override{
        std::cout << "Vrsta vozila: Kamion" <<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu() << " kg"<<std::endl;
        std::cout<<"Tezina tereta: " << tezina_tereta << " kg"<<std::endl;
        std::cout<<"Ukupna tezina: " <<DajUkupnuTezinu() << " kg"<< std::endl;
    }
};

class Autobus: public ApstraktnoVozilo{
    private:
    int broj_p;
    int srednja_v;
    public:
    Autobus(int tezina, int broj_putnika, int srednja_tezina):ApstraktnoVozilo(tezina), broj_p(broj_putnika), srednja_v(srednja_tezina){};
    int DajUkupnuTezinu() const override{
        return (broj_p*srednja_v)+DajTezinu();
    }
    ApstraktnoVozilo *DajKopiju() const override{
        return new Autobus(*this);
    }
    void IspisiPodatke() const override{
        std::cout << "Vrsta vozila: Autobus"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu() << " kg"<<std::endl;
        std::cout<<"Broj putnika: " << broj_p<<std::endl;
        std::cout<<"Prosjecna tezina putnika: "<< srednja_v <<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: " <<DajUkupnuTezinu() << " kg"<< std::endl;
    } 
};


class Vozilo{
    private:
    ApstraktnoVozilo *vozilo = nullptr;
    public:
    Vozilo(){}
    ~Vozilo(){
        delete vozilo;
    }
    Vozilo(const ApstraktnoVozilo &x):vozilo(x.DajKopiju()){}
    Vozilo(const Vozilo &x){
        vozilo=x.vozilo->DajKopiju();
    }
    Vozilo(Vozilo &&x){
        vozilo=x.vozilo;
        x.vozilo=nullptr;
    }
    Vozilo &operator=(const Vozilo &x){
        if(this!=&x){
            delete vozilo;
            if(x.vozilo){
                vozilo=x.vozilo->DajKopiju();
            }
            else{
                vozilo=nullptr;
            }
        }
        return *this;
    }
    Vozilo &operator=(Vozilo &&x){
        std::swap(vozilo, x.vozilo);
        return *this;
    }
    int DajTezinu() const{
        return vozilo->DajTezinu();
    }
    int DajUkupnuTezinu() const{
        return vozilo->DajUkupnuTezinu();
    }
    void IspisiPodatke() const{
        vozilo->IspisiPodatke();
    }
};

int main ()
{
    std::vector<Vozilo> vektor;
    std::ifstream file("VOZILA.TXT");
    if(!file){ 
        throw std::logic_error("Datoteka ne postoji");
    }
    for(;;){
        if(file.peek()=='A'){
            file.ignore(1, '\n');
            int tezina_1;
            int broj;
            file>>tezina_1>>broj;
            std::vector<int> v_tez;
            for(int i=0; i<broj; i++){
                int broj_1;
                file>>broj_1;
                v_tez.push_back(broj_1);
            }
            Automobil automobil(tezina_1, v_tez);
            vektor.push_back(automobil);
        }
        else if(file.peek()=='K'){
            file.ignore(1, '\n');
            int tezina_2;
            int masa;
            file>>tezina_2>>masa;
            Kamion kamion(tezina_2, masa);
            vektor.push_back(kamion);
        }
        else if(file.peek()=='B'){
            file.ignore(1, '\n');
            int tezina_3;
            int broj;
            int sr;
            file>>tezina_3>>broj>>sr;
            Autobus autobus(tezina_3, broj, sr);
            vektor.push_back(autobus);
        }
        else if(!file.eof() && !file){
            throw std::logic_error("Datoteka sadrzi besmislene podatake");
        }
        if(file.eof()){
            break;
        }
        file.ignore(1, '\n');
        file.clear();
    }

    std::sort(std::begin(vektor), std::end(vektor), [](Vozilo x, Vozilo y){
       return x.DajUkupnuTezinu()<y.DajUkupnuTezinu();
    });
    
    std::for_each(std::begin(vektor), std::end(vektor), [](Vozilo vozilo){
        std::cout<<vozilo.DajUkupnuTezinu()<<std::endl;
    });
	return 0;
}