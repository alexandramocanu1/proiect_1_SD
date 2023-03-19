#include <iostream>
#include <cstdlib> // biblioteca pentru functia rand()

using namespace std;

int main() {
    int n, m;
    cout << "Introduceti numarul de valori si valoarea maxima: ";
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        int numar_aleatoriu = rand() % m;
        cout << numar_aleatoriu << " ";
    }
    cout << endl;
    return 0;
}
