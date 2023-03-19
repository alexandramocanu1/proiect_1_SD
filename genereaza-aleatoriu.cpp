#include <iostream>
#include <random>

int main()
{
    int n, m;
    std::cout << "Introduceti numarul de numere aleatorii (n): ";
    std::cin >> n;
    std::cout << "Introduceti valoarea maxima (m): ";
    std::cin >> m;

    // se initializeaza generatorul cu o valoare aleatoare initiala
    std::random_device rd;
    std::mt19937 gen(rd());

    // se creeaza o distributie uniforma intre 0 si m-1
    std::uniform_int_distribution<> dis(0, m-1);

    // se genereaza n numere aleatoare si se afiseaza
    for (int i = 0; i < n; ++i) {
        std::cout << dis(gen) << " ";
    }

    std::cout << "\n";
    return 0;
}
