# Pacman en c++ P1

El proyecto consiste en un intento dolorosamente torpe de Pacman en la terminal de comandos
de Windows programado en c++ y con el uso de la IDE Visual Studio para ejecutar dicho "juego", 
trata de cumplir con los requisitos de la entrega de CampusNet programada para el día 12/12/2022 (Que fecha más chula por cierto).


## Autor

- [Antonio Manuel Álvarez Madueño](https://github.com/Speedtron222)


## Detalles

Ha habido algunos problemas relativos al rendimiento a 
la hora de utilizar colores en el juego, la solución por la que me
he decantado (dado que el sistema para colorear los caracteres que he usado es
ANSI) consiste en agregar la posibilidad de desactivar los colores pulsando la tecla
E.

Cabe destacar tanto que dicho sistema puede no funcionar en versiones de Windows anteriores
a Windows10, como que el código utilizado está mayormente sacado del usuario Timmy_A de StackOverflow en 
su respuesta al post "[Different coloured characters in char array output on C++](https://stackoverflow.com/questions/51807566/different-coloured-characters-in-char-array-output-on-c)"
