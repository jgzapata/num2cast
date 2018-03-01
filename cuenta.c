/* cliente básico para biblioteca num2cast
   compilar con
   gcc cuenta.c -o cuenta.exe -I. -L. num2cast.a

*/



#include <num2cast.h> 

int main(int argc, char *argv[]) {
  char la_salida[10000]; //máximo texto producible

  /* opciones */
  if (argc !=2) {
    printf("uso: cuenta numeroendecimal\n");
    exit(0);
  }
  
  /* llamada */
 
  num2cast("dummya", argv[1], la_salida);

  printf("%i\n",cuentaNoEspacios(la_salida));
  
  return(0);
}

int cuentaNoEspacios(char *in) {
  int i = 0, cuenta = 0;

  while (in[i] != '\0') {
    if (in[i] != ' ')
      cuenta++;
    i++;
  }
  return(cuenta);
}
