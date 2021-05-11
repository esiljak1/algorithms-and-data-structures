#include <iostream>

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
class NizLista : public Lista<Tip>{
    Tip **p = nullptr;
    int velicina, trenutno, kapacitet;
    void praznaLista() const{
        if(velicina == 0) throw std::range_error("Prazna lista!");
    }
    void dealociraj(int n){
        for(int i = 0; i < n; i++) delete p[i];
            delete [] p;
    }
    public:
    NizLista() : trenutno(0), velicina(0), kapacitet(1000){
        p = new Tip*[kapacitet]{};
    }
    ~NizLista(){
        for(int i=0; i<velicina; i++){
            if(p[i] != nullptr) 
                delete p[i];
            p[i] = nullptr;
        }
        delete [] p; velicina = 0;
    }
    NizLista(const NizLista<Tip> &niz){
        kapacitet = niz.kapacitet; trenutno = niz.trenutno;
        velicina = niz.velicina;
        p = new Tip*[kapacitet];
        for(int i=0; i<velicina; i++) p[i] = new Tip(*niz.p[i]);
    }
    NizLista<Tip> &operator = (const NizLista<Tip> &niz){
        for(int i=0; i<velicina; i++) delete p[i];
        delete [] p;
        kapacitet = niz.kapacitet; trenutno = niz.trenutno;
        velicina = niz.velicina;
        p = new Tip*[kapacitet];
        for(int i=0; i<velicina; i++) p[i] = new Tip(*niz.p[i]);
        return *this;
    }
    int brojElemenata() const{
        return velicina;
    }
    Tip &trenutni() const{
        praznaLista();
        return *p[trenutno];
    }
    bool prethodni(){
        praznaLista();
        if(trenutno == 0) return false;
        trenutno--;
        return true;
    }
    bool sljedeci(){
        praznaLista();
        if(trenutno == velicina - 1) return false;
        trenutno++;
        return true;
    }
    void pocetak(){
        praznaLista();
        trenutno = 0;
    }
    void kraj(){
        praznaLista();
        trenutno = velicina - 1;
    }
    void obrisi(){
        praznaLista();
        if(trenutno == velicina - 1){
            delete p[trenutno]; velicina--;
            if(trenutno != 0) trenutno--; 
            return;
        }
        delete p[trenutno];
        for(int i = trenutno; i < velicina - 1; i++) p[i] = p[i + 1];
        velicina--;
    }
    void dodajIspred(const Tip &el){
        if(velicina + 1 == kapacitet){
            kapacitet+=1000;
            velicina++;
            auto temp = new Tip *[kapacitet];
            bool uslov = false;
            for(int i=0; i<velicina; i++){
                if(i == trenutno){
                    uslov = true;
                    temp[i] = new Tip(el);
                }else if(uslov){
                    temp[i] = p[i - 1];
                }else{
                    temp[i] = p[i];
                }
            }
            delete [] p;
            p = temp;
        }else{
            if(velicina != 0){
                for(int i=velicina; i>trenutno; i--){
                    if(i != velicina) delete p[i];
                    p[i] = p[i - 1];
                } 
            }
            velicina++;
            //delete p[trenutno];
            p[trenutno] = new Tip(el);
        }
        if(velicina != 1) trenutno++;
    }
    void dodajIza(const Tip &el){
        if(velicina + 1 == kapacitet){
            kapacitet+=1000;
            velicina++;
            auto temp = new Tip *[kapacitet];
            bool uslov = false;
            for(int i=0; i<velicina; i++){
                if(i == trenutno + 1){
                    uslov = true;
                    temp[i] = new Tip(el);
                }else if(uslov){
                    temp[i] = p[i - 1];
                }else{
                    temp[i] = p[i];
                }
            }
            delete [] p;
            p = temp;
        }else{
            for(int i = velicina; i > trenutno + 1; i--){
                delete p[i];
                p[i] = new Tip(*p[i - 1]);
            }
            if(velicina == 0){
                p[velicina] = new Tip(el);
            }else{
                delete p[trenutno + 1];
                p[trenutno + 1] = new Tip(el);
            }
            velicina++;
        }
    }
    Tip &operator [](int n){
        if(n < 0 || n >= velicina) throw std::range_error("Indeks izlazi izvan opsega niza");
        return *p[n];
    }
    const Tip &operator [](int n) const {
        if(n < 0 || n >= velicina) throw std::range_error("Indeks izlazi izvan opsega niza");
        return *p[n];
    }
    
};

int main(){

    return 0;
}