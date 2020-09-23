#include<stdio.h>
#include"header.h"

 // Работает  HELP !!!!!!!!!!!!!!!!!!! ура!

void helpfunc() // функция выводит в консоль краткую справку по параметрам
{
  printf("   --ip [IPv4]                             default = 192.168.10.1\n");
  printf("   -p / --port                             default = 502\n");
  printf("   -a / --addr                             default = 1\n");
  printf("   -r / --reg                              default = 0\n");
  printf("   -m / --mode [single | loop | trig]      default = single \n");
  printf("   --log [Namefile]\n");
  printf("   -i / --interval [ms]\n");
  printf("   -t / --timeout  [ms]                    default = 1000\n");
  printf("   --hex                                   default = dec\n"); 
  printf("   -h / --help\n");
} 
