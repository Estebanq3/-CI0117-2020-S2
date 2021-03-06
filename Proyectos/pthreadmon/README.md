Documentacion Externa:

Trabajo elaborado por:
Esteban Quesada Quesada B96157
Steven Nuñez Murillo B95614

Manual de Usuario:
El programa se desarrolló en el sistema operativo Ubuntu 20.04.1 LTS
Las bibliotecas necesarias para poder compilar el programa se pueden 
descargar en un sistema con linux, digitando los siguientes comandos 
en la terminal:
	
	-> sudo apt-get install libgtk-3-dev
	-> sudo apt install pkg-config
	-> sudo apt-get install glade

	->Bibliotecas necesarias para poder utilizar hilos vienen integradas 
	  en el sistema de linux. Se debe utilizar -pthread para poder compilar
	  cuando se utiliza esta biblioteca.
	->Asimismo utilizamos la biblioteca de math para poder realizar una
	  función denominada floor, para redondear números. Se debe utilizar 
	  -lm para poder compilar con esta biblioteca.

Para compilar el programa en la terminal de linux se debe utilizar el
siguiente comando:
	gcc *.c -o prueba -Wall `pkg-config --libs --cflags gtk+-3.0` -pthread -lm

Hora de Utilizar el programa:
En primera instancia se despliega una ventana la cual se denomina "Informacion", donde se deben llenar los respectivos campos de texto. En primer lugar se debe digitar los nombres de los jugadores en los respectivos cuadros de entrada de 
texto. Estos nombres de jugadores pueden admitir solamente 25 caracteres.
Cada jugador debe elegir a tres pokemones, digitando el nombre de los que desean seleccionar para su equipo. La lista de pokemones disponibles no se despliega,
mas muchos de ellos se encuentran en el conocido juego denominado "Pokemon Go".
Los nombres de los pokemones no superan los 11 caracteres, por lo tanto en los
cuadros donde se digitan los nombres de estos, el máximo permitido son 11 caracteres.
Una vez se digitan los nombres de los jugadores y de los pokemones seleccionados
se debe presionar el botón denominado "IniciarBatalla". Posteriormente si los elementos digitados fueron correctos aparecerá
una pantalla donde se muestra una simulación de la batalla entre los pokemones
de cada jugador. Esta ventana se denomina "SimulacionPokemon" y una vez se termine la simulación desaparecerá y se mostrará una nueva ventana que contiene las estadísticas finales de la batalla.
Si se desea volver a iniciar una nueva batalla entre los mismos pokemones y jugadores o se desea introducir nuevos datos se debe presionar el botón que se muestra en la parte inferior de la ventana denominada Resultados, el cual se denomina "IniciarNuevamente".

Interpretación de Resultados:
Los datos que se muestran en la ventana llamada SimulacionPokemon, la cual aparece luego de iniciar el juego se pueden interpretar de la siguiente forma:
->En el lado izquierdo se muestra el jugador1, su respectivo nombre, con sus pokemones seleccionados, los cuales muestran dos estados, un estado denominado "Habilitado" el cual indica que permanece habilitado para batallar o se encuentra en plena batalla  y todavía no ha sido debilitado por ningún pokemon enemigo. Cuando un pokemon muere muestra el estado denominado "Debilitado".
->Cada pokemon que se encuentre en batalla se va a mostrar en el campo denominado pokemon activo, asimismo, se mostrará la vida de este pokemon, la EnergíaAcumulada que posee en los distintos momentos de una batalla, cuando esta energía se iguale a "UltimateEnergy" el pokemon tendrá la posibilidad de realizar un ataque cargado, Por lo tanto este dato especial denominado "UltimateEnergy" 
significa la energía que debe alcanzar un pokemon para realizar un ataque cargado al oponente.
->En el lado derecho de la ventana se muestran exactamente los mismos datos para el jugador 2.
->En el centro de la ventana, se muestra el Ataque que se está realizando en un momento determinado de la batalla, por lo tanto se denomina "AtaqueActual", asimismo, se presenta el nombre del pokemon que realiza determinado ataque, así como el jugador que posee a tal pokemon, es decir el "Player".

En la última ventana denominada Resultados, la información que se presenta es el jugador que resultó ganador con su determinado equipo de pokemones, así como al perdedor con su equipo. Se indica el nombre de cada pokemon del jugador, así como la vida final con la que terminó en la batalla cada pokemon, y el tiempo que duró en batalla cada uno de estos.
Al final se muestra un dato que se denomina "TiempoTotal" el cual señala la duración total de la batalla.

Casos de Prueba:
Ventana 0:

![image](https://github.com/Estebanq3/-CI0117-2020-S2/blob/master/Proyectos/pthreadmon/CasodePruebaW0.png)

Ventana 1:

![image](https://github.com/Estebanq3/-CI0117-2020-S2/blob/master/Proyectos/pthreadmon/CasoDePruebaW1.png)

Ventana 2:

![image](https://github.com/Estebanq3/-CI0117-2020-S2/blob/master/Proyectos/pthreadmon/CasoDePruebaW2.png)

Estructura del Programa:
Se utiliza el Modelo Vista Controlador (MVC), el cual es un estilo de arquitectura de software que separa los datos de una aplicación, la interfaz de usuario, y la lógica de control en tres componentes distintos.

La estructura de folders es la siguiente:
-Model, la cual contiene la mayor parte de los .h del programa, los cuales son:
	*GameMaster.h
	*mapper.h
	*Player.h
	*Pokemon.h
-Controller, contiene todas las implementaciones de los modelos:
	*GameMaster.c
	*Player.c
	*Pokemon.c
	*mapper.c
-View, contiene la interfaz gráfica del programa:
	*interfaz.h
	*interfaz.c

Descripción de cada componente:
-GameMaster:Este componente es el encargado de la mayor parte de la lógica de las batallas entre los pokemones. En este se inicializan los jugadores y pokemones de cada partida. En el se implementa la forma en la que se llevan a cabo las peleas entre los pokemones de cada jugador, es decir el método principal denominado Mortal_Combat, en el cual se manipulan hilos y datos para que los pokemones peleen acorde a lo solictado en el enunciado. En sí se puede considerar como 
un segundo main. También se encarga de la liberación de las instancias creadas de los jugadores y los pokemones de la batalla, ya que recordemos que este mismo los inicializaba, así como otros datos que se usan para llevar a cabo la pelea pokemon.
-Player: Este componente es necesario para crear una instancia de un jugador en GameMaster, cuenta con todos los atributos que tiene un jugador de pokemon. Este cuenta con un arreglo de pokemones, en el cual se asignarán los pokemones que se seleccionen durante la batalla. Asimismo, cuenta con su propio método para destruirse.
-Pokemon: Este componente es necesario para crear una instancia de pokemon, el cual será asignado a un determinado jugador. Contiene atributos como vida, energía, nombre, tipo, entre otros. Tmabién cuenta con su propio método para destruirse. Asimismo, se obtienen datos del mapper para poder realizar un análisis del daño que debe realizar cada pokemon dependiendo de su oponente, por lo cual se recurre a los arreglos de debilidades, fortalezas, entre otros, del mapper.
-Mapper: Como se ha mencionado anteriormente, el mapper contiene gran cantidad de los datos necesarios para llevar a cabo una pelea pokemon, en este apartado se encuentran todos los pokemones que se pueden utilizar, así como los datos de cada uno de estos. Muchos de los demás componentes recurren a recuperar información de este elemento para poder llevar a cabo sus métodos.
-Interfaz: Este componente es el encargado de construir la interfaz gráfica del programa, es decir contiene todas las funciones para mostrar información en las ventanas que se construyen.Asi como contiene todas las funciones para recuperar información que es digitada por el usuario.

Métodos de Sincronización Utilizados:
-Barrier Waiting_Area: Este método de sincronización es utilizado en el GameMaster, específicamente en el método Mortal_Combat, para que lleguen
todos los hilos antes de que se comiencen las peleas. Por lo tanto hasta que lleguen los 3 pokemones de cada jugador, se inicia la pelea. Esto con
el fin de que los pokemones se encuentren disponibles todos, para su respectiva pelea durante la batalla, y no existan pokemones que no han llegado
cuando les toca su turno.
-Variable Condicional denominada team_cond y su respectivo mutex denominado team_mutex: este método de sincronización también utilizado en el método Motal_Combat, es de gran utilidad para sincronizar el orden en el que deben pelear los pokemones, si el pokemon que llega no le toca su turno todavía, este es enviado a la lista de espera mientras que no sea su turno. Cuando muere un pokemon se realiza un broadcast que libera todos lo hilos que se encontraban en la lista de espera para verificar si ya deben luchar, de no ser así, se vuelven a introducir a la lista de espera.
-Variable Condicional denominada cond_charged_attack y su respectivo mutex denominado charged_attack_area: esta variable condicional se utiliza para que cuando algún hilo realiza un ataque cargado, solo este ataque se haga en ese preciso instante y no se puedan ejecutar ataques rápidos o cragados de otros pokemones enemigos.
-Mutex fight_area: Este mutex contribuye también al cond_charged_attack para evitar que se realice un ataque rápido mientras se ejecuta un ataque cargado.


Aclaraciones:
	Se presentan errores de congelación de ventana debido a que se desconoce concretamente qué los provoca. Es seguro que GTK influye directamente en tales errores, mientras que la lógica de las peleas pokemon no son la causa del problema, ya que en la terminal el programa se ejecuta correctamente, sin generar algún fallo desconocido o conocido. Se sospecha que la resolución de la pantalla y las ventanas, así como los constantes 
	set que se realizan a los labels pueden provocar cambios en el tamaño de las ventas que incumplen lo necesario para un buen funcionamiento. Incluso no todas las veces se congela la ventana y forza el cierre. Algunas ocasiones la ventana de las estadísticas se ve forzada al cierre, más la mayor parte de veces aunque se congele la ventana de la simulación la ventana de las estadísticas al ser independiente, no falla, y presenta 
	correctamente los datos. Asimismo, permite reiniciar la simulación con su botón de "IniciarNuevamente".




	


