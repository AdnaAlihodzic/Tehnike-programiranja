//TP 2022/2023: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <tuple>
#include <utility>
#include <complex>

const double PI=4*atan(1.);
const double eps=0.000001;

class Sinusoida{
    private:
    double A;
    double w;
    double fi;
    public:
    double DajAmplitudu() const{
        return A;
    }
    double DajFrekvenciju() const{
        return w;
    }
    double DajFazu() const{
        return fi;
    }
    std::tuple<double, double, double> DajParametre() const {
      return std::make_tuple(A, w, fi);
    }

    Sinusoida(double A, double w, double fi){
        if(w<0){
            w*=(-1);
            fi=fi+PI;
        }
        if(A<0){
            A*=(-1);
            fi=fi+PI;
        }
        fi=atan2(sin(fi), cos(fi));
        this->A=A;
        this->w=w;
        this->fi=fi;
    }
    Sinusoida &PostaviAmplitudu(double A){
        if(A<0){
            A*=(-1);
            fi=fi+PI;
        }
        fi=atan2(sin(fi), cos(fi));
        this->A=A;
        return *this;
    }
    Sinusoida &PostaviFrekvenciju(double w){
        if(w<0){
            w*=(-1);
            fi=-fi+PI;
        }
        fi=atan2(sin(fi), cos(fi));
        this->w=w;
        return *this;
    }
    Sinusoida &PostaviFazu(double fi){
        this->fi=atan2(sin(fi), cos(fi));
        return *this;
    }
    Sinusoida &PostaviParametre(std::tuple<double, double, double> parametri){
        PostaviAmplitudu(std::get<0>(parametri));
        PostaviFrekvenciju(std::get<1>(parametri));
        PostaviFazu(std::get<2>(parametri));
        return *this;
    }
    double operator()(double t){
        double vrijednost=A*sin(w*t+fi);
        return vrijednost;
    }
    double operator[](const char *c)const{
        std::string parametar(c);
        if(parametar=="A"){
            return A;
        }
        else if(parametar=="fi" || parametar=="phi"){
            return fi;
        }
        else if(parametar=="omega" || parametar=="w"){
            return w;
        }
        else{
            throw std::domain_error("Neispravan naziv parametra");
        }
    }
    double &operator [](const char *c){
        std::string parametar(c);
        if(parametar=="A"){
            return A;
        }
        else if(parametar=="fi" || parametar=="phi"){
            return fi;
        }
        else if(parametar=="omega" || parametar=="w"){
            return w;
        }
        else{
            throw std::domain_error("Neispravan naziv parametra");
        }
    }
    Sinusoida &operator+=(const Sinusoida &s){
        if(fabs(w-s.w)>eps){
            throw std::domain_error("Razlicite frekvencije");
        }
        A=A+s.A;
        return *this;
    }
    Sinusoida &operator -=(const Sinusoida &s){
        if(fabs(w-s.w)>eps){ 
            throw std::domain_error("Razlicite frekvencije");
        }
        A=A-s.A;
        return *this;
    }
    Sinusoida &operator *=(const double broj){
        A=A*broj;
        return *this;
    }
    Sinusoida &operator /=(const double broj){
        A=A/broj;
        return *this;
    }
    friend Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2);
    friend Sinusoida operator *(const Sinusoida &s, double broj);
    friend Sinusoida operator /(const Sinusoida &s, double broj);
    friend Sinusoida operator -(const Sinusoida &s){
        return Sinusoida(-s.A, s.w, s.fi);
    };
};
Sinusoida operator +(const Sinusoida &s1, const Sinusoida &s2){
    if(fabs(s1.w-s2.w)>eps){
        throw std::domain_error("Razlicite frekvencije");
    }
    std::complex<double> s3;
    s3=s1.A*std::exp(std::complex<double>(0, s1.fi))+s2.A*std::exp(std::complex<double>(0, s2.fi));
    return Sinusoida(abs(s3), s1.w, arg(s3));
}
Sinusoida operator -(const Sinusoida &s1, const Sinusoida &s2){
    if(fabs(s1.w-s2.w)>eps){
        throw std::domain_error("Razlicite frekvencije");
    }
    std::complex<double> s3;
    s3=s1.A*std::exp(std::complex<double>(0, s1.fi))-s2.A*std::exp(std::complex<double>(0, s2.fi));
    return Sinusoida(abs(s3), s1.w, arg(s3));
}
Sinusoida operator *(const Sinusoida &s, double broj){
    return Sinusoida(s.A *broj, s.w, s.fi);
}
Sinusoida operator *(double broj, const Sinusoida &s){
    return s*broj;
}
Sinusoida operator /(const Sinusoida &s, double broj){
    return Sinusoida(s.A/broj, s.w, s.fi);
}
Sinusoida operator /(double broj, const Sinusoida &s){
    return s/broj;
}
Sinusoida operator -(Sinusoida &s){
    return Sinusoida(-s.DajAmplitudu(), s.DajFrekvenciju(), s.DajFazu());
}

int main ()
{
    Sinusoida sin_1(1, 2, 5);
    Sinusoida sin_2(4, 5, 6);
    std::cout<<"sin_1(0.0)= "<<sin_1(0.0)<<std::endl;
    std::cout<<"sin_2(0.0)= "<<sin_2(0.0)<<std::endl;
    Sinusoida sin_3=sin_1+sin_2;
    std::cout<<"s3(0.0)= "<<sin_3(0.0)<<std::endl;
	return 0;
}
