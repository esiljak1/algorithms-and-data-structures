#include <iostream>

template <typename TipKljuc, typename TipVrijednost>
struct BinStablo{
  BinStablo *roditelj;
  BinStablo *lijevi, *desni;
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
class BinStabloMapa : public Mapa<TipKljuc, TipVrijednost>{
    BinStablo<TipKljuc, TipVrijednost> *pocetni = nullptr;
    int brElemenata = 0;
    
    void odstraniSve(BinStablo<TipKljuc, TipVrijednost> *&p){
        if(p == nullptr) return;
         odstraniSve(p -> desni);
         odstraniSve(p -> lijevi);
         delete p;
         p = nullptr;
    }
    BinStablo<TipKljuc, TipVrijednost> *dodajElemente(BinStablo<TipKljuc, TipVrijednost> *&p, BinStablo<TipKljuc, TipVrijednost> *t){
        if(t == nullptr) return nullptr;
        BinStablo<TipKljuc, TipVrijednost> *l = nullptr, *d = nullptr, *ret = nullptr;
        
        p = new BinStablo<TipKljuc, TipVrijednost>{p, nullptr, nullptr, t->kljuc, t->vrijednost};
        ret = p;
        
        d = dodajElemente(p -> desni, t -> desni);
        l = dodajElemente(p -> lijevi, t -> lijevi);
        ret -> desni = d;
        ret -> lijevi = l;
        
        return ret;
    }
    public:
    BinStabloMapa() : pocetni(nullptr), brElemenata(0){}
    ~BinStabloMapa(){
        odstraniSve(pocetni);
    }
    BinStabloMapa(const BinStabloMapa<TipKljuc, TipVrijednost> &b){
        brElemenata = b.brElemenata;
        dodajElemente(pocetni, b.pocetni);
    }
    BinStabloMapa<TipKljuc, TipVrijednost> &operator =(const BinStabloMapa<TipKljuc, TipVrijednost> &b){
        if(&b == this) return *this;
        obrisi();
        brElemenata = b.brElemenata;
        dodajElemente(pocetni, b.pocetni);
        return *this;
    }
    TipVrijednost &operator [](const TipKljuc &el){
        BinStablo<TipKljuc, TipVrijednost> *it = pocetni, *roditelj = nullptr;
        while(it != nullptr){
            if(it -> kljuc == el) return it -> vrijednost;
            
            if(it -> kljuc < el){
                roditelj = it;
                it = it -> desni;
            }    
            else if(it -> kljuc > el){
                roditelj = it;
                it = it -> lijevi;
            }    
        }
        it = new BinStablo<TipKljuc, TipVrijednost>{roditelj, nullptr, nullptr, el, TipVrijednost()};
        if(!pocetni) pocetni = it;
        else{
            if(roditelj -> kljuc > el){
                roditelj -> lijevi = it;
            }else{
                roditelj -> desni = it;
            }
        }
        brElemenata++;
        return it -> vrijednost;
    }
    const TipVrijednost operator [](const TipKljuc &el) const{
        BinStablo<TipKljuc, TipVrijednost> *it = pocetni;
        while(it != nullptr){
            if(it -> kljuc == el) return it -> vrijednost;
            
            if(it -> kljuc < el){
                it = it -> desni;
            }    
            else if(it -> kljuc > el){
                it = it -> lijevi;
            }    
        }
        return TipVrijednost();
    }
    int brojElemenata() const{
        return brElemenata;
    }
    void obrisi(){
        odstraniSve(pocetni);
        brElemenata = 0;
    }
    void obrisi(const TipKljuc &el){
        BinStablo<TipKljuc, TipVrijednost> *it = pocetni, *roditelj = nullptr, *m = nullptr;
        while(it != nullptr && el != it -> kljuc){
            roditelj = it;
            if(el < it -> kljuc){
                it = it -> lijevi;
            }else if(el > it -> kljuc){
                it = it -> desni;
            }
        }
        if(it == nullptr){
            throw std::domain_error("Nema elementa sa zadanim kljucem");
        }
        if(it -> lijevi == nullptr){
            m = it -> desni;
        }else{
            if(it -> desni == nullptr){
                m = it -> lijevi;
            }else{
                BinStablo<TipKljuc, TipVrijednost> *pm = it, *tmp = nullptr;
                m = it -> lijevi;
                tmp = m -> desni;
                while(tmp != nullptr){
                    pm = m;
                    m = tmp;
                    tmp = m -> desni;
                }
                if(pm != it){
                    pm -> desni = m -> lijevi;
                    m -> lijevi = it -> lijevi;
                }
                m -> desni = it -> desni;
            }
        }if(roditelj == nullptr){
                pocetni = m;
        }else{
            if(it == roditelj -> lijevi){
                roditelj -> lijevi = m;
            }else{
                roditelj -> desni = m;
            }
        }
        delete it;
        brElemenata--;
    }
};

int main(){
    return 0;
}