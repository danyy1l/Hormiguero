###################################################################################<br>
&emsp; &emsp; &emsp; &emsp;  &emsp;  &emsp;  &emsp;  &emsp;  &emsp;  &emsp;  &emsp;  &emsp;  &emsp; INSTRUCCIONES PARA LA EJECUCIÓN DEL JUEGO<br>
###################################################################################<br>

1 - Dirigirse a la carpeta anthill_game/ 
 
2 - Comandos de terminal:<br>
&emsp; &emsp;   ->make: Compilar los archivos y crear el ejecutable.<br>
&emsp; &emsp; &emsp; &emsp;     -> ./anthill anthill.dat: Ejecuta manualmente una vez compilados los archivos<br>
&emsp; &emsp;   ->make clean: Eliminar los archivos compilados y el ejecutable.<br>
&emsp; &emsp;   ->make run: Compilar los archivos, crear el ejecutable y ejecutar el juego.<br>
&emsp; &emsp;   ->make runv: Compilar y ejecutar el juego con valgrind para revisar fugas de memoria.<br>

3 - Comandos del juego:<br>
&emsp; &emsp;   ->North(n): Moverse a la casilla de encima.
&emsp; &emsp;   ->East(e): Moverse a la casilla a la derecha.
&emsp; &emsp;   ->South(s): Moverse a la casilla de debajo.
&emsp; &emsp;   ->West(w): Moverse a la casilla a la izquierda.
&emsp; &emsp;   ->Take(t): Coger el objeto que haya en la casilla en la que nos encontremos.
&emsp; &emsp;   ->Drop(d): Soltar el objeto si lo tenemos cogido.
&emsp; &emsp;   ->Quit(q): Cerrar el juego.
