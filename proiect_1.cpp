#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

ifstream fin("date.in");

int maxim(int v[], int n)
{
    int maxi = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > maxi)
            maxi = v[i];
    return maxi;
}


void sortcifre(int v[], int n, int exp)
{
    vector<int> v2(n);
    int fr[10] = { 0 };

    for (int i = 0; i < n; i++)
        fr[(v[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        fr[i] = fr[i] + fr[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        v2[fr[(v[i] / exp) % 10] - 1] = v[i];
        fr[(v[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = v2[i];
}


void radixSort(int v[], int n)
{
    int maxi = maxim(v, n);
    for (int exp = 1; maxi / exp > 0; exp = exp * 10)
        sortcifre(v, n, exp);
}

void merge(int v[], int stg, int mij, int dr) {
    int n1 = mij - stg + 1;
    int n2 = dr - mij;

    //Crearea subvectorilor temporari pt stanga si dreapta
    int *vs = new int[n1];
    int *vd = new int[n2];

    //Copiem datele în subvectorii temporari
    for (int i = 0; i < n1; i++)
    {
        vs[i] = v[stg + i];
    }
    for (int j = 0; j < n2; j++)
    {
        vd[j] = v[mij + 1 + j];
    }

    //Interclasarea subvectorilor temporari înapoi în vectorul principal
    int i = 0, j = 0, k = stg;
    while (i < n1 && j < n2)
    {
        if (vs[i] <= vd[j])
        {
            v[k] = vs[i];
            i++;
        }
        else
        {
            v[k] = vd[j];
            j++;
        }
        k++;
    }

    // Copierea elementelor rămase din vd (dacă există)
    while (j < n2)
    {
        v[k] = vd[j];
        j++;
        k++;
    }
}

// Funcția principală care sortează elementele folosind algoritmul MergeSort
void mergeSort(int v[], int stg, int dr)
{
    if (stg >= dr)
    {
        // Vectorul are cel mult un element, deci este deja sortat
        return;
    }

    int mij = stg + (dr - stg) / 2;
    mergeSort(v, stg, mij);   // Sortarea primei jumătăți a vectorului
    mergeSort(v, mij + 1, dr);  // Sortarea celei de-a doua jumătăți a vectorului
    merge(v, stg, mij, dr); // Interclasarea celor două jumătăți sortate
}

void shellSort(int v[], int n)
{
    for (int k = n / 2; k > 0; k = k / 2)
    {
        for (int i = k; i < n; i = i + 1)
        {
            int aux = v[i];
            int j;
            for (j = i; j >= k && v[j - k] > aux; j = j - k)
                v[j] = v[j - k];
            v[j] = aux;
        }
    }
}


int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Iau pivot-ul
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sortez partea stanga si dreapta
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

    // cel mai bun caz
    if (start >= end)
        return;

    // il impart
    int p = partition(arr, start, end);

    // Sortez partea stanga
    quickSort(arr, start, p - 1);

    // Sortez partea dreapta
    quickSort(arr, p + 1, end);
}


void countSort(int v[], int n)
{
    int maxi = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > maxi)
            maxi = v[i];

    int vcount[maxi + 1] = { 0 };
    for (int i = 0; i < n; i++)
        vcount[v[i]]++;

    for (int i = 1; i <= maxi; i++)
        vcount[i] = vcount[i] + vcount[i - 1];

    int sortedv[n];
    for (int i = n - 1; i >= 0; i--)
    {
        sortedv[vcount[v[i]] - 1] = v[i];
        vcount[v[i]]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = sortedv[i];

}


bool test_sort(int v[], int n)
{
    if (n == 0 || n == 1)
        return true;
    for (int i = 1; i < n; i++)
        if (v[i] < v[i - 1])
            return false;
    return true;
}

int main()
{
    int n;
    fin >> n;
    int v[n], v1[n], v2[n], v3[n], v4[n], v5[n];
    for (int i = 0; i < n; i++)
    {
        fin >> v[i];
        v1[i] = v[i];
        v2[i] = v[i];
        v3[i] = v[i];
        v4[i] = v[i];
        v5[i] = v[i];
    }


    //radixSort(v,n);
    cout << "RadixSort ";
    /*for (int i=0; i<n; i++)
        cout<<v[i]<< " "; */
    auto start1 = high_resolution_clock::now(); // momentul de inceput al masurarii
    radixSort(v1, n);
    auto stop1 = high_resolution_clock::now(); // momentul de sfarsit al masurarii

    auto duration1 = duration_cast<nanoseconds>(stop1 - start1); // calcularea duratei in microsecunde
    cout << "Durata de executie a functiei este: " << duration1.count() << " nanosecunde." << endl;



    // mergeSort(v2,0,n-1);
    cout << endl << "MergeSort ";
    /*for (int i=0; i<n; i++)
        cout<<v2[i]<< " ";*/

    auto start2 = high_resolution_clock::now(); // momentul de inceput al masurarii
    mergeSort(v2, 0, n - 1);
    auto stop2 = high_resolution_clock::now(); // momentul de sfarsit al masurarii

    auto duration2 = duration_cast<nanoseconds>(stop2 - start2); // calcularea duratei in microsecunde
    cout << "Durata de executie a functiei este: " << duration2.count() << " nanosecunde." << endl;


    
    //shellSort(v3,n);
    cout << endl << "ShellSort ";
    /*for (int i=0; i<n; i++)
        cout<<v3[i]<< " ";*/
    auto start3 = high_resolution_clock::now(); // momentul de inceput al masurarii
    shellSort(v3, n);
    auto stop3 = high_resolution_clock::now(); // momentul de sfarsit al masurarii

    auto duration3 = duration_cast<nanoseconds>(stop3 - start3); // calcularea duratei in microsecunde
    cout << "Durata de executie a functiei este: " << duration3.count() << " nanosecunde." << endl;


    
    //bubbleSort(v4,n);
    cout << endl << "QuickSort ";
    /*for (int i=0; i<n; i++)
        cout<<v4[i]<< " ";*/
    auto start4 = high_resolution_clock::now(); // momentul de inceput al masurarii
    quickSort(v4, 0, n);
    auto stop4 = high_resolution_clock::now(); // momentul de sfarsit al masurarii

    auto duration4 = duration_cast<nanoseconds>(stop4 - start4); // calcularea duratei in microsecunde
    cout << "Durata de executie a functiei este: " << duration4.count() << " nanosecunde." << endl;


    
    //countSort(v5,n);
    cout << endl << "CountSort ";
    /*for (int i=0; i<n; i++)
        cout<<v5[i]<< " ";*/
    auto start5 = high_resolution_clock::now(); // momentul de inceput al masurarii
    countSort(v5, n);
    auto stop5 = high_resolution_clock::now(); // momentul de sfarsit al masurarii

    auto duration5 = duration_cast<nanoseconds>(stop5 - start5); // calcularea duratei in microsecunde
    cout << "Durata de executie a functiei este: " << duration5.count() << " nanosecunde." << endl;

    
    
    cout << endl;
    
}
