#include <iostream>

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

template <typename TipKljuc, typename TipVrijednost>
class NizMapa : public Mapa<TipKljuc, TipVrijednost>{
    Par<TipKljuc, TipVrijednost> *niz = nullptr;
    int kapacitet = 1000;
    int broj = 0;
    void dealociraj(){
        delete [] niz;
        broj = 0;
        kapacitet = 1000;
    }
    public:
    ~NizMapa(){
        delete [] niz;
        kapacitet = 1000;
        broj = 0;
        niz = nullptr;
    }
    NizMapa(){
        niz = new Par<TipKljuc, TipVrijednost>[kapacitet]{};
    }
    NizMapa(const NizMapa<TipKljuc, TipVrijednost> &m){
        kapacitet = m.kapacitet;
        broj = m.broj;
        niz = new Par<TipKljuc, TipVrijednost>[kapacitet]{};
        for(int i = 0; i < broj; i++) niz[i] = m.niz[i];
    }
    NizMapa<TipKljuc, TipVrijednost> &operator =(const NizMapa<TipKljuc, TipVrijednost> &m){
        if(&m == this) return *this;
        dealociraj();
        broj = m.broj;
        kapacitet = m.kapacitet;
        niz = new Par<TipKljuc, TipVrijednost>[kapacitet]{};
        for(int i = 0; i < broj; i++) niz[i] = m.niz[i];
        return *this;
    }
    TipVrijednost &operator [](const TipKljuc &kljuc){
        for(int i = 0; i < broj; i++){
            if(niz[i].kljuc == kljuc) return niz[i].vrijednost;
        }
        if(broj + 1 > kapacitet){
            kapacitet*=2;
            auto temp = new Par<TipKljuc, TipVrijednost>[kapacitet]{};
            for(int i = 0; i < broj; i++) temp[i] = niz[i];
            
            delete [] niz;
            niz = temp;
        }
        niz[broj++] = {kljuc, TipVrijednost()};
        return niz[broj - 1].vrijednost;
    }
    const TipVrijednost operator [](const TipKljuc &kljuc) const{
        for(int i = 0; i < broj; i++){
            if(niz[i].kljuc == kljuc) return niz[i].vrijednost;
        }
        return TipVrijednost();
    }
    int brojElemenata() const{
        return broj;
    }
    void obrisi(){
        broj = 0;
    }
    void obrisi(const TipKljuc &el){
        for(int i = 0; i < broj; i++){
            if(niz[i].kljuc == el){
                for(int j = i; j < broj - 1; j++){
                    niz[j] = niz[j + 1];
                }broj--;
                return;
            }
        }
        throw std::range_error("Nema tog kljuca");
    }
};

int main(){
    return 0;
}