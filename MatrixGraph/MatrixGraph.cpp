#include <iostream>
#include <vector>
#include <queue>

template <typename TipOznake>
class Grana;

template <typename TipOznake>
class Cvor;

template <typename TipOznake>
class GranaIterator;

template <typename Tip>
class UsmjereniGraf{
    public:
    UsmjereniGraf(){}
    UsmjereniGraf(int n){}
    virtual ~UsmjereniGraf(){}
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int n) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina = 0) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina) = 0;
    virtual float dajTezinuGrane(int polazni, int dolazni) = 0;
    virtual bool postojiGrana(int polazni, int dolazni) = 0;
    virtual void postaviOznakuCvora(int broj, Tip oznaka) = 0;
    virtual Tip dajOznakuCvora(int broj) = 0;
    virtual void postaviOznakuGrane(int polazni, int dolazni, Tip oznaka) = 0;
    virtual Tip dajOznakuGrane(int polazni, int dolazni) = 0;
    virtual Grana<Tip> dajGranu(int polazni, int dolazni) = 0;
    virtual Cvor<Tip> dajCvor(int broj) = 0;
    virtual GranaIterator<Tip> dajGranePocetak() = 0;
    virtual GranaIterator<Tip> dajGraneKraj() = 0;
};

template <typename Tip>
class Grana{
    int polazni, dolazni;
    UsmjereniGraf<Tip> *g;
    public:
    Grana(UsmjereniGraf<Tip> *gr, int polaz, int dolaz){
        g = gr;
        polazni = polaz;
        dolazni = dolaz;
    }
    float dajTezinu() const{
        return g -> dajTezinuGrane(polazni, dolazni);
    }
    void postaviTezinu(float tez){
       g -> postaviTezinuGrane(polazni, dolazni, tez);
    }
    Tip dajOznaku() const{
        return g -> dajOznakuGrane(polazni, dolazni);
    }
    void postaviOznaku(Tip oz){
        g -> postaviOznakuGrane(polazni, dolazni, oz);
    }
    Cvor<Tip> dajPolazniCvor() const{
        return g -> dajCvor(polazni);
    }
    Cvor<Tip> dajDolazniCvor() const{
        return g -> dajCvor(dolazni);
    }
    
};

template <typename Tip>
class Cvor{
    int broj;
    Tip oznaka = Tip();
    UsmjereniGraf<Tip> *graf;
    public:
    Cvor(UsmjereniGraf<Tip> *g, int br){
        graf = g;
        broj = br;
    }
    bool operator ==(const Cvor<Tip> &c){
        return graf == c.graf && broj == c.broj;
    }
    Tip dajOznaku() const{
        return (graf -> dajOznakuCvora(broj));
    }
    void postaviOznaku(Tip oz){
        graf -> postaviOznakuCvora(broj, oz);
    }
    int dajRedniBroj() const{
        return broj;
    }
};

template <typename Tip>
class GranaIterator {
    UsmjereniGraf<Tip> *g;
    int polazni, dolazni;
    public:
    GranaIterator(UsmjereniGraf<Tip> *gr, int pol, int dol) : g(gr), polazni(pol), dolazni(dol) {}
    Grana<Tip> operator*(){
        return g -> dajGranu(polazni, dolazni);
    }
    bool operator== (const GranaIterator<Tip> &iter) const{
        return g == iter.g && polazni == iter.polazni && dolazni == iter.dolazni;
    }
    bool operator!= (const GranaIterator<Tip> &iter) const{
        return !(*this == iter);
    }
    GranaIterator &operator ++(){
        while(1){
            if(dolazni >= g -> dajBrojCvorova()){
                dolazni = -1;
                polazni++;
            }
            dolazni++;
            if(polazni >= g -> dajBrojCvorova()) break;
            if(dolazni == g -> dajBrojCvorova()) continue;
            if(g -> postojiGrana(polazni, dolazni)) return *this;
        }return *this;
    }
    GranaIterator operator ++(int){
        GranaIterator<Tip> ret = *this;
        while(1){
            bool uslov = true;
            if(dolazni > g -> dajBrojCvorova()){
                dolazni = 0;
                polazni++;
                uslov = false;
            }if(polazni > g -> dajBrojCvorova()) throw "Greska";
            if(g -> postojiGrana(polazni, dolazni)) return ret;
        }
    }
};

template<typename Tip>
class MatricaGraf : public UsmjereniGraf<Tip>{
    std::vector<std::vector<float>> v;
    std::vector<Tip> cvoroviOz;
    std::vector<std::vector<Tip>> graneOz;
    
    void izuzetak(int prvi, int drugi){
        try{
            v.at(prvi).at(drugi);
        }catch(...){
            throw std::range_error("Ne valja indeks");
        }
    }
    
    public:
    MatricaGraf(){}
    MatricaGraf<Tip>(int n){
        v = std::vector<std::vector<float>>(n, std::vector<float>(n, -1));
        cvoroviOz = std::vector<Tip>(n, Tip());
        graneOz = std::vector<std::vector<Tip>>(n, std::vector<Tip>(n, Tip()));
    }
    ~MatricaGraf(){}
    int dajBrojCvorova() const{
        return cvoroviOz.size();
    }
    void postaviBrojCvorova(int n){
        v = std::vector<std::vector<float>>(n, std::vector<float>(n, -1));
        cvoroviOz = std::vector<Tip>(n, Tip());
        graneOz = std::vector<std::vector<Tip>>(n, std::vector<Tip>(n, Tip()));
    }
    void dodajGranu(int polazni, int dolazni, float tezina = 0){
        izuzetak(polazni, dolazni);
        v[polazni][dolazni] = tezina;
    }
    void obrisiGranu(int polazni, int dolazni){
        izuzetak(polazni, dolazni);
        v[polazni][dolazni] = -1;
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina = 0){
        izuzetak(polazni, dolazni);
        if(tezina < 0) throw "";
        v[polazni][dolazni] = tezina;
    }
    float dajTezinuGrane(int polazni, int dolazni){
        izuzetak(polazni, dolazni);
        return v[polazni][dolazni];
    }
    bool postojiGrana(int polazni, int dolazni){
        izuzetak(polazni, dolazni);
        return v[polazni][dolazni] != -1;
    }
    void postaviOznakuCvora(int broj, Tip oznaka){
        izuzetak(broj, broj);
        cvoroviOz[broj] = oznaka;
    }
    Tip dajOznakuCvora(int broj){
        izuzetak(broj, broj);
        return cvoroviOz[broj];
    }
    void postaviOznakuGrane(int polazni, int dolazni, Tip oznaka){
        izuzetak(polazni, dolazni);
        graneOz[polazni][dolazni] = oznaka;
    }
    Tip dajOznakuGrane(int polazni, int dolazni){
        izuzetak(polazni, dolazni);
        return graneOz[polazni][dolazni];
    }
    Cvor<Tip> dajCvor(int broj){
        izuzetak(broj, broj);
        return Cvor<Tip>(this, broj);
    }
    Grana<Tip> dajGranu(int polazni, int dolazni){
        izuzetak(polazni, dolazni);
        return Grana<Tip>(this, polazni, dolazni);
    }
    GranaIterator<Tip> dajGranePocetak(){
        return ++GranaIterator<Tip>(this, 0, -1);
    }
    GranaIterator<Tip> dajGraneKraj(){
        return GranaIterator<Tip>(this, cvoroviOz.size(), 0);
    }
      
};
template <typename Tip>
void bfs(UsmjereniGraf<Tip> *g, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> pocetni){
    obilazak.push_back(pocetni);
    std::queue<Cvor<Tip>> red;
    std::vector<bool> iskoristen (g -> dajBrojCvorova(), false);
    iskoristen[pocetni.dajRedniBroj()];
    red.push(pocetni);
    while(!red.empty()){
        Cvor<Tip> temp = red.front();
        red.pop();
        for(GranaIterator<Tip> it = g -> dajGranePocetak(); it != g -> dajGraneKraj(); ++it){
            if((*it).dajPolazniCvor() == temp && iskoristen[(*it).dajDolazniCvor().dajRedniBroj()] == false){
                red.push((*it).dajDolazniCvor());
                iskoristen[(*it).dajDolazniCvor().dajRedniBroj()] = true;
                obilazak.push_back((*it).dajDolazniCvor()); 
            }
        }
    }
}

template <typename Tip>
void dfs(UsmjereniGraf<Tip> *g, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> pocetni){
    obilazak.push_back(pocetni);
    for(GranaIterator<Tip> it = g -> dajGranePocetak(); it != g -> dajGraneKraj(); ++it){
        Cvor<Tip> temp = (*it).dajDolazniCvor();
        if((*it).dajPolazniCvor() == pocetni){
            bool nema = true;
            for(int i = 0; i < obilazak.size(); i++){
                if(obilazak[i] == temp) nema = false;
            }
            if(!nema) continue;
            dfs(g, obilazak, temp);
        }
    }
}

int main() {
    
    return 0;
}