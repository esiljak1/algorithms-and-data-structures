#include <iostream>

template <typename Tip>
class Stek{
  Tip *stek = nullptr;
  int top = -1, kapacitet = 1000;
  void prazanStek(){
      if(top == -1) throw std::range_error("Stek je prazan");
  }
  void dealociraj(){
      delete [] stek;
      stek = nullptr;
  }
  public:
  Stek() : stek(nullptr), top(-1), kapacitet(1000){
      stek = new Tip[kapacitet]{};
  }
  ~Stek(){
      delete [] stek;
      stek = nullptr;
      top = -1;
      kapacitet = 1000;
  }
  Stek(const Stek<Tip> &s){
      stek = new Tip[s.kapacitet]{};
      kapacitet = s.kapacitet;
      top = s.top;
      for(int i=0; i<=top; i++) stek[i] = s.stek[i];
  }
  Stek<Tip> &operator =(const Stek<Tip> &s){
      if(s.stek == stek) return *this; 
      dealociraj();
      stek = new Tip[s.kapacitet]{};
      kapacitet = s.kapacitet;
      top = s.top;
      for(int i=0; i<=top; i++) stek[i] = s.stek[i];
      return *this;
  }
  void brisi(){
      top = -1;
  }
  void stavi(const Tip &el){
      if(++top == kapacitet){
          kapacitet+=1000;
          auto temp = new Tip[kapacitet]{};
          for(int i=0; i<top; i++) temp[i] = stek[i];
          delete [] stek;
          stek = temp;
      }
      stek[top] = el;
  }
  Tip skini(){
      prazanStek();
      return stek[top--];
  }
  Tip &vrh(){
      prazanStek();
      return stek[top];
  }
  int brojElemenata() const{
      return top + 1;
  }
};

int main(){
    return 0;
}