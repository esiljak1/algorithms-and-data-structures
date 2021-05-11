#include <iostream>

template <typename Tip>
struct Cvor{
    Tip element;
    Cvor *prethodni, *sljedeci;
};

template <typename Tip1>
class Lista{
    public:
    
    virtual ~Lista(){}
    virtual int brojElemenata() const = 0;
    virtual Tip1 &trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip1& el) = 0;
    virtual void dodajIza(const Tip1& el) = 0;
    virtual Tip1 &operator [] (int n) = 0;
    virtual const Tip1 &operator [](int n) const = 0;
};


template <typename Tip>
class DvostrukaLista : public Lista<Tip>{
    Cvor<Tip> *poc = nullptr, *trenutno = nullptr, *kr = nullptr;
    int broj = 0;
    void praznaLista() const{
        if(poc == nullptr) throw std::range_error("Prazna lista!");
    }
    void dealociraj(){
        auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->sljedeci;
            delete it;
        }poc = nullptr; trenutno = nullptr; kr = nullptr;
    }
    public:
    DvostrukaLista() {}
    DvostrukaLista(const DvostrukaLista<Tip> &l){
        for(auto it = l.poc; it!=nullptr; it = it -> sljedeci){
            dodajIza(it->element);
            sljedeci();
        }pocetak();
    }
    ~DvostrukaLista(){
        auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->sljedeci;
            delete it;
        }
    }
    DvostrukaLista<Tip> &operator= (const DvostrukaLista<Tip> &l){
        if(&l == this) return *this; 
        dealociraj();
        for(auto it = l.poc; it!=nullptr; it = it -> sljedeci){
            dodajIza(it->element);
            sljedeci();
        }pocetak();
        return *this;
    }
    int brojElemenata() const{
        return broj;
    }
    Tip &trenutni() const{
        praznaLista();
        return trenutno->element;
    }
    bool prethodni(){
        praznaLista();
        if(trenutno == poc) return false;
        trenutno = trenutno->prethodni;
        return true;
    }
    bool sljedeci(){
        praznaLista();
        if(trenutno->sljedeci == nullptr) return false;
        trenutno = trenutno->sljedeci;
        return true;
    }
    void pocetak(){
        praznaLista();
        trenutno = poc;
    }
    void kraj(){
        praznaLista();
        trenutno = kr;
    }
    void obrisi(){
        broj--;
        if(trenutno == poc){
            auto temp = poc;
            poc = poc->sljedeci; trenutno = poc;
            delete temp;
            return;
        }
        if(trenutno == kr){
            auto temp = trenutno;
            trenutno = trenutno -> prethodni;
            trenutno->sljedeci = nullptr;
            kr = trenutno;
            delete temp;
            return;
        }
        auto temp = trenutno->sljedeci;
        trenutno->prethodni->sljedeci = trenutno->sljedeci;
        trenutno->sljedeci->prethodni = trenutno->prethodni;
        delete trenutno;
        trenutno = temp;
    }
    void dodajIspred(const Tip &el){
        broj++;
        if(trenutno == nullptr){
            poc = new Cvor<Tip>{el, nullptr, nullptr};
            trenutno = poc;
            kr = poc;
        }
        else if(trenutno == poc){
            auto temp = poc;
            poc = new Cvor<Tip>{el, temp, trenutno};
            trenutno->prethodni = poc;
        }
        else {
            auto temp = new Cvor<Tip>{el, trenutno->prethodni, trenutno};
            trenutno->prethodni->sljedeci = temp;
            trenutno->prethodni = temp;
        }    
    }
    void dodajIza(const Tip &el){
        broj++;
        if(trenutno == nullptr){
            poc = new Cvor<Tip>{el, nullptr, nullptr};
            trenutno = poc;
            kr = poc;
        }
        else if(trenutno -> sljedeci == nullptr){
            trenutno->sljedeci = new Cvor<Tip>{el, trenutno, nullptr};
            kr = trenutno->sljedeci;
        }
        else{
            auto temp = new Cvor<Tip>{el, trenutno, trenutno->sljedeci};
            trenutno->sljedeci->prethodni = temp;
            trenutno->sljedeci = temp;
        }    
    }
    Tip &operator [](int n){
        if(n<0 || n>=brojElemenata()) throw std::range_error("Indeks nije validan");
        int i=0;
        for(auto it = poc; it!=nullptr; it = it->sljedeci){
            if(i++ == n) return it -> element;
        }
        
    }
    const Tip &operator [](int n) const{
        if(n<0 || n>=brojElemenata()) throw std::range_error("Indeks nije validan");
        int i=0;
        for(auto it = poc; it!=nullptr; it = it->sljedeci){
            if(i++ == n) return it -> element;
        }
    }        
        
};

int main(){
    return 0;
}