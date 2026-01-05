//TP 2022/2023: ===TITLE===
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <cstring>
#include <new>
#include <fstream>

template <typename T>
class Matrica{
    int broj_redova, broj_kolona;
    T **elem;
    char ime_mat;
    static T **AlocirajMemoriju(int broj_redova, int broj_kolona);
    static void DealocirajMemoriju(T **elem, int broj_redova);
    void KopirajElemente(T **elem);
    public:
    Matrica(int broj_redova, int broj_kolona, char ime = 0);
    Matrica(const Matrica &m);
    Matrica(Matrica &&m);
    Matrica(const char ime[], bool dat);
    ~Matrica(){
        DealocirajMemoriju(elem, broj_redova);
    }
    Matrica &operator =(const Matrica &m);
    Matrica &operator =(Matrica &&m);
    T *&operator [](const int &indeks) const{
        return elem[indeks];
    }
    T &operator ()(const int &x,const int &y) const{
        if(x<1 || x>broj_redova || y<1 || y>broj_kolona){
            throw std::range_error("Neispravan indeks");
        }
        return elem[x-1][y-1];
    }
    template <typename T2>
    friend std::istream& operator >>(std::istream &tok, Matrica<T2> &m);
    template <typename T2>
    friend std::ostream& operator <<(std::ostream &tok, const Matrica<T2> &m);
    template <typename T2>
    friend Matrica<T2> operator +(const Matrica<T2> &m1, const Matrica<T2> &m2);
    template <typename T2>
    friend Matrica<T2> operator *(const Matrica<T2> &a, const Matrica<T2> &b);
    template <typename T2>
    friend Matrica<T2> operator -(const Matrica<T2> &a, const Matrica<T2> &b);
    template <typename T2, typename T3>
    friend Matrica<T2> operator *(T3 broj, const Matrica<T2> &b);
    template <typename T2, typename T3>
    friend Matrica<T2> operator *( const Matrica<T2> &b, T3 broj);
    template <typename T2>
    friend Matrica<T2> operator +=(Matrica<T2> &a, const Matrica<T2> &b);
    template <typename T2>
    friend Matrica<T2> operator -=(Matrica<T2> &a, const Matrica<T2> &b);
    template <typename T2>
    friend Matrica<T2> operator *=(Matrica<T2> &a, const Matrica<T2> &b);
    template <typename T2,typename T3>
    friend Matrica<T> operator *=(Matrica<T3> &a, T3 broj);
    operator std::string() const{
        std::stringstream ss;
        ss<<"{";
        for(int i=0; i<broj_redova; i++){
            ss<<"{";
            for(int j=0; j<broj_kolona; j++){
                ss<<static_cast<int>(elem[i][j]);
                if(j!=broj_kolona-1)
                ss<<",";
            }
            if(i!=broj_redova-1){
                ss<<"},";
            }
            else{
                ss<<"}";
            }
        }
        ss<<"}";
        return ss.str();
    }
    void SacuvajUTekstualnuDatoteku(const char ime[]) const;
    void SacuvajUBinarnuDatoteku(const char ime[]) const;
    void ObnoviIzTekstualneDatoteke(const char ime[]);
    void ObnoviIzBinarneDatoteke(const char ime[]);
};
template <typename T>
T ** Matrica<T>::AlocirajMemoriju(int broj_redova, int broj_kolona){
    T **elem = new T*[broj_redova] {};
    try{
        for(int i = 0; i < broj_redova; i++){
            elem[i] = new T[broj_kolona];
        }
    } catch(...) {
        DealocirajMemoriju(elem, broj_redova);
        throw;
    }
    return elem;
}
template <typename T>
void Matrica<T>::DealocirajMemoriju(T **elem, int broj_redova){
    if(broj_redova!=0) {
        for(int i=0; i<broj_redova; i++){
            delete[] elem[i];
            elem[i]=nullptr;
        }
        delete[] elem;
        elem=nullptr;
    }
}
template <typename T>
Matrica<T>::Matrica(int broj_redova, int broj_kolona, char ime) :broj_redova(broj_redova), broj_kolona(broj_kolona), ime_mat(ime), elem(AlocirajMemoriju(broj_redova, broj_kolona)) {}
template <typename T>
void Matrica<T>::KopirajElemente(T **elem){
    for(int i=0; i<broj_redova; i++){ 
        std::copy(elem[i], elem[i]+broj_kolona, Matrica::elem[i]);
    }
}
template <typename T>
Matrica<T>::Matrica(const Matrica<T> &m) : broj_redova(m.broj_redova), broj_kolona(m.broj_kolona), ime_mat(m.ime_mat), elem(AlocirajMemoriju(m.broj_redova, m.broj_kolona)){
    KopirajElemente(m.elem);
}
template <typename T>
Matrica<T>::Matrica(Matrica<T> &&m) : broj_redova(m.broj_redova), broj_kolona(m.broj_kolona), elem(m.elem), ime_mat(m.ime_mat){
    m.broj_redova = 0;
    m.elem = nullptr;
}
template <typename T>
Matrica<T> &Matrica<T>::operator =(const Matrica<T> &m){
    if(broj_redova!=m.broj_redova || broj_kolona!=m.broj_kolona) {
        T **novi_prostor=AlocirajMemoriju(m.broj_redova, m.broj_kolona);
        for(int i=0; i<m.broj_redova; i++){
            std::copy(m.elem[i], m.elem[i]+m.broj_kolona, novi_prostor[i]);
        }
        DealocirajMemoriju(elem, broj_redova);
        elem=novi_prostor;
    } 
    else if(broj_redova>m.broj_redova){ 
        for(int i=m.broj_redova; i<broj_redova; i++){
            delete elem[i];
        }
    }
    broj_redova=m.broj_redova;
    broj_kolona=m.broj_kolona;
    ime_mat=m.ime_mat;
    KopirajElemente(m.elem);
    return *this;
}
template <typename T>
Matrica<T> &Matrica<T>::operator =(Matrica<T> &&m){
    std::swap(broj_redova, m.broj_redova);
    std::swap(broj_kolona, m.broj_kolona);
    std::swap(ime_mat, m.ime_mat);
    std::swap(elem, m.elem);
    return *this;
}
template <typename T>
std::istream& operator >>(std::istream &tok, Matrica<T> &m){
    for(int i = 0; i < m.broj_redova; i++)
        for(int j = 0; j < m.broj_kolona; j++) {
            std::cout << m.ime_mat << "(" << i + 1 << "," << j + 1 << ") = ";
            tok >> m.elem[i][j];
        }
    return tok;
}
template <typename T>
std::ostream& operator <<(std::ostream &tok, const Matrica<T> &m){
    int sirina=tok.width();
    for(int i = 0; i < m.broj_redova; i++) {
        for(int j = 0; j < m.broj_kolona; j++){ 
            tok.width(sirina);
            tok << m.elem[i][j];
    }
    tok << std::endl;
}
    return tok;
}
template <typename T>
Matrica<T> operator +(const Matrica<T> &m1, const Matrica<T> &m2){
    if(m1.broj_redova != m2.broj_redova || m1.broj_kolona != m2.broj_kolona){ 
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    }
    Matrica<T> m3(m1.broj_redova, m1.broj_kolona);
    for(int i = 0; i < m1.broj_redova; i++)
        for(int j = 0; j < m1.broj_kolona; j++)
            m3.elem[i][j] = m1.elem[i][j] + m2.elem[i][j];
    return m3;
}
template <typename T>
Matrica<T> operator *(const Matrica<T> &a, const Matrica<T> &b){
    if(a.broj_kolona==0 || b.broj_kolona==0 || a.broj_redova==0 || b.broj_redova==0|| a.broj_redova != b.broj_kolona) {
        throw std::domain_error("Matrice nisu saglasne za mnozenje");
    }
    Matrica<T> ret(a.broj_redova,b.broj_kolona);
    for(int i=0; i<a.broj_redova; i++) {
        for(int j=0; j<b.broj_kolona; j++) {
            T suma=T();
            for(int k=0; k<a.broj_kolona; k++) {
                suma+= a.elem[i][k] * b.elem[k][j];
            }
            ret.elem[i][j]=suma;
        }
    }
    return ret;
}
template <typename T>
Matrica<T> operator - (const Matrica<T> &a, const Matrica<T> &b){
    if(a.broj_redova != b.broj_redova || a.broj_kolona != b.broj_kolona){
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    }
    Matrica<T> ret(a.broj_redova,b.broj_kolona);
    for(int i=0; i<a.broj_redova; i++) {
        for(int j=0; j<b.broj_kolona; j++) {
            ret.elem[i][j]= a.elem[i][j] - b.elem[i][j];
        }
    }
    return ret;
}
template <typename T, typename T2>
Matrica<T> operator *(T2 broj, const Matrica<T> &m){
    Matrica<T> ret(m.broj_redova,m.broj_kolona);
    for(int i=0; i<m.broj_redova; i++) {
        for(int j=0; j<m.broj_kolona; j++) {
            ret.elem[i][j]=broj*m.elem[i][j];
        }
    }
    return ret;
}
template <typename T, typename T2>
Matrica<T> operator * (const Matrica<T> &m, T2 broj){
    Matrica<T> ret(m.broj_redova,m.broj_kolona);
    for(int i=0; i<m.broj_redova; i++) {
        for(int j=0; j<m.broj_kolona; j++) {
            ret.elem[i][j]=broj*m.elem[i][j];
        }
    }
    return ret;
}
template <typename T>
Matrica<T> operator +=(Matrica<T> &a, const Matrica<T> &b){
    return a=a+b;
}
template <typename T>
Matrica<T> operator -=(Matrica<T> &a, const Matrica<T> &b){
    return a=a-b;
}
template <typename T>
Matrica<T> operator *=(Matrica<T> &a, const Matrica<T> &b){
    return a=a*b;
}
template <typename T,typename T2>
Matrica<T> operator *=(Matrica<T> &a, T2 broj){
    return a=a*broj;
}
template <typename T>
void Matrica<T>::SacuvajUTekstualnuDatoteku(const char ime[])const{
    std::ofstream pisac(ime);
    if(!pisac){
        throw std::logic_error("Problemi sa upisom u datoteku");
    }
    for(int i=0; i<broj_redova; i++) {
        for(int j=0; j<broj_kolona; j++) {
            if(j==0){
                pisac << this->elem[i][j];
            }
            else{
                pisac << "," << this->elem[i][j];
            }
            if(!pisac){
                throw std::logic_error("Problemi sa upisom u datoteku");
            }
        }
        pisac << std::endl;
        if(!pisac){
            throw std::logic_error("Problemi sa upisom u datoteku");
        }
    }
}
template <typename T>
void Matrica<T>::SacuvajUBinarnuDatoteku(const char ime[]) const {
    std::ofstream pisac(ime, std::ios::binary);
    if (!pisac) {
        throw std::logic_error("Problemi sa upisom u datoteku");
    }
    pisac.write(reinterpret_cast<const char*>(this), sizeof(*this));
    for (int i = 0; i < broj_redova; i++) {
        pisac.write(reinterpret_cast<const char*>(elem[i]), sizeof(T) * broj_kolona);
    }
    if (!pisac) {
        throw std::logic_error("Problemi sa upisom u datoteku");
    }
}
template <typename T>
void Matrica<T>::ObnoviIzTekstualneDatoteke(const char ime[]){
    bool ulaz=true;
    std::vector<T> pom;
    std::ifstream file(ime);
    if(!file){
        throw std::logic_error("Trazena datoteka ne postoji");
    }
    char z=',';
    T I1;
    int red=0;
    int broj=0;
    while(z==',' && file>>I1) {
        broj++;
        file>>z;
        pom.push_back(I1);
    }
    red++;
    if(!file.eof()) {
        file.clear();
        file.seekg(-1, std::ios::cur);
    } 
    else if(file.eof()){
        ulaz=false;
    }
    else if(!file){
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
    if(ulaz){
        while(!file.eof()){
            char znak=',';
            T I2;
            int brpom=0;
            while(file>>I2 && znak==','){
                brpom++;
                file>>znak;
                pom.push_back(I2);
            }
            red++;
            if(!file.eof()){
                file.clear();
                file.seekg(-1, std::ios::cur);
            }
            if(broj != brpom){
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            else if(file.eof()){
                continue;
            }
            else if(!file){
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
        }
    }
    Matrica m(red, broj);
    int clan=0;
    for(int i=0; i<red; i++){
        for(int j=0; j<broj; j++){
            m.elem[i][j] = pom.at(clan);
            clan++;
        }
    }
    *this=m;
}
template <typename T>
void Matrica<T>::ObnoviIzBinarneDatoteke(const char ime[]){
    std::ifstream file(ime, std::ios::binary);
    if(!file){
        throw std::logic_error("Trazena datoteka ne postoji");
    }
    for (int i = 0; i < broj_redova; i++) {
        delete[] elem[i];
    }
    delete[] elem;
    file.read(reinterpret_cast<char*>(this), sizeof(*this));
    elem = new T*[broj_redova];
    for (int i = 0; i < broj_redova; i++) {
        elem[i] = new T[broj_kolona];
        file.read(reinterpret_cast<char*>(elem[i]), sizeof(T) * broj_kolona);
    }
    if (!file) {
        for (int i = 0; i < broj_redova; i++) {
            delete[] elem[i];
        }
        delete[] elem;
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
}
template <typename T>
Matrica<T>::Matrica(const char ime[], bool dat){
    if(dat){
        std::ifstream file(ime, std::ios::binary);
        if(!file){
            throw std::logic_error("Trazena datoteka ne postoji");
        }
        file.read(reinterpret_cast<char*>(this), sizeof(*this));
        elem = new T*[broj_redova] {};
        for(int i=0; i<broj_redova; i++) {
            elem[i]= new T[broj_kolona];
            file.read(reinterpret_cast<char*>(elem[i]), sizeof(T)*broj_kolona);
        }
        if(!file){
            for(int i=0; i<broj_redova; i++){
                delete elem[i];
            }
            delete[] elem;
            throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
    } 
    else{
        broj_redova=broj_kolona =0;
        ObnoviIzTekstualneDatoteke(ime);
    }
}
int main(){
    int mat_1, mat_2;
    std::cout<<"Unesite broj redova i kolona za matrice: "<<std::endl;
    std::cin>>mat_1>>mat_2;
    try{
        Matrica<double> mat(4,5);
        mat(0,0)=1.1;
        mat(0,1)=1.2;
        mat(0,2)=5;
        mat(0,3)=6;
        mat(1,0)=6;
        mat(1,1)=4;
        mat(1,2)=0.17;
        mat(1,3)=-1.7;

        mat.SacuvajUTekstualnuDatoteku("matrica.txt");
        mat.SacuvajUBinarnuDatoteku("matrica-bin");
        Matrica<double>mat_1("matrica.txt", false);
        mat_1.SacuvajUTekstualnuDatoteku("nova_matrica.txt");
        Matrica<double>mat_2("matrica.bin", true);
        mat_2.SacuvajUBinarnuDatoteku("nova_matrica.bin");
        return 0;
    }catch(const std::exception& el){
        std::cout<<"Greska: "<<el.what()<<std::endl;
        return 1;
    }
    return 0;
}