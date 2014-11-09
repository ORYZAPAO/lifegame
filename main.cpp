#include<iostream>

#include"lifegame.h"

using namespace std;

int main(){
  lifegame::Cell<80,40> lfg;

  ///lfg.Initialize();
  lfg.Preset();

  while(1){
    printf("\033[2J");   // 画面クリア
    printf("\033[0;0H"); // カーソルを(x=0, y=0)移動
    printf("\033[33m");  // 文字色を黄色
    lfg.Print();

    // Wait for Key
    cout  << "Return Key...";
    getchar();

    lfg.NextStep();
  }
}
