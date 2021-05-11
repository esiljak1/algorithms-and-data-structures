#include <iostream>

int fib2_0(int n, int pretprosli = 0, int prosli = 1){
    if(n == 0) return pretprosli;
    else if(n == 1) return prosli;
    
    return fib2_0(n - 1, prosli, pretprosli + prosli);
}

int nzd(int x, int y){
    if(y == 0) return x;
    
    return nzd(y, x%y);
}

int main(){
    return 0;
}