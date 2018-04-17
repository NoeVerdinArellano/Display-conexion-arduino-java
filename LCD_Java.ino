//Este codigo implemetara la funcionalidad ya mencionada en el README
//NOTA: las librerias se deben de descargar e implementar si no dara errrar aunque se impoarte
//en el readme hay un link de descar de las ya mencionadas, de LiquidCrystal no por que es una libreria que ya la tiene el IDE de arduino
//Lo primero será importar las librerias
#include <Time.h>
#include <TimeLib.h>
#include <LiquidCrystal.h>

// la variable time_t t tiene el manejo de la hora y fecha
time_t t;
//la variable de tipo LiquidCrystal sirve para inicializar la comunicacion con el display LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//arreglo que almacenara los saludos, solo seran tres por la pequeña capacidad de memoria del arduino
String saludo[3];
//en caso de problema con la libreria Time, se mostrara el mensaje "S/H"
String reloj="S/H";
//la variable cambio es la que lleva el contro de cada 4 segundos se mostrara otro mensaje
int cambio;
//la siguiente variable booleana sirve para indicar si se está mostrando el saludo
//o la temperatura, siendo true es que se muestra el saludo, sirve junto con la 
//variable anterior para el cambio
boolean m=false;
//index sirve para navegar entre los saludos, al solicitar
//el cambio en la interfaz index aumentará o disminuira
//dependiendo del mensaje que se solicite a mostrar
int index=0;
//está variable es para almacenar la lectura del sensor de temperatura
float centigrados=0.0;


void setup(){  
// se inicializa eldisplay 16X2 por que son las dimenciones de nuestro display
lcd.begin(16, 2);
//inicializamos la comunicacion serial, esta misma se comunica con la interfaz de java
Serial.begin(9600);
//el arreglo antes inicializado con los 3 salidos
  saludo[0] = "Saludo 1";
  saludo[1] = "saludo 2";
  saludo[2] = "saludo 3"; 
}

//este loop nos ayuda para tener el control de cada cuanto se leera la comunicacion del serial
//y cada cuando se cambiará el mensaje, actualizrá la hora y la temperatura
void loop(){

// la funcion de actualizar asignar y leer el la cadena de la interfaz de java, actualizarlo,
//asi como actualizara la hora y la temperatura
actualizar();

// escribiendo la hora en formato de 24hrs
escribeHora();
//escribeM escribira ya sea el saludo o la temperatura, dependiendo del valor de la variable booleana m
escribeM();


delay(500);
//aqui es donde se cuenta el tiempo para realizar los cambios entre el mensaje de saludo y temp
//simplemente al contar los 4 seg se modifica el valor de la booleana m para que el metodo
//escribeM escriba la temperatura o el saludo, dependiendo de lo que toque
cambio = cambio +500;
if(cambio>=4000){
  cambio=0;
 if(m){
  m = false;
 }else{
  m = true;
 }
}

}

//metodo actualizar
void actualizar(){
//en está parte declaramos una serie de variables que nos ayudarán a leer el mensaje
//del serial (dado por la interfaz java) y a asignaro a sus variables correspondientes
String Mensaje="";
int indice=0;
int mensajes=0;
String aux="";
//inicializacion de las variamos para la hora,minuto, y segundos
int h,m,s;

//la funcion del while es leer la comunicacion serial por caracteres mientras el metodo Decimal_to_ASCII
//se encarga de juntarlos y hacerlos un string 
while (Serial.available()>0){
Mensaje= Mensaje+Decimal_to_ASCII(Serial.read());

}

//en esta parte del metodo si el mensaje existe se captura la hora (que es la primer parte del mensaje)
//el formato recibido del serial es 00 00 00*saludo,saludo,saludo*0
//siendo los primeros numeros la hr (horas,minutos,segundos) luego un * que indica que comienzan los saludos
//siendo separados por comas y seguidos de otro * que indica comienza el valor del INDEX, varibale descrita al inicio
//cuya funcion es indicar que saludo mostrar
if(Mensaje!=""){
  //capturamos la hora del serial
    reloj ="";
  //el siguiente while leera los chars hasta toparse con un * 
  //que indica se ha terminado de leer la hora
    while(Mensaje.charAt(indice)!='*'){
      //este otro while busca hasta un espacio porque las horas,minutos y segundos se separan por espacios
      while(Mensaje.charAt(indice)!=' '){
      reloj = reloj+Mensaje.charAt(indice);
      indice++;
      }
      h = reloj.toInt();
      
      reloj="";
      indice++;
      while(Mensaje.charAt(indice)!=' '){
      reloj = reloj+Mensaje.charAt(indice);
      indice++;
      }
      m = reloj.toInt();
    
      reloj="";
      indice++;
      while(Mensaje.charAt(indice)!='*'){
      reloj = reloj+Mensaje.charAt(indice);
      indice++;
      }
      s = reloj.toInt();
      reloj="";
      //ya asignados los valores a las variables h,m y s se usa el metodo setTime
      //que inicializa la hora y la fecha a los valores dados como parametros
      //como la fecha no se usa, puede ser cualquiera, ojo solo por este ejemplo que no se utiliza
      setTime(h,m,s,12,04,2018);
      
    }
    //es importante decir que indice ayuda a ser el puntero de lectura sobre el mensaje de entrada
    //del serial
      indice++;
  //el sigueinte while leera todos los saludos
  while(Mensaje.charAt(indice)!='*'){
    //almacenando cada char del saludo en la variable aux, hasta toparse con una coma
    //será entonces que el saludo se asigne al arreglo, se vacie la variable auxiliar
    //y se vuelva a comenzar
    if(Mensaje.charAt(indice)!=','){
     aux = aux+Mensaje.charAt(indice);
     }
     else{
      
      saludo[mensajes] = aux;
      mensajes++;
      aux="";
     }
    indice++;
  }
  //aqui sólo queda leer el ultimo char que indica cual saludo mostrar
  indice++;
  //si es un 0 mostrará el primer saludo, un 1 el segundo y así
switch(Mensaje.charAt(indice)){
  case '0' : index =0;
  break;
  case '1' : index =1;
  break;
  case '2': index = 2;
  break;
}
  
}
//capturamos temperatura

centigrados = (analogRead(A0)*500)/1024;

}
//fin de metodo

//este metodo es muy sencillo, ya que sólo coloca el cursor de escritura del display
//en el inicio de la pantalla y el segundo renglon, borra lo que haya escrito y escribe
//la nueva hora
void escribeHora(){
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  //aqui se usa la variable de tipo time_t descrita anteriormente
  //nos ayuda a traer la hora asignada anteriormente con setTime
  //con la moneria de poder solicitar ya sea la hora solamente, el minuto, segundo
  //incluso partes de la fecha pero para este ejemplo no ocupamos eso
  t = now();
  reloj = hour(t);
  reloj = reloj+":";
  reloj = reloj+minute(t);
  reloj = reloj+":";
  reloj = reloj+second(t);
  //imprime la hora
  lcd.print(reloj);
  
}
//fin del metodo

//este es el metodo que escribe ya sea la lectura de temperatura
//o el saludo. De igual manera primero borra lo anterior escrito y vuelve a escribir
void escribeM(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  if(m){
    lcd.print(saludo[index]);
  }else{
    lcd.print("temp: ");
    lcd.print(centigrados);
  }
}
//fin del metodo

//este es de los primeros metodos descritos y nos ayuda a transformar
//la lectura del serial que viene en formato ASCII a un char
//ASCII tiene una cantidad enormemente mayor de claves pero sólo incluí
//las que creí necesarias para el ejemplo
//se pueden consultar simplemente observando la salida
char Decimal_to_ASCII(int entrada){
  char salida=' ';
  switch(entrada){
case 32: 
salida=' '; 
break; 
case 33: 
salida='!'; 
break; 
case 34: 
salida='"'; 
break; 
case 35: 
salida='#'; 
break; 
case 36: 
salida='$'; 
break; 
case 37: 
salida='%'; 
break; 
case 38: 
salida='&'; 
break; 
case 39: 
salida=' '; 
break; 
case 40: 
salida='('; 
break; 
case 41: 
salida=')'; 
break; 
case 42: 
salida='*'; 
break; 
case 43: 
salida='+'; 
break; 
case 44: 
salida=','; 
break; 
case 45: 
salida='-'; 
break; 
case 46: 
salida='.'; 
break; 
case 47: 
salida='/'; 
break; 
case 48: 
salida='0'; 
break; 
case 49: 
salida='1'; 
break; 
case 50: 
salida='2'; 
break; 
case 51: 
salida='3'; 
break; 
case 52: 
salida='4'; 
break; 
case 53: 
salida='5'; 
break; 
case 54: 
salida='6'; 
break; 
case 55: 
salida='7'; 
break; 
case 56: 
salida='8'; 
break; 
case 57: 
salida='9'; 
break; 
case 58: 
salida=':'; 
break; 
case 59: 
salida=';'; 
break; 
case 60: 
salida='<'; 
break; 
case 61: 
salida='='; 
break; 
case 62: 
salida='>'; 
break; 
case 63: 
salida='?'; 
break; 
case 64: 
salida='@'; 
break; 
case 65: 
salida='A'; 
break; 
case 66: 
salida='B'; 
break; 
case 67: 
salida='C'; 
break; 
case 68: 
salida='D'; 
break; 
case 69: 
salida='E'; 
break; 
case 70: 
salida='F'; 
break; 
case 71: 
salida='G'; 
break; 
case 72: 
salida='H'; 
break; 
case 73: 
salida='I'; 
break; 
case 74: 
salida='J'; 
break; 
case 75: 
salida='K'; 
break; 
case 76: 
salida='L'; 
break; 
case 77: 
salida='M'; 
break; 
case 78: 
salida='N'; 
break; 
case 79: 
salida='O'; 
break; 
case 80: 
salida='P'; 
break; 
case 81: 
salida='Q'; 
break; 
case 82: 
salida='R'; 
break; 
case 83: 
salida='S'; 
break; 
case 84: 
salida='T'; 
break; 
case 85: 
salida='U'; 
break; 
case 86: 
salida='V'; 
break; 
case 87: 
salida='W'; 
break; 
case 88: 
salida='X'; 
break; 
case 89: 
salida='Y'; 
break; 
case 90: 
salida='Z'; 
break; 
case 91: 
salida='['; 
break; 
case 92: 
salida=' '; 
break; 
case 93: 
salida=']'; 
break; 
case 94: 
salida='^'; 
break; 
case 95: 
salida='_'; 
break; 
case 96: 
salida='`'; 
break; 
case 97: 
salida='a'; 
break; 
case 98: 
salida='b'; 
break; 
case 99: 
salida='c'; 
break; 
case 100: 
salida='d'; 
break; 
case 101: 
salida='e'; 
break; 
case 102: 
salida='f'; 
break; 
case 103: 
salida='g'; 
break; 
case 104: 
salida='h'; 
break; 
case 105: 
salida='i'; 
break; 
case 106: 
salida='j'; 
break; 
case 107: 
salida='k'; 
break; 
case 108: 
salida='l'; 
break; 
case 109: 
salida='m'; 
break; 
case 110: 
salida='n'; 
break; 
case 111: 
salida='o'; 
break; 
case 112: 
salida='p'; 
break; 
case 113: 
salida='q'; 
break; 
case 114: 
salida='r'; 
break; 
case 115: 
salida='s'; 
break; 
case 116: 
salida='t'; 
break; 
case 117: 
salida='u'; 
break; 
case 118: 
salida='v'; 
break; 
case 119: 
salida='w'; 
break; 
case 120: 
salida='x'; 
break; 
case 121: 
salida='y'; 
break; 
case 122: 
salida='z'; 
break; 
case 123: 
salida='{'; 
break; 
case 124: 
salida='|'; 
break; 
case 125: 
salida='}'; 
break; 
case 126: 
salida='~'; 
break; 




  }
  return salida;
}
