# Display Conexion de java en arduino
El en siguiente proyecto se pretende realizar en java la itereaccion desde un arduino y java mandando un msk en LCD donde se muestra la temperatura, la hora y la fecha actual, y un mensaje(el que el usuario quiera mandar), y todo esto se lograra usando la libreria RXTX para mantener la comunicacion entre el puerto seria y los datos leidos en java

# Materiales
Pararealizar esta pratica necesitaremos los siguientes materiales:
* Arduino UNO
* Cables para protoboard
* Un protoboard
* Sensor de temperatura lm35
* Display LCD de 16X2 con su placa controladora
* Potenciometro de 10K Ohm's
* IDE de desarrolla JAVA

Adicionalmente, necesitaremos tener a nuestra disposicion del Java Developer Kit para lograr la programacion en Java.
Ya sea en un IDE (como netbeans, Oracle, etc) o sólo el compilador por consola, la libreras RXTX y Timer.h para la 
conexion serial y para obtener la hora del sistema del equipo de computo

## Imagen del prototipo
![Una imagen cualquiera](Evidencia1.jpg "Prototipo")
![Una imagen cualquiera](Evidencia2.jpg "Prototipo")
![Una imagen cualquiera](Evidencia3.jpg "Prototipo")

## Imagen del esquema de conexion
![Una imagen cualquiera](https://github.com/FranciscoMan/DisplaySerial/blob/master/LCD.png "Prototipo")

## Funcionalidad
El LCD mostrara en todo momento una cierta hora predeterminada como 00:00:00 en un formato de 24hrs
En la parte superior del LCD se mostraran mensajes cambiantes, siendo uno la lectura del sensor de temperatura y el otro 1 de 3 mensajes
varios que, mediante la interfaz se podrán personalizar (como se muestra en las imagenes anteriores).

## Interfaz de JAVA
![Una imagen cualquiera](https://github.com/FranciscoMan/DisplaySerial/blob/master/interfaz1.png "interfaz")
La interfaz es como se muetra a anteriormente. Funciona a manera que el panel derecho muestra la lista de saludos en orden,
si se quiere se puede dar click en un saludo, al hacer esto se seleccionará de la siguiente manera

![Una imagen cualquiera](https://github.com/FranciscoMan/DisplaySerial/blob/master/interfaz2.png "interfaz")

y al escribir sobre la texbox se podra actualizar ese mensaje para que sea diferente.

* **Actualizar** mensaje
este boton hace lo anterior descrito
* **Actualizar**
este boton actualiza todos los mensajes al arduino, aunque se modifiquen en la lista no será
sino hasta que se use este boton que se reflejaran en el arduino
* **Mostrar**
si seleccionamos un mensaje y damos click en este boton se mostrará en el arduino el mensaje que hayamos seleccionado
