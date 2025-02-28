# Instrucciones para la ejecución del juego
Dirigirse a la carpeta anthill_game/ 
 
### Comandos de terminal:
Compilar los archivos y crear el ejecutable
```bash
make
```
Ejecuta el juego una vez compilados los archivos
```bash
./anthill anthill.dat
```
Eliminar los archivos compilados y el ejecutable
```bash
make clean
```
Compilar los archivos, crear el ejecutable y ejecutar el juego
```bash
make run
```
Compilar y ejecutar el juego con valgrind para revisar fugas de memoria
```bash
make runv
```

### Comandos del juego:
- North (n): Moverse a la casilla de encima.<br>
- East (e): Moverse a la casilla a la derecha.<br>
- South (s): Moverse a la casilla de debajo.<br>
- West (w): Moverse a la casilla a la izquierda.<br>
- Take (t): Coger el objeto que haya en la casilla en la que nos encontremos.<br>
- Drop (d): Soltar el objeto si lo tenemos cogido.<br>
- Attack (a): Ataca al personaje de la casilla si no es friendly<br>
- Chat (c): Conversa con el personaje de la casilla si es friendly<br>
- Quit (q): Cerrar el juego.<br>

## License
[GLPv3.0](https://choosealicense.com/licenses/gpl-3.0/)
