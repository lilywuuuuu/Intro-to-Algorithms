#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int fake(vector<int> coin, int p1, int p2, int p3, int p4, int size){
    long long int pile1 = 0, pile2 = 0, pile3 = 0;
    int _size = floor(size/3);
    int __size = floor(_size/3);
    for(int i=p1; i<p2; i++) pile1 += coin[i];
    for(int i=p2; i<p3; i++) pile2 += coin[i];
    for(int i=p3; i<p4; i++) pile3 += coin[i];
    
    // if fake coin appears outside the 3 piles
    if(pile1 == pile2 && pile1 == pile3 && pile2 == pile3){
        if(size%3 == 1) return p4;
        else {
            if(coin[p1] == coin[p4]) return p4 + 1;
            else return p4;
        }
    }
    // if fake coin appears in pile 1
    else if(pile2 == pile3) {
        if(__size == 0){
            if(_size == 1) return p1;
            else{
                if(coin[p2] == coin[p1]) return p1 + 1;
                else return p1;
            }
        }
        return fake(coin, p1, p1 + __size, p1 + __size*2, p1 + __size*3, _size);
    }
    else if(pile1 == pile3) {
        if(__size == 0){
            if(_size == 1) return p2;
            else{
                if(coin[p1] == coin[p2]) return p2 + 1;
                else return p2;
            }
        }
        return fake(coin, p2, p2 + __size, p2 + __size*2, p2 + __size*3, _size);
    }
    else if(pile1 == pile2) {
        if(__size == 0){
            if(_size == 1) return p3;
            else{
                if(coin[p1] == coin[p3]) return p3 + 1;
                else return p3;
            }
        }
        return fake(coin, p3, p3 + __size, p3 + __size*2, p3 + __size*3, _size);
    }
    return 0;
}

int main(void){
    int n;
    while(cin >> n){
        vector<int> coin;
        for(int i=0; i<n; i++){
            int tmp;
            cin >> tmp;
            coin.push_back(tmp);
        }
        int size = coin.size();
        int psize = floor(coin.size()/3);
        int index = fake(coin, 0, psize, psize*2, psize*3, size);
        cout << index << "\n";
    }
    
    return 0;
}
