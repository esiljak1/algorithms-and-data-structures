#include <iostream>

template <typename Tip>
struct Cvor{
    Tip element;
    Cvor *prethodni, *sljedeci;
};

template <typename Tip>
class DvostraniRed{
  Cvor<Tip> *poc, *kr;
  int br;
  
  void prazanRed(){
      if(br == 0) throw std::range_error("Red je prazan!");
  }
  public:
  DvostraniRed() : poc(nullptr), kr(nullptr), br(0) {}
  ~DvostraniRed(){
      auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->sljedeci;
            delete it;
        }
  }
  DvostraniRed(const DvostraniRed<Tip> &dr){
       poc = nullptr; kr = nullptr; br = 0;
      for(auto it = dr.poc; it != nullptr; it = it -> sljedeci){
          staviNaVrh(it -> element);
      }br = dr.br;
  }
  DvostraniRed<Tip> &operator =(const DvostraniRed<Tip> &dr){
      if(&dr == this) return *this;
      brisi();
      for(auto it = dr.poc; it != nullptr; it = it -> sljedeci){
          staviNaVrh(it -> element);
      }br = dr.br;
      return *this;
  }
  
  void brisi(){
      auto it = poc, temp = poc;
        while(temp!=nullptr){
            it = temp;
            temp=it->sljedeci;
            delete it;
        }br = 0;
        poc = nullptr; kr = nullptr;
  }
  int brojElemenata(){
      return br;
  }
  void staviNaVrh(const Tip &el){
      if(poc == nullptr && kr == nullptr){
          kr = new Cvor<Tip>{el, nullptr, nullptr};
          poc = kr;
      }else{
          auto temp = kr;
          kr = new Cvor<Tip>{el, temp, nullptr};
          temp -> sljedeci = kr;
      }br++;
  }
  Tip skiniSaVrha(){
      prazanRed();
      Tip ret = kr->element;
      auto temp = kr;
      kr = kr -> prethodni;
      delete temp; 
      if(kr != nullptr) kr -> sljedeci = nullptr;
      else poc = nullptr;
      br--;
      return ret;
  }
  void staviNaCelo(const Tip &el){
      if(poc == nullptr && kr == nullptr){
          poc = new Cvor<Tip>{el, nullptr, nullptr};
          kr = poc;
      }else{
          auto temp = poc;
          poc = new Cvor<Tip>{el, nullptr, temp};
          temp -> prethodni = poc;
      }br++;
  }
  Tip skiniSaCela(){
      prazanRed();
      Tip ret = poc -> element;
      auto temp = poc;
      poc = poc -> sljedeci;
      delete temp; 
      if(poc != nullptr) poc -> prethodni = nullptr;
      else kr = nullptr;
      br--;
      return ret;
  }
  Tip &vrh(){
      prazanRed();
      return kr -> element;
  }
  Tip &celo(){
      prazanRed();
      return poc -> element;
  }
  
};

int main(){
    return 0;
}