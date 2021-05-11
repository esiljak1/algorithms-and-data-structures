#include <iostream>
#include <functional>
#include <vector>
#include <list>

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
class HashMapaLan : public Mapa<TipKljuc,TipVrijednost> {
    private:
        std::vector<std::list<Par<TipKljuc, TipVrijednost>>> mapa;
        int broj = 0;
        int kapacitet = 1000;
        std::function<unsigned int(TipKljuc, unsigned int)> f;
    public:
        HashMapaLan(){
            mapa.resize(1000);
        }
        int brojElemenata() const { 
            return broj; 
        }
        TipVrijednost &operator[](const TipKljuc &kljuc){
            int ind = f(kljuc, kapacitet);
            auto it = mapa[ind].begin();
            while(it != mapa[ind].end()){
                if(it -> kljuc == kljuc){
                    return it -> vrijednost;
                }else if(it -> kljuc > kljuc){
                    break;
                }it++;
            }
            it = mapa[ind].insert(it, Par<TipKljuc, TipVrijednost>{kljuc, TipVrijednost()});
            broj++;
            return it -> vrijednost;
        }
        const TipVrijednost operator[](const TipKljuc &kljuc) const{
            int ind = f(kljuc, kapacitet);
            auto it = mapa[ind].begin();
            while(it != mapa[ind].end()){
                if(it -> kljuc == kljuc){
                    return it -> vrijednost;
                }else if(it -> kljuc > kljuc){
                    it--;
                    break;
                }it++;
            }return TipVrijednost();
        }
        void obrisi(){
            for(int i = 0; i < mapa.size(); i++){
                mapa[i].clear();
            }
            broj = 0;
        }
        void obrisi(const TipKljuc &kljuc){
            int ind = f(kljuc, kapacitet);
            auto it = mapa[ind].begin();
            while(it != mapa[ind].end()){
                if(it -> kljuc == kljuc){
                    mapa[ind].erase(it);
                    broj--;
                    return;
                }if(it -> kljuc > kljuc) break;
                it++;
            }
            throw "";
        }
        void definisiHashFunkciju(std::function<unsigned int(TipKljuc, unsigned int)> fun) {
            f = fun; 
        }
};

int main(){
    return 0;
}