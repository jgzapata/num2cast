/**___________________________________________

   num2cast.c
   
  comprobar con:
for ((i=101;i<1000;i++)); do echo $i ':'; ./num2cast $i ;done > sali.txt 
for ((i=1000;i>100;i--)); do echo $i ':'; ./a.out $i ;done > ilas.txt
   
   ___________________________________________**/
   
/**  TO DO
  - los géneros
  - el acabado en "... y un" si la palabra que sigue es un sustantivo masculino o un sustantivo femenino comenzando en «a» o en «ha» tónica.
  - solo cardinales http://buscon.rae.es/dpdI/SrvltGUIBusDPD?lema=cardinales
  -
**/

#include "num2cast.h" 

int grupo(char * format, char * charnumero, char *salida);
int unidad(char * format, char * charnumero, char *salida);
int decena(char * format, char * charnumero, char *salida);
int centena(char * format, char * charnumero, char *salida);

//int main(int argc, char *argv[]) {
//  char la_salida[10000]; //maximo texto producible
//
//  /* opciones */
//  if (argc !=2) {
//    printf("uso: num2cast numeroendecimal\n");
//    exit(0);
//  }
//  
//  /* llamada */
//  
//  num2cast("dummya", argv[1], la_salida);
//  
//  printf(" %s\n",la_salida);
//  
//  return(0);
//}

int numi2cast(char * format, int numero, char * salida) {
  char charnumero[100];  // maximo numero de cifras
  
  sprintf(charnumero, "%i", numero);
  num2cast(format, charnumero, salida);
  return(0);
  
}

int num2cast(char * format, char * charnumero, char * salida) {
  char temp[100]; // máximo numero de cifras
  char lista_grupos[34][4]; // máximo numero de grupos
  char pronuncia_grupos[34][34]; // los máximos caracteres de un grupo son 33, casualmente
    char nombres_de_grupo[32][16] = {"",
                                   "mil ",
                                   "mill",
                                   "mil ",
                                   "bill",
                                   "mil ",
                                   "trill",
                                   "mil ",
                                   "cuatrill",
                                   "mil ",
                                   "quintill",
                                   "mil ",
                                   "sextill",
                                   "mil ",
                                   "septill",
                                   "mil ",
                                   "octill",
                                   "mil ",
                                   "nonill",
                                   "mil ",
                                   "decill",
                                   "mil ",
                                   "oncill",
                                   "mil ",
                                   "docill",
                                   "mil ",
                                   "trecill",
                                   "mil ",
                                   "catorcill",
                                   "mil ",
                                   "quincill",
                                   "mil "};
                                   
  int i, num_grupos;

  /* grupo acepta trs caracteres. los <= 99 se rellenan con ceros */
  if (strlen(charnumero)%3 == 1) { strcpy(temp,charnumero);strcpy(charnumero,"00");strcat(charnumero,temp);}
  if (strlen(charnumero)%3 == 2) { strcpy(temp,charnumero);strcpy(charnumero,"0");strcat(charnumero,temp);}
 
  /* dividir en grupos */
  num_grupos = (strlen(charnumero) + 2) / 3 ;
  
  //printf("%s son %i grupos\n",charnumero, num_grupos);
  //fflush(NULL);

  for (i = 0; i < num_grupos; i++){
    strncpy(lista_grupos[i],&(charnumero[3*i]), 3);
    lista_grupos[i][3] = '\0';
  }
  
  /* pronunciar cada grupo */ 
  for (i = 0; i < num_grupos - 1; i++) {
    grupo("gc",lista_grupos[i],pronuncia_grupos[i]); 
    //printf("pronun %s\n",pronuncia_grupos[i]);
    //fflush(NULL);
  }

  grupo("c",lista_grupos[num_grupos - 1],pronuncia_grupos[num_grupos - 1]); 
  
  /* unirlo todo */
  strcpy(salida,"");
  if (NULL != strchr(format,'n'))
    sprintf(salida,"%s: ",charnumero);
     
  for (i = 0; i < num_grupos; i++) {
    /* pronuncia el grupo */
    if (!((0 == strcmp(lista_grupos[i],"001") && ((num_grupos - i -1)%2 == 1)))) {  // para evitar "uno mil"
      strcat(salida,pronuncia_grupos[i]);
      if (strlen(pronuncia_grupos[i]) > 0)
      strcat(salida," "); // el espacio es responsabilidad del más significativo
    }
    
    /* pronuncia el nombre de grupo */
    if (!(0 == strcmp(lista_grupos[i],"000")) || ((num_grupos - i -1)%2 == 0)) {// para evitar "1000000" como "un millón mil"
      if (!((0 == strcmp(lista_grupos[i],"000")) && (0 == strcmp(lista_grupos[i-1],"000")))) {
        strcat(salida,nombres_de_grupo[num_grupos - i - 1]);
        if (((num_grupos - i -1)%2 == 0) && ((num_grupos - i -1) >1) ) {
          if (((0 != strcmp(lista_grupos[i],"001"))))  // para añadir "es " o " "
            strcat(salida,"ones ");
          else
            strcat(salida,"ón ");
        }
      }
    }
  }

  return(0);
  
}

int grupo(char * format, char * charnumero, char * salida) {
  char micentena[15]; // máximo tamaño de las salidas de las funciones correspondientes
  char midecena[13];
  char miunidad[8];
  
  //supone que es un grupo de tres caracteres, completado con ceros a la izquierda si es necesario
  if (charnumero[0] == '0') {
    strcpy(micentena,"");
    if (charnumero[1] == '0') {  // necesario para 001 noches
      strcpy(midecena,"");
      if (charnumero[2] == '0')
        if (NULL == strchr(format,'c'))
          strcpy(miunidad,"cero");
        else
          strcpy(miunidad,"");

      else
        unidad(format, &charnumero[2],miunidad);
    } else {
      decena(format, &charnumero[1],midecena);
      unidad(format, &charnumero[2],miunidad);
    }
  } else {
    centena(format, &charnumero[0],micentena);
    decena(format, &charnumero[1],midecena);
    unidad(format, &charnumero[2],miunidad);
  }


  strcpy(salida,micentena);
  strcat(salida,midecena);
  strcat(salida,miunidad);

  return(0);

}




int unidad(char * format, char * charnumero, char * salida) {

   /* supone que *(charnumero - 1) apunta a las decenas */
  if (charnumero[0] == '1')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el once es responsabilidad de decena 
    else if (NULL != strchr(format,'g'))
      strcpy(salida,"un");
    else if (NULL != strchr(format,'f')) 
      strcpy(salida,"una");
    else
      strcpy(salida,"uno");
      
  else if (charnumero[0] == '2')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el doce es responsabilidad de decena 
    else if (charnumero[-1] == '2')
      strcpy(salida,""); // el veintidós es responsabilidad de decena 
    else
    strcpy(salida,"dos"); 
  else if (charnumero[0] == '3')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el trece es responsabilidad de decena 
    else if (charnumero[-1] == '2')
      strcpy(salida,""); // el veintitrés es responsabilidad de decena 
    else
    strcpy(salida,"tres"); 
  else if (charnumero[0] == '4')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el catorce es responsabilidad de decena 
    else
    strcpy(salida,"cuatro"); 
  else if (charnumero[0] == '5')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el quince es responsabilidad de decena 
    else
    strcpy(salida,"cinco"); 
  else if (charnumero[0] == '6')
    if (charnumero[-1] == '1')
      strcpy(salida,""); // el dieciséis es responsabilidad de decena 
    else if (charnumero[-1] == '2')
      strcpy(salida,""); // el veintiséis es responsabilidad de decena 
    else
    strcpy(salida,"seis"); 
  else if (charnumero[0] == '7')
    strcpy(salida,"siete"); 
  else if (charnumero[0] == '8')
    strcpy(salida,"ocho"); 
  else if (charnumero[0] == '9')
    strcpy(salida,"nueve"); 
  else if (charnumero[0] == '0')  //necesario para 110
    strcpy(salida,""); 

  return(0);  
    
} 

int decena(char * format, char * charnumero, char * salida) {

  /* supone que *(charnumero + 1) apunta a las unidades */
  if (charnumero[0] == '1')
    if (charnumero[1] == '0')
      strcpy(salida,"diez"); 
    else if (charnumero[1] == '1')
      strcpy(salida,"once");
    else if (charnumero[1] == '2')
      strcpy(salida,"doce");
    else if (charnumero[1] == '3')
      strcpy(salida,"trece");
    else if (charnumero[1] == '4')
      strcpy(salida,"catorce");
    else if (charnumero[1] == '5')
      strcpy(salida,"quince");
    else if (charnumero[1] == '6')
      strcpy(salida,"dieciséis");
    else
      strcpy(salida,"dieci"); 
  else if (charnumero[0] == '2')
    if (charnumero[1] == '0')
      strcpy(salida,"veinte"); 
    else if (charnumero[1] == '2')
      strcpy(salida,"veintidós");
    else if (charnumero[1] == '3')
      strcpy(salida,"veintitrés");
    else if (charnumero[1] == '6')
      strcpy(salida,"veintiséis");
    else 
      strcpy(salida,"veinti"); 
  else if (charnumero[0] == '3')
    if (charnumero[1] == '0')
      strcpy(salida,"treinta"); 
    else
      strcpy(salida,"treinta y ");  // consultar la academia, no es strcpy(salida,"trentai"); 
  else if (charnumero[0] == '4')
    if (charnumero[1] == '0')
      strcpy(salida,"cuarenta"); 
    else
      strcpy(salida,"cuarenta y "); 
  else if (charnumero[0] == '5')
    if (charnumero[1] == '0')
      strcpy(salida,"cincuenta"); 
    else
      strcpy(salida,"cincuenta y "); 
  else if (charnumero[0] == '6')
    if (charnumero[1] == '0')
      strcpy(salida,"sesenta"); 
    else
      strcpy(salida,"sesenta y "); 
  else if (charnumero[0] == '7')
    if (charnumero[1] == '0')
      strcpy(salida,"setenta"); 
    else
      strcpy(salida,"setenta y "); 
  else if (charnumero[0] == '8')
    if (charnumero[1] == '0')
      strcpy(salida,"ochenta"); 
    else
      strcpy(salida,"ochenta y "); 
  else if (charnumero[0] == '9')
    if (charnumero[1] == '0')
      strcpy(salida,"noventa"); 
    else
      strcpy(salida,"noventa y "); 
  else if (charnumero[0] == '0') // necesario para 100
    strcpy(salida,""); 

  return(0);  
    
} 

int centena(char * format, char * charnumero, char * salida) {

  /* supone que *(charnumero + 1) apunta a las decenas y *(charnumero + 2) apunta a las unidades */
  if (charnumero[0] == '1')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"cien"); 
    else
      strcpy(salida,"ciento "); 
  else if (charnumero[0] == '2')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"doscientos"); 
    else
      strcpy(salida,"doscientos "); 
  else if (charnumero[0] == '3')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"trescientos"); 
    else
      strcpy(salida,"trescientos "); 
  else if (charnumero[0] == '4')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"cuatrocientos"); 
    else
      strcpy(salida,"cuatrocientos "); 
  else if (charnumero[0] == '5')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"quinientos"); 
    else
      strcpy(salida,"quinientos "); 
  else if (charnumero[0] == '6')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"seiscientos"); 
    else
      strcpy(salida,"seiscientos "); 
  else if (charnumero[0] == '7')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"setecientos"); 
    else
      strcpy(salida,"setecientos "); 
  else if (charnumero[0] == '8')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"ochocientos"); 
    else
      strcpy(salida,"ochocientos "); 
  else if (charnumero[0] == '9')
    if ((charnumero[1] == '0') && (charnumero[2] == '0'))
      strcpy(salida,"novecientos"); 
    else
      strcpy(salida,"novecientos "); 
  else if (charnumero[0] == '0') // ¿necesario?
    strcpy(salida,""); 

  return(0);  
    
} 




