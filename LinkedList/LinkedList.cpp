#include <iostream>

template <typename Tip>
struct Cvor{
    Tip element;
    Cvor *pok;
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
class JednostrukaLista : public Lista<Tip>{
    Cvor<Tip> *poc = nullptr, *trenutno = nullptr;
    int broj = 0;
    void praznaLista() const{
        if(poc == nullptr) throw std::range_error("Prazna lista!");
    }
    void dealociraj(){
        auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->pok;
            delete it;
        }
    }
    public:
    JednostrukaLista() {}
    JednostrukaLista(const JednostrukaLista<Tip> &l){
        for(auto it = l.poc; it!=nullptr; it = it -> pok){
            dodajIza(it->element);
            sljedeci();
        }pocetak();
    }
    ~JednostrukaLista(){
        auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->pok;
            delete it;
        }
    }
    JednostrukaLista<Tip> &operator= (const JednostrukaLista<Tip> l){
        dealociraj();
        for(auto it = l.poc; it!=nullptr; it = it -> pok){
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
        for(auto it = poc; it!=nullptr; it = it->pok){
            if(it->pok == trenutno) trenutno = it;
        }return true;
    }
    bool sljedeci(){
        praznaLista();
        if(trenutno->pok == nullptr) return false;
        trenutno = trenutno -> pok;
        return true;
    }
    void pocetak(){
        praznaLista();
        trenutno = poc;
    }
    void kraj(){
        praznaLista();
        for(auto it = poc; it!=nullptr; it = it->pok){
            if(it -> pok == nullptr) trenutno = it;
        }
    }
    void obrisi(){
        praznaLista();
        if(poc == trenutno){
            auto p = poc;
            poc = poc -> pok;
            trenutno = poc;
            delete p;
        }
        for(auto it = poc; it!=nullptr; it = it -> pok){
            if(it -> pok == trenutno){
                it->pok = trenutno->pok;
                delete trenutno;
                if(it->pok == nullptr) trenutno = it;
                else trenutno = it->pok;
                break;
            }
        }broj--;
    }
    void dodajIspred(const Tip &el){
        if(trenutno == nullptr){
            poc = new Cvor<Tip>{el, nullptr};
            trenutno = poc;
        }
        else if(trenutno == poc){
            poc = new Cvor<Tip>{el, trenutno};
        }
        else {
            for(auto it = poc; it!=nullptr; it = it -> pok){
                if(it -> pok == trenutno){
                    auto temp = it -> pok;
                    it -> pok = new Cvor<Tip>{el, temp};
                    break;
                }
            }
        }broj++;    
    }
    void dodajIza(const Tip &el){
        if(trenutno == nullptr){
            poc = new Cvor<Tip>{el, nullptr};
            trenutno = poc;
        }
        else if(trenutno -> pok == nullptr){
            trenutno->pok = new Cvor<Tip>{el, nullptr};
        }
        else{
            auto temp = trenutno -> pok;
            trenutno -> pok = new Cvor<Tip>{el, temp};
        }broj++;   
    }
    Tip &operator [](int n){
        if(n<0 || n>=brojElemenata()) throw std::range_error("Indeks nije validan");
        int i = 0;
        for(auto it = poc; it!=nullptr; it = it -> pok){
            if(i++ == n) return it->element;
        }
    }
    const Tip &operator [](int n) const{
        if(n<0 || n>=brojElemenata()) throw std::range_error("Indeks nije validan");
        int i = 0;
        for(auto it = poc; it!=nullptr; it = it -> pok){
            if(i++ == n) return it->element;
        }
    }
};

int main(){
    return 0;
}