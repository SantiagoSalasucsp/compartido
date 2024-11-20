# compartido
En este trabajo tomamos como base el codigo de semaforo que ya habiamos implementado y aparte usamos Share memory y teniendo esto tenemos un programa que se llama px.c este recibe como parametros una palabra y un numero y vamos a ejecutarlo 3 veces, cada uno de ellos va a consultar si el numero que le pasamos es el siguiente que toca para esrcbir en la Share memory y si no solo espera y asi se van rotando, ademas tenemos el programa r.c que esta imprimiendo en consola todo lo que esta en la Share memory y ademas tenemos dos variación donde entran a ese circulo un programa en c++ y python
ademas despues de poner el make, se pone en este orden
./init.exe
./r.exe 
g++ px.cpp  (ademas si se quiere ejecitar el codigo de python se tiene que instalar sysv_ipc)
./px.exe julio 4
./px.exe keiko 5
./a.out pedro 6 (si fuera python se pondria python pyth.py pedro 6)
