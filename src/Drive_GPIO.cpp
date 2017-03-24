#include <stdio.h>
#include "Pin.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void matar(pid_t pid){  
        kill(pid,SIGTERM);
}

int main(int argc, char *argv[]){
  //DECLARANDO VARIAVEIS
  string url="/proc/meminfo";
  int n, i;
  int mem[2];
  int time;
  int memoria_consumida;
  bool proc_ex = false;
  pid_t id; 

  Pin led_verde("P9_11", "out", 0);
  Pin led_amarelo("P9_13", "out", 0);
  Pin led_vermelho("P9_15", "out", 0);
  Pin botao("P9_42", "in", 0);
  while(true) {
    if (!proc_ex) {
      proc_ex = true;
      id = fork();
    }

    if (id == 0) {
      int num = 1;
      while (1) {             
        malloc(num); 
        num = num + num;
      }
    }

    ifstream file("/proc/meminfo");
    string s,t;     
    file>>s;
    file>>mem[0];
    file>>t;
    file>>s;
    file>>mem[1];
    memoria_consumida = 100 - ((mem[1])*100)/mem[0];
    printf("%d porcento da memoria ocupada\n", memoria_consumida );
    printf("\n");

    if (memoria_consumida <= 25) {
      led_verde.setValue(1);
      led_amarelo.setValue(0);
      led_vermelho.setValue(0);
    } else if (memoria_consumida <= 50)  {
      led_verde.setValue(0);
      led_amarelo.setValue(1);
      led_vermelho.setValue(0);
    } else if (memoria_consumida <= 75) {
      led_verde.setValue(0);
      led_amarelo.setValue(0);
      led_vermelho.setValue(1);
    } else {
        while (botao.getValue() == 0) {
          led_verde.setValue(1);
          led_amarelo.setValue(1);
          led_vermelho.setValue(1);
          time = clock();
          while((clock() - time) < 10000){
          }
          led_verde.setValue(0);
          led_amarelo.setValue(0);
          led_vermelho.setValue(0);
          time = clock();
          while((clock() - time) < 10000){
          }
        }
        matar(id);
        sleep(3);
        proc_ex = false;          
    }
        
    if (botao.getValue() == 1) {
      matar(id);
      led_verde.setValue(0);
      led_amarelo.setValue(0);
      led_vermelho.setValue(0);
      exit(1); 
    }
  }
return 0;
}

