#include <iostream>
#include <cmath>
#include <vector>

template <typename Tip>
void bubble_sort(Tip *niz, int velicina){
    bool sortiran = true;
    for(int i = 0; i<velicina - 1 ; i++){
        sortiran = true;
        for(int j = 0; j < velicina - 1; j++){
            if(niz[j] > niz[j+1]){
                auto temp = niz[j];
                niz[j] = niz[j+1];
                niz[j+1] = temp;
                sortiran = false;
            }
        }if(sortiran) break;
    }
}

template <typename Tip>
void selection_sort(Tip *niz, int velicina){
    for(int i = 0; i < velicina; i++){
        int mini = i;
        for(int j = i + 1; j < velicina; j++){
            if(niz[j] < niz[mini]) mini = j;
        }auto temp = niz[i];
        niz[i] = niz[mini];
        niz[mini] = temp;
    }
}

template <typename Tip>
int particija(Tip *niz, int prvi, int zadnji){
    Tip pivot = niz[zadnji];
    int p = prvi - 1;
    for(int i = prvi; i < zadnji; i++){
        if(niz[i] < pivot){
            p++;
            Tip temp = niz[i];
            niz[i] = niz[p];
            niz[p] = temp;
        }
    }
    Tip temp = niz[p + 1];
    niz[p + 1] = niz[zadnji];
    niz[zadnji] = temp;
    return p+1;
}
template<typename Tip>
void quick_sort_pomocna(Tip *niz, int pocetak, int kraj){
    if(pocetak >= kraj) return;
    int j = particija(niz, pocetak, kraj);
    quick_sort_pomocna(niz, pocetak, j-1);
    quick_sort_pomocna(niz, j+1, kraj);
}

template <typename Tip>
void quick_sort(Tip *niz, int velicina){
    quick_sort_pomocna(niz, 0, velicina - 1);
}

template<typename Tip>
void merge(Tip *niz, int pocetak1, int kraj1, int pocetak2, int kraj2, int indeks){
    if(pocetak1 > kraj1 || pocetak2 > kraj2){
        if(pocetak1 > kraj1){
            int i = pocetak2;
            while(i <= kraj2){
                niz[indeks++] = niz[i++];
            }
        }else{
            int i = pocetak1;
            while(i <= kraj1){
                niz[indeks++] = niz[i++];
            }
        }return;
    }
    Tip temp;
    if(niz[pocetak1] < niz[pocetak2]){
        temp = niz[pocetak1];
        merge(niz, pocetak1 + 1, kraj1, pocetak2, kraj2, indeks + 1);
    }else{
        temp = niz[pocetak2];
        merge(niz, pocetak1, kraj1, pocetak2 + 1, kraj2, indeks + 1);
    }
    niz[indeks] = temp;
}

template<typename Tip>
void merge_sort_pomocna(Tip *niz, int prvi, int zadnji){
    if(prvi >= zadnji) return;
    int p = std::floor((prvi + zadnji - 1)/2);
    int q = p + 1;
    merge_sort_pomocna(niz, prvi, p);
    merge_sort_pomocna(niz, q, zadnji);
    merge(niz, prvi, p, q, zadnji, prvi);
}
template <typename Tip>
void merge_sort(Tip *niz, int velicina){
    merge_sort_pomocna(niz, 0, velicina - 1);
}

int dajMaxBroj(std::vector<int> &v){
    int max = 0;
    for(int i = 1; i < v.size(); i++){
        if(v.at(i) > v.at(max)) max = i;
    }
    return max;
}

void countingSort(std::vector<int> &v, int pozicija){
    std::vector<int> output(v.size()), brojac(10, 0);
    
    for(int i = 0; i < v.size(); i++) brojac.at((v.at(i) / pozicija) % 10)++;
    
    for(int i = 1; i < 10; i++) brojac.at(i) += brojac.at(i - 1);
    
    for(int i = v.size() - 1; i >= 0; i--){
        output.at(brojac.at((v.at(i) / pozicija) % 10) - 1) = v.at(i);
        brojac.at((v.at(i) / pozicija) % 10)--;
    }
    v = output;
}

void radixSort(std::vector<int> &v){
    int ponavljanje = v.at(dajMaxBroj(v));
    for(int place = 1; ponavljanje / place > 0; place *= 10) countingSort(v, place);
}

void Gomila(std::vector<int> &v, int n, int i){
    int max = i;
    int l = 2 * i + 1, d = 2 * i + 2;
    
    if(l < n && v.at(l) > v.at(max)){
        max = l;
    }
    if(d < n && v.at(d) > v.at(max)){
        max = d;
    }
    if(max != i){
        std::swap(v.at(i), v.at(max));
        Gomila(v, n, max);
    }
}

void pomocna(std::vector<int> &v, int n, int i){
    if(i == 0) return;
    int broj = (i - 1)/2;
    if(v.at(i) > v.at(broj)){
        std::swap(v.at(i), v.at(broj));
    }
    pomocna(v, n, broj);
}

void stvoriGomilu(std::vector<int> &a){
    int start = a.size()/2 + 1;
    
    for(int i = start; i >= 0; i--){
        Gomila(a, a.size(), i);
    }
    
}

void umetniUGomilu(std::vector<int> &a, int umetni, int &velicina){
    a.insert(a.begin() + velicina, umetni);
    velicina++;
    pomocna(a, velicina, velicina - 1);
}

void izbaciPrvi(std::vector<int> &a, int &velicina){
    
    std::swap(a.at(0), a.at(velicina - 1));
    velicina--;
    
    Gomila(a, velicina, 0);
}

void gomilaSort(std::vector<int> &a){
    
    for(int i = a.size()/2 - 1; i >= 0; i--){
        Gomila(a, a.size(), i);
    }
    
    for(int i = a.size() - 1; i >= 0; i--){
        std::swap(a.at(0), a.at(i));
        
        Gomila(a, i, 0);
    }
}

int main() {
    
    return 0;
}