**Manual de usuario: Incluir información sobre cómo compilar el código fuente y bibliotecas adicionales a instalar. Información sobre cómo utilizar el programa (entradas esperadas e interpretación de resultados)**

Integrantes del Proyecto:

*Steven Nuñez Murillo B95614*

*Esteban Quesada Quesada B96157*

**Compilación de programa**
El programa fue desarrollado en c++ en un sistema operativo linux.
Las bibliotecas adicionales que se utilizan para compilar este programa son: mpi.h
Esta biblioteca se debe instalar con los siguientes comandos:

```c
sudo apt-get install openmpi-bin
```

El programa se puede compilar mediante el siguiente comando: mpic ++ GameMaster.cpp Mario.cpp World.cpp -o prueba
Para ejecutar el programa se utiliza: mpiexec --oversubscribe -n *numero de procesos* ./prueba

**Uso del programa:**
Para utilizar el programa simplemente se debe abrir el cmd de linux, posteriormente introducir el comando de ejecución indicado anteriormente, en este comando se puede modificar 
la cantidad de Marios que queremos que jueguen a la vez, configurando el número de procesos. Posteriormente, se solicitará un proceso o Mario, esto para espectar las acciones del 
mismo durante el tiempo que se mantenga vivo. Asimismo, al inicio del programa se dará una única oportunidad de seleccionar la estrategia del Mario, debido a que es el primer 
proceso, por lo tanto, una vez se haya solicitado el Mario que se desea espectar, se solicitará la estrategia que se desea establecer para el Mario seleccionado para observarlo.
Se brindan cuatro estrategias que el usuario puede establecer para el Mario:
1.RANDOM: Se establece digitando el número 1, en dicha estrategia se escoge un Mario aleatorio para atacarlo.

2.LESS_COINS: Se establece digitando el número 2. Mario ataca al enemigo con menos monedas.

3.MORE_COINS: Se establece digitando el número 3. Mario ataca al enemigo con mayor número de monedas.

4.ATTACKER: Se establece digitando el número 4. Mario ataca al último enemigo que lo atacó a él.

Asimismo, durante la ejecución de la simulación, si un Mario que se está espectando muere, se le solicita al usuario digitar otro Mario para observar, este debe ser un Mario que 
se encuentre vivo. Los Marios vivos se indican antes de preguntar a cual nuevo jugador se desea observar.

**Detalles de la solución: Estructura del programa (clases, folders, archivos, etc.) y breve descripción de cada uno de los componentes**
El programa está ordenado en dos carpetas, una llamada modelo y otra controlador. En la carpeta modelo se encuentran todos los .h, tales como world.h, mario.h, actions.h
mientras que en la carpeta denominada controlador se contemplan los archivos .cpp: world.cpp mario.cpp gameMaster.cpp.
Componentes Principales de la Implementación:
GameMaster: El gameMaster es el encargado de dirigir la simulación de cada proceso o Mario que se crea en el juego, esta clase coordina todas las acciones y eventos de los 
Marios. Se encarga de crear e inicilizar con métodos de otras clases al Mario y al mundo de cada proceso. Asimismo controla las acciones que realizan los Marios de acuerdo a 
las probabilidades que se obtengan con los métodos de la clase Action. Podemos observar que esta clase se convierte en el main principal de la implementación. Asimismo contiene
métodos para inicializar vectores en los cuales almacenamos información que respecta a los actos de Mario en cada simulación. Estos vectores son compartidos con ayuda de las 
funciones de MPI entre todos los Marios que se están ejecutando, esto con el fin de coordinar el battle royale que ocurre entre todos los Marios que se han inicializado para
participar en la simulación. Una vez se finaliza la simulación esta clase se encarga de hacer los delete respectivos de aquella memoria solicitada dinámicamente.
Actions: La clase actions es la encargada de definir las probabilidades de cada acción de Mario en la simulación, debido a que esta se encarga de calcular una diferente 
probabilidad según el elemento con el cual Mario tenga contaco en el mapa. Una vez se obtenga la probabilidad esta clase se encargará de definir cual acción se realizará según l
la probabilidad obtenida. Por otra parte, esta clase es de gran importancia, puesto que contiene un método encargado de seleccionar la víctima de un determinado Mario según la 
estrategia que el mismo posea. De esta forma se puede definir a esta clase como una parte del programa sumamente enlazada con los ataques de Mario a otros jugadores, así como 
las acciones que realice cada Mario según el elemento que esté enfrentado en el mapa.
Mario: Es una clase encargada de encasillar todos los atributos básico del Mario del videojuego, con un método para construirlo. Asimismo, contamos con diferentes gets y sets, 
los cuales son de utilidad para setear y obtener características básicas de cada jugador durante el momento de la partida. Algunos métodos que engloba son: set/getMarioID, 
set/getMarioLocation, set/getMarioCoins, set/getMarioAlive, getChoosenStrategy. Asimismo, en esta clase se define el método encargado de definir la estrategia a utilizar para 
cada Mario la simulación.
World: La clase World, es utilizada para poder definir al mundo de cada Mario, donde estos mundos podrán tener casillas con los diferentes elementos mencionados en el enunciado, 
tal como los huecos, las monedas, los enemigos. Esta clase contiene un struct, el cual como elementos contiene los diferentes elementos que puede contener un mundo, a medida que 
se necesite colocar una moneda, o un enemigo en determinada posición del mapa, se sumará uno a cada variable del determinado struct para determinar la existencia de tal 
elemento en el entorno. Esta clase contiene métodos como inicializar para crear un mundo de Mario con elementos definidos en cada casilla, así como también cuenta con métodos 
get para obtener la siguiente posición en el mapa o obtener más bien la posición en la que se está actualmente.

**Aclaraciones**
*A la hora que se solicita un nuevo proceso para espectarlo, después de que el proceso que se estaba observando haya muerto, puede suceder un pequeño detalle. Cuando
se solicita el nuevo proceso a espectar, siempre se imprime una lista con los Marios vivos, sin embargo, esta lista puede arrojar datos no completamente actualizados
,puesto que mientras se imprima algun proceso de los que se van a imprimir, alguno pueda haber muerto, por lo tanto, si el programa dura un rato en responder, es porque en 
realidad, no se están imprimiendo las acciones del proceso muerto. Otra aclaración importante es que a pesar de que en ciertos momentos de la impresión Mario indique que está siendo atacado por otro Mario, no necesariamente va a recibir goombas o koopatropas, puesto que solo se está indicando que un Mario lo escogió temporalmente para atacarlo, en caso de matar un goomba o un koopa tropa, pero de no matar a ninguno de estos no se realizará el ataque.*

**Funciones del estándar MPI utilizadas**

1.En primer lugar existe una gran cantidad de Allgathers, los cuales como ya sabemos para todos los procesos, hace un send de los datos de un buffer a todos los demás procesos. 
Asimismo, funciona como un receive de todos datos. Todos los procesos tendrán el arreglo con los valores recolectados. Esta función de MPI se utiliza principalmente para que 
todos los procesos conozcan la cantidad de monedas de cada Mario, así como los Marios vivos que se encuentran en la simulación, los atacantes de cada Mario, así como sus 
víctimas, es decir esta función se encarga de recolectar de todos los procesos determinada información para luego agruparla en un vector al cual todos los procesos tienen 
acceso. Es de gran utilidad que todos los procesos recolecten estos datos y los tengan, debido a que las estrategias de more coins o less coins dependen de quien es el Mario que
tenga más monedas o el que tenga menos, por eso es importante realizar esta recolecciín para que cada procesos conozca bien los datos, y pueda realizar acciones entorno a la
información que se comparte entre todos. Asimismo ocurre cuando se envían enemigos a otros procesos, es necesario el uso de esta función para poder enviar al proceso víctima
los little goombas que se establecerán 10 posiciones en el mapa adelante de la posición actual del Mario víctima.

2.Posteriormente también se utiliza la función send y receive, estas son utilizadas para enviarle desde el proceso raíz 0, al proceso que se va a expectar, la estrategia que 
este deberá adaptar, recordemos que solo el hilo 0 puede leer, por lo tanto una vez que lee la estrategia decidida por el usuario, se le enviará al Mario respectivo que se desea
expectar para que este realice un set con la información obtenida para cambiar su comportamiento durante la simulación.

3. Se utiliza asimismo la función Allreduce, esto con el fin de obtener la máxima cantida de Marios vivos que se encuentran durante un determinado momento de la simulación, se 
pensó en utilizar esta función debido a que para todos los procesos, all_reduce funciona como un send de los datos de un buffer a los demás procesos. Asimismo, se realiza una 
operación de reducción sobre los datos recibidos. Donde finalmente todos los procesos tienen el resultado de la operación(suma), es decir, la cantidad de Marios vivos durante un 
momento de la partida. Una vez que este número sea igual a uno se detendrá la simulación, puesto que un Mario habrá ganado la partida al ser el último en quedar en pie.

4. Asimismo, utilizamos un reduce(MPI_Reduce funciona como un send de los datos de un buffer al proceso raíz) para enviar determinados datos específicos sobre el comportamiento 
de la partida al hilo 0, es decir el proceso raíz, para que este pueda decidir que acciones tomar con base en lo que está recibiendo de parte de otros procesos.

5.Por último también, se utiliza un broadcast para avisar al resto de procesos de la partida quien va a ser el proceso observado durante la simulación, cada vez que se elija a 
quién se va a observar. Recordando el broadcast lo que realizaba era solictiar al proceso raíz enviar la misma información a todos los demás procesos. Donde la dirección de envío
es la misma que la dirección donde los procesos que reciben guardan la información que se les es enviada.

