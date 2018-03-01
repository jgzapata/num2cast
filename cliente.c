/* cliente básico para biblioteca num2cast
   compilar con
   gcc cliente.c -o clinum -I. -L. num2cast.a

*/



#include <num2cast.h> 

int main(int argc, char *argv[]) {
  char la_salida[10000]; //máximo texto producible

  /* opciones */
  if (argc !=2) {
    printf("uso: num2cast numeroendecimal\n");
    exit(0);
  }
  
  /* llamada */
 
  num2cast("dummya", argv[1], la_salida);
  
  printf("%s\n",la_salida);
  
  return(0);
}

