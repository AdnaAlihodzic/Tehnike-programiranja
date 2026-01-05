//TP 2022/2023: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T, typename T2, typename F1, typename F2> 
auto GeneraliziraniMatricniProizvod(const vector<vector<T>> &A, const vector<vector<T2>> &B, const F1 &f, const F2 &g)->vector<vector<decltype(g(A[0][0], B[0][0]))>> {
    if (A.size() == 0 || A[0].size() == 0 || B.size() == 0 || B[0].size() == 0 || A[0].size() != B.size()) {
        return {};
    }
    
    for (const auto& row : A) {
        if (row.size() != B.size()) {
            throw domain_error("Matrice nisu saglasne za mnozenje");
        }
    }
    
    vector<vector<decltype(g(A[0][0], B[0][0]))>> C(A.size(), vector<decltype(g(A[0][0], B[0][0]))>(B[0].size(), g(A[0][0], B[0][0])));
    for (size_t i = 0; i < C.size(); i++) {
        for (size_t j = 0; j < C[i].size(); j++) {
            auto rez = g(A[i][0], B[0][j]);
            for (size_t k = 1; k < B.size(); k++) {
                try {
                    rez = f(rez, g(A[i][k], B[k][j]));
                    } catch (...) { 
                        throw runtime_error("Neocekivani problemi pri racunanju");
                    }
            }
            C[i][j] = rez;
        }
    }
    return C;
}

int main ()
{
    int m, n, p;
    std::cout << "Unesite broj redova prve matrice: ";
    std::cin >> m;
    std::cout<< "Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
    std::cin >> n;
    std::cout << "Unesite broj kolona druge matrice: " << std::endl;
    std::cin >> p;
    std::vector<std::vector<std::string>> A(m, std::vector<std::string>(n));
    std::vector<std::vector<std::string>> B(n, std::vector<std::string>(p));
    std::cout << "Unesite elemente prve matrice:" << std::endl;
    for (auto& row : A) {
        for (auto& elem : row) {
            std::cin >> elem;
        }
    }
    std::cout << "Unesite elemente druge matrice:" << std::endl;
    for (auto& row : B) {
        for (auto& elem : row) {
            std::cin >> elem;
        }
    }
    std::cout << std::endl << "Matricni proizvod:" << std::endl;
    try {
        auto C = GeneraliziraniMatricniProizvod(A, B, [](std::string x, std::string y) { return x + "+" + y; }, [](std::string x, std::string y) { return x + "*" + y; });
        for (const auto& row : C) {
            for (const auto& elem : row) {
                std::cout << elem << "  ";
            }
            std::cout << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
