#include <iostream>

template <typename Tip>
class Red{
    Tip *p = nullptr;
    int poc, kr, kapacitet = 1000, br = 0;
    void prazanRed(){
        if(poc == -1 && kr == -1) throw std::range_error("Red je prazan");
    }
    void dealociraj(){
        delete [] p;
        p = nullptr;
        kapacitet = 1000;
        br = 0;
    }
    public:
    Red() : p(nullptr), poc(-1), kr(-1), kapacitet(1000){
        p = new Tip[kapacitet];
    }
    ~Red(){
        delete [] p;
        p = nullptr;
        kapacitet = 1000;
        br = 0;
    }
    Red(const Red<Tip> &r){
        p = new Tip[r.kapacitet];
        if(r.kr < r.poc){
            int zadnji = 0;
            for(int i = 0; r.poc + i < r.kapacitet; i++){
                p[i] = r.p[i + r.poc];
                if(r.poc + i + 1 == r.kapacitet) zadnji = i + 1;
            }
            for(int i = 0; i <= kr; i++) p[zadnji + i] = r.p[i];
            poc = 0;
            kr = zadnji + kr;
            br = r.br;
            kapacitet = r.kapacitet;
        }else{
            poc = r.poc;
            kr = r.kr;
            kapacitet = r.kapacitet;
            br = r.br;
            for(int i = poc; i <= kr; i++) p[i] = r.p[i];
        }
    }
    Red<Tip> &operator =(const Red<Tip> &r){
        if(r.p == p) return *this;
        dealociraj();
        p = new Tip[r.kapacitet];
        if(r.kr < r.poc){
            int zadnji = 0;
            for(int i = 0; r.poc + i < r.kapacitet; i++){
                p[i] = r.p[i + r.poc];
                if(r.poc + i + 1 == r.kapacitet) zadnji = i + 1;
            }
            for(int i = 0; i <= kr; i++) p[zadnji + i] = r.p[i];
            poc = 0;
            kr = zadnji + kr;
            br = r.br;
            kapacitet = r.kapacitet;
        }else{
            poc = r.poc;
            kr = r.kr;
            kapacitet = r.kapacitet;
            br = r.br;
            for(int i = poc; i <= kr; i++) p[i] = r.p[i];
        }
        return *this;
    }
    void brisi(){
        poc = -1;
        kr = -1;
        br = 0;
    }
    void stavi(const Tip &el){
        if(poc == -1) poc = 0;
        if(kr + 1 == kapacitet && poc==0){
            kapacitet*=2;
            auto temp = new Tip[kapacitet];
            for(int i=0; i<=kr; i++) temp[i] = p[i];
            delete [] p;
            p = temp;
        }else if(kr + 1 == kapacitet && poc != 0){
            kr = -1;
        }else if(kr < poc && kr + 1 == poc && kr != -1){
                kapacitet*=2;
                auto temp = new Tip[kapacitet];
                for(int i=0; i < kapacitet/2 - poc; i++) temp[i] = p[poc + i];
                for(int i=0; i<=kr; i++) temp[kapacitet/2 - poc + i] = p[i];
                delete [] p;
                p = temp;
                kr = kapacitet/2 - poc + kr - 1; poc = 0;
        } kr++;
        br++;
        p[kr] = el;
    }
    Tip skini(){
        prazanRed();
        br--;
        if(poc == kr){
            Tip temp = p[poc];
            poc = -1; kr = -1;
            return temp;
        }return p[poc++];
    }
    Tip &celo(){
        prazanRed();
        return p[poc];
    }
    int brojElemenata() const{
        return br;
    }
};

int main(){
    return 0;
}