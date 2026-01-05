//TP 2022/2023: ===TITLE===
#include <iostream>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <vector>

template <typename Tip> 
class DatotecniKontejner{
    std::fstream tok;
    public:
    DatotecniKontejner(const std::string &ime){
        tok.open(ime, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
    }
    void DodajNoviElement(const Tip &element){
        std::streampos trenutna_pozicija=tok.tellp();
        tok.seekp(0, std::ios::end);
        tok.write(reinterpret_cast<const char *>(&element), sizeof(Tip));
        if(tok.fail()){
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        }
        tok.seekp(trenutna_pozicija);
    }
    int DajBrojElemenata(){
        tok.seekg(0, std::ios::end);
        if(tok.fail()){
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        }
        return tok.tellg()/sizeof(Tip);
    }
    Tip DajElement(int pozicija){
        int velicina=DajBrojElemenata();
        if(pozicija<0 || pozicija>=velicina){
            throw std::range_error("Neispravna pozicija");
        }
        tok.seekg(pozicija*sizeof(Tip));
        if(tok.fail()){
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        }
        Tip element;
        tok.read(reinterpret_cast<char *>(&element), sizeof(Tip));
        if(tok.fail()){
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        }
        return element;
    }
    void IzmijeniElement(int pozicija, const Tip &element){
        int vel=DajBrojElemenata();
        if(pozicija<0 || pozicija>=vel){
            throw std::range_error("Neispravna pozicija");
        }
        std::fstream tempTok("temp.bin", std::ios::binary | std::ios::out);
        if(!tempTok.is_open()){
            throw std::logic_error("Problemi prilikom pristupa datoteci");
        }
        for(int i=0; i<vel; i++){
            auto pomocna=DajElement(i);
            if(i==pozicija){
                pomocna=element;
            }
            tempTok.write(reinterpret_cast<const char *>(&pomocna), sizeof(Tip));
            if(tempTok.fail()){
                tempTok.close();
                throw std::logic_error("Problemi prilikom pristupa datoteci");
            }
        }
        tempTok.close();
        tok.close();
        std::remove("test.bin");
        std::rename("temp.bin", "test.bin");
        tok.open("test.bin", std::ios::binary | std::ios::in | std::ios::out);
        if(!tok.is_open()){
            throw std::logic_error("Problemi prilikom otvaranja datoteke");
        }
    }
    void Sortiraj(std::function<bool(const Tip &, const Tip &)>kriterij=std::less<Tip>()){
        int vel=DajBrojElemenata();
        for(int i=0; i<vel-1; i++){
            for(int j=0; j<vel-i-1; j++){
                auto element_1=DajElement(j);
                auto element_2=DajElement(j+1);
                if(kriterij(element_2, element_1)){
                    IzmijeniElement(j, element_2);
                    IzmijeniElement(j+1, element_1);
                }
            }
        }
    }
};

int main() {
    try{
        DatotecniKontejner<int> dki("test.bin");
        dki.DodajNoviElement(2);
        dki.DodajNoviElement(5);
        std::cout<<"Broj elemenata: "<<dki.DajBrojElemenata()<<std::endl;
        for(int i=0; i<dki.DajBrojElemenata(); i++){
            std::cout<<"Element na poziciji "<<i<<": "<<dki.DajElement(i)<<std::endl;
        }
        dki.IzmijeniElement(2,3);
        for(int i=0; i<dki.DajBrojElemenata(); i++){
            std::cout<<"Element na poziciji "<<i<<": "<<dki.DajElement(i)<<std::endl;
        }
        dki.Sortiraj([](int x, int y){
            return x>y;
        });
        for(int i=0; i<dki.DajBrojElemenata(); i++){
            std::cout<<"Element na poziciji"<<i<<": "<<dki.DajElement(i)<<std::endl;
        }
    }catch(const std::exception& e){
        std::cerr<<"Izuzetak: "<<e.what()<<std::endl;
    }
    return 0;
}
