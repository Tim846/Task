/* программа для считывания параметров из командной строки (к.с.) принимает на вход строку произвольной длинны, делит её на слова и группирует принятые параметры по символам указателям */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h" // заголовочный файл, описывающий функции

#define DL 35 // длина строки параметров. Думаю, этого достаточно
#define MAXSIMV 200 // максимальное количество символов строки параметров. Максимум по минимуму выйдет 124 символа с пробелами (пусть будет 200 на 17.09)

void helpfunc(); // функция выводит в консоль краткую справку по параметрам

int main()
{
    int c, i, a, b, k;
//    char line[MAXSIMV];       // строка для записи парамеров 
//    fgets(line, MAXSIMV, stdin);// считывает строку в line длинной MAXSIMV из к.с.

    char line[]="-h --port 503 -a 2 --reg 1 --count 3 -i 3000 --timeout 3000 --hex --ip 192.168.10.10 --mode loop"; 
    //--log /home/tim/Документы/1/1.txt";  // пока будем вводить строку внутри программы
   
    char ip[DL], log[DL];       // параметры по умолчанию
    char mode[] = "single";   //  в строки записанны слова. Слова сравниваются с параметрами, полученными из командной строки
    
    char str_ip1[]="--ip";    char str_ip2[]="--ip";      //  записанны в строках для более простой замены
    char str_p1[]="-p";       char str_p2[]="--port";          char str_p3[]="port";
    char str_a1[]="-a";       char str_a2[]="--addr";          char str_a3[]="addr";
    char str_r1[]="-r";       char str_r2[]="--reg";           char str_r3[]="reg";
    char str_c1[]="-c";       char str_c2[]="--count";         char str_c3[]="count";
    char str_m1[]="-m";       char str_m2[]="--mode";          char str_m3[]="mode";
    char str_log1[]="--log";  char str_log2[]="--log";
    char str_in1[]="-i";      char str_in2[]="--interval";     char str_in3[]="interval";
    char str_t1[]="-t";       char str_t2[]="--timeout";       char str_t3[]="timeout";
    char str_hex1[]="--hex";
    char str_help1[]="-h";    char str_help2[]="--help";        
    int port, addr, reg, count, interval, timeout, hex;
    port = 502;        //  порт default
    addr = 1;          //  Модбас адрес устройства
    reg = 0;           //  номер регистра
    count = 1;         //  количество регистров
    timeout = 1000;    //  таймаут ожидания ответа
//     interval = 0;      //  временной интервал между запросами 
    hex=0;             //  результат dec в десятичной по умолчанию. Работает как триггер?
    
    
    printf("default p %3i adr %2i reg %2i mode %s c %2i t %i hex %i\n", port, addr, reg, mode, count, timeout, hex ); // вывод значений по умолчанию
    printf("Вы ввели\n"); 
    puts(line); // выводим "введённую" строку
    
// выделю парсер командной строки в отдельную функцию. но сначала его напишу(не выделю. так не работает)
    char param[20][DL];                 // массив для записи параметров
    
    char *ukazat;                       // инициализация указателя
    ukazat = strtok (line, " ");        /* ukaz-указатель на первое вхождение разделителя "-" в строке line */
//    printf("Разделение введённой строки на слова\n");
    i=0;                                // обнулили счётчик
//  while ((ukazat = strtok (line, " ")) != NULL){    // разделяем строку на слова   
    while (ukazat != NULL){             // разделяем строку на слова
        strcpy(param[i],ukazat);        // копируем выделенные слова в массив
        i++;                            // переходим в следующую ячейку
        ukazat = strtok (NULL, " ");    // ищем следующий символ разделитель и получаем на него указатель   
     }
//     вывод строки , поделенной на слова
//        for (a = 0;a < i;a +=1){
//              printf("%s\n",param[a]);       // вывод строки, поделенной на слова
//         }
//       printf("i=%i\n",i);
      /* В массиве записанны в ячейках последовательно название параметра а следом значение параметра, если оно есть ( hex и help ? ). Сравниваю содержимое ячеек с названием параметра. Если совпало, то в следующей ячейке лежит значение. Его запоминаю и применяю. 
     *
     */
     for(a = 0; a < i; ){
         
         if (strcmp(param[a], str_help1) == 0 || strcmp(param[a], str_help2) == 0 ){  // help
//             helpfunc();            // вызываем функцию "help"
            a=a+1;
            continue;               // значение обнаружено. начинаем новую итерацию цикла
            }
            
         if (strcmp(param[a], str_p1) == 0||strcmp(param[a], str_p2) == 0){           //  порт
            port = atoi(param[a+1]);  // записываем порт                 printf("Порт!  %i\n", port);
            a=a+2;
            continue;               // значение обнаружено. 
            }  
         if (strcmp(param[a], str_a1) == 0||strcmp(param[a], str_a2) == 0){           // адрес
            addr = atoi(param[a+1]); // записываем адрес                     printf("Адрес! %i\n",addr);
            a=a+2;
            continue;               // значение обнаружено
            }
         if (strcmp(param[a], str_r1) == 0||strcmp(param[a], str_r2) == 0){           //  регистры
            reg = atoi(param[a+1]); // запись номер регистра               printf("Регистр! %i\n",reg);
            a=a+2;
            continue;               // значение обнаружено
            }
         if ((strcmp(param[a], str_c1) == 0)||(strcmp(param[a], str_c2) == 0)){       // количество регистров
            count = atoi(param[a+1]); // записываем количество регистров                printf("Количество регистров  %i\n",count);
            a=a+2;
            continue;               // значение обнаружено
            } 
         if (strcmp(param[a], str_in1) == 0||strcmp(param[a], str_in2) == 0){         // интервал
            interval = atoi(param[a+1]); // записываем интервал              printf("Интервал = %i\n", interval);  
            a=a+2;
            continue;               // значение обнаружено
            }
         if (strcmp(param[a], str_t1) == 0||strcmp(param[a], str_t2) == 0){           // таймаут
            timeout = atoi(param[a+1]); // записываем интервал                           printf("Таймаут = %i\n", timeout);
            a=a+2;
            continue;               // значение обнаружено
            }
         if (strcmp(param[a], str_hex1) == 0){                                         //  система счисления
            hex=1;                     // записываем значение                            printf("Некс \n");
            a=a+1;
            continue;               // значение обнаружено
            }
         if (strcmp(param[a], str_ip1) == 0){                                          // IP          
            strcpy(ip,param[a+1]);  // копируем значение ip в память        записываем IP адресс               printf("IP= %s\n", ip);
            a=a+2;
            continue;               // значение обнаружено
            }  
         if (strcmp(param[a], str_m1) == 0||strcmp(param[a], str_m2) == 0){           //  режим
            strcpy(mode,param[a+1]);  // копируем значение        записываем режим в память               printf("mode= %s\n", mode);
            a=a+2;
            continue;               // значение обнаружено
            }
         if (strcmp(param[a], str_log1) == 0){                                         // файл для записи
            strcpy(log,param[a+1]);  // копируем название файла в память        записываем адрес            printf("log= %s\n", log);
            a=a+2;
            continue;               // параметр распознан
            }
         else {                                                                       // ошибочный ввод
            printf("Введён неправильный параметр %s", param[a]); 
            printf(" Произошла ошибка. Введите параметры ещё раз, или вызовите помощь -h\n");    // ошибка обнаружена. завершаем цикл и сообщаем об ошибке
//             printf("default p %3i adr %2i reg %2i mode %s c %2i int %4i t %i hex %i\n", port, addr, reg, mode, count, interval, timeout, hex );
             break; // 
//             a++;
//             continue;
            }
        }
//      printf("default p %3i adr %2i reg %2i mode %s c %2i int %4i t %i hex %i\n", port, addr, reg, mode, count, interval, timeout, hex );
    return 0;
}

/*
               Время
//#include<asm/io.h> //если возникнут проблемы с отладкой, gcc -g -o
#include<stdio.h>
#include<time.h>

int main()
{
    int c;
    while ((c=getchar()) != EOF && c != '\n'){
        
    } 
    printf("Привет, мир!\n");
//     запрс времени, даты. работает, но я не знаю как
//     time_t timer = time(NULL); 
//     printf("%s\n", ctime(&timer));
    return 0;
}
  
*/
