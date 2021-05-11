#include <iostream>
#include <functional>

unsigned int hash_f(int ulaz, unsigned int max) {
	unsigned int suma=23; 
	suma = suma*31 + ulaz;
	return suma % max;
}

template <typename TipKljuc, typename TipVrijednost>
struct Par{
    TipKljuc kljuc;
    TipVrijednost vrijednost;
};

template<typename TipKljuc, typename TipVrijednost>
class Mapa{
    public:
    virtual ~Mapa(){}
    virtual TipVrijednost &operator[](const TipKljuc &kljuc) = 0;
    virtual const TipVrijednost operator[](const TipKljuc &kljuc) const = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipKljuc &el) = 0;
};

template<typename TipKljuc, typename TipVrijednost>
class HashMapa : public Mapa<TipKljuc, TipVrijednost>{
    Par<TipKljuc, TipVrijednost> **niz;
    unsigned int kapacitet;
    int brElemenata;
    std::function<unsigned int(TipKljuc, unsigned int)> fun;
    void dealociraj(){
        for(int i = 0; i < kapacitet; i++) delete niz[i];
        delete [] niz;
        niz = nullptr;
        kapacitet = 0;
        brElemenata = 0;
    }
    public:
    HashMapa() : kapacitet(1000), brElemenata(0){
        niz = new Par<TipKljuc, TipVrijednost>*[kapacitet]{};
        for(int i = 0; i < kapacitet; i++) niz[i] = new Par<TipKljuc, TipVrijednost>{TipKljuc(), TipVrijednost()};
    }
    ~HashMapa(){
        for(int i = 0; i < kapacitet; i++) delete niz[i];
        delete [] niz;
        kapacitet = 1000;
        brElemenata = 0;
        fun = nullptr;
    }
    HashMapa(const HashMapa<TipKljuc, TipVrijednost> &mapa){
        kapacitet = mapa.kapacitet;
        brElemenata = mapa.brElemenata;
        fun = mapa.fun;
        niz = new Par<TipKljuc, TipVrijednost>*[kapacitet]{};
        for(int i = 0; i < kapacitet; i++){
            niz[i] = new Par<TipKljuc, TipVrijednost>{mapa.niz[i] -> kljuc, mapa.niz[i] -> vrijednost};
        }
    }
    HashMapa<TipKljuc, TipVrijednost> &operator =(const HashMapa<TipKljuc, TipVrijednost> &mapa){
        if(this == &mapa) return *this;
        dealociraj();
        kapacitet = mapa.kapacitet;
        brElemenata = mapa.brElemenata;
        fun = mapa.fun;
        niz = new Par<TipKljuc, TipVrijednost>*[kapacitet]{};
        for(int i = 0; i < kapacitet; i++){
            niz[i] = new Par<TipKljuc, TipVrijednost>{mapa.niz[i] -> kljuc, mapa.niz[i] -> vrijednost};
        }
        return *this;
    }
    void definisiHashFunkciju(std::function<unsigned int(TipKljuc, unsigned int)> f){
        fun = f;
    }
    TipVrijednost &operator [](const TipKljuc &kljuc){
        if(brElemenata + 1 > kapacitet){
            kapacitet*=2;
            auto temp = new Par<TipKljuc, TipVrijednost>*[kapacitet]{};
            for(int i = 0; i < kapacitet; i++) temp[i] = new Par<TipKljuc, TipVrijednost>{TipKljuc(), TipVrijednost()};
            for(int i = 0; i < brElemenata; i++){
                int ind = fun(niz[i] -> kljuc, kapacitet);
                if(ind == kapacitet - 1 && temp[ind] != nullptr && temp[ind] -> kljuc != niz[i] -> kljuc){
                    while(ind > 0){
                        if(temp[ind] == nullptr){
                            ind--;
                            continue;
                        }
                        if(temp[ind] -> kljuc == TipKljuc()) break;
                        ind--;
                    }
                }
                while(temp[ind] -> kljuc != TipKljuc() && temp[ind] -> vrijednost != TipVrijednost() && ind < kapacitet){
                    ind++;
                }temp[ind] -> kljuc = niz[i] -> kljuc;
                temp[ind] -> vrijednost = niz[i] -> vrijednost;
            }
            for(int i = 0; i < kapacitet/2; i++) delete niz[i];
            delete [] niz;
            niz = temp;
        }
        unsigned int index = fun(kljuc, kapacitet);
        bool uslov = true;
        int ind = index;
        if(index == kapacitet - 1 && niz[index] != nullptr && niz[index] -> kljuc != TipKljuc()){
            while(ind > 0){
                if(niz[ind] == nullptr){
                    ind--;
                    continue;
                }
                if(niz[ind] -> kljuc == kljuc) return niz[ind] -> vrijednost;
                if(niz[ind] -> kljuc == TipKljuc() && niz[ind] -> vrijednost == TipVrijednost()) break;
                ind--;
            }
            uslov = false;
        }
        while(uslov){
            if(niz[index] == nullptr){
                ind = index;
                index++;
                continue;
            }
            if(index >= kapacitet || niz[index] -> kljuc == TipKljuc() || niz[index] -> vrijednost == TipVrijednost()) break;
            if(niz[index] -> kljuc == kljuc) return niz[index] -> vrijednost;
            index++;
        }
        brElemenata++;
        if(niz[ind] == nullptr){
            niz[ind] = new Par<TipKljuc, TipVrijednost>{};
        }
        niz[ind] -> kljuc = kljuc; 
        niz[ind] -> vrijednost = TipVrijednost();
        return niz[ind] -> vrijednost;
    }
    const TipVrijednost operator [](const TipKljuc &kljuc) const{
        unsigned int index = fun(kljuc, kapacitet);
        auto temp = index;
        while(1){
            if(niz[index] == nullptr){
                index++;
                continue;
            }
            if(index >= kapacitet || niz[index] -> kljuc == TipKljuc() || niz[index] -> vrijednost == TipVrijednost()) break;
            if(fun(niz[index] -> kljuc, kapacitet) != temp) break;
            if(niz[index] -> kljuc == kljuc) return niz[index] -> vrijednost;
            index++;
        }
        return TipVrijednost();
    }
    int brojElemenata() const{
        return brElemenata;
    }
    void obrisi(){
        for(int i = 0; i < kapacitet; i++){
            niz[i] -> kljuc = TipKljuc();
            niz[i] -> vrijednost = TipVrijednost();
        }brElemenata = 0;
    }
    void obrisi(const TipKljuc &el){
        unsigned int index = fun(el, kapacitet);
        auto temp = index;
        if(index == kapacitet - 1 && niz[index] != nullptr && niz[index] -> kljuc != el){
            while(index >= 0){
                if(niz[index] == nullptr){
                    index--;
                    continue;
                }
                if(niz[index] -> kljuc == el){
                    delete niz[index];
                    niz[index] = nullptr;
                    brElemenata--;
                    return;
                }index--;
            }throw std::range_error("Nema tog kljuca");
        }
        while(1){
            if(niz[index] == nullptr){
                index++;
                continue;
            }
            if(index >= kapacitet || niz[index] -> kljuc == TipKljuc() || niz[index] -> vrijednost == TipVrijednost()) break;
            if(fun(niz[index] -> kljuc, kapacitet) != temp) break;
            if(niz[index] -> kljuc == el){
                delete niz[index];
                niz[index] = nullptr;
                brElemenata--;
                return;
            }
        }throw std::range_error("Nema tog kljuca");
    }
};

int main(){
    return 0;
}