# NODO_TETRIS
Prueba inicial del juego tetris implementado con GBT.
## Funciones actuales
el juego permite elegir entre modo de video CGA (320x200) y modo VGA (640x480).
Los elementos graficos escalan apropiadamente segun el modo de video.
Ademas se permite aplicar un multiplicador de escala de N pixeles que no afecta la resolucion logica
### Modo de uso
Con el proyecto compilado se genera un archivo "ventana.exe".
si se hace doble click en ventana.exe el juego inicia en el ultimo modo de video y escala utilizados.

para elegir el modo de video se debe abrir desde la terminal.
```bash
Resoluciones logicas
  -v  Resolucion logica VGA (640x480)
  -c  Resolucion logica CGA (320x200)
Escalas de pixel
  -<N> Escalas de pixel. Siendo N la escala de los pixeles, rango 0-9. Ej -2
Ejemplo de uso
./Ventana.exe -v -2
  Abre el juego en resolucion logica VGA con escala de pixeles 2 (1280 x 960)
```
