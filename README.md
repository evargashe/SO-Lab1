## SO-Lab1
## Para el productor
Primero tenemos nuestra estructura que es llamado region :
### `struct region{`
    `int len;`
    `char buf[MAX_LEN];`
`};`

la cual no servira para poder crear un memoria compartida.
Usamos la funcion shm_open() que nos servira para crear y abrir un objeto de
memoria compartido y ademas en este espacio podremos leer y escribir a la vez.
Y la funcion ftruncate sera para configurar el tamaño de la funcion shm_open,
Dentro del while infinito  creamos varias procesos con la funcion fork() de c,
y si al crear el valor nos da 0 entramos a la funcion hijo, dentro del proceso hijo 
calculamos el tiempo en que fue creado con algunas funciones de c como timespec y clock_gettime, 
Ademas de eso dentro del proceso hijo en el buff de nuestra estructura almacenamos los procesos 
creados en cada iteracion y tambien con la ayuda de la funcion mmap() crea una nueva asignación 
en el espacio de direcciones virtuales de la proceso de llamada.
Y cuando el valor de fork es mayor a 0 entramos a la funcion padre, al igual que la funcion hijo 
calculamos el tiempo en que fue creado y tambien mapeamos nuestra direccion de espacio.

## Para el consumidor
Tambien usamos para funcion shm_open() para crear un espacio de memoria pero con la condicion
de que solo podremos leer osea imprimir la informacion.
Tambien haremos un mapeo a nuestra region pero solo sera de lectura.
En el while eliminaremos todas los procesos creados en el productor mostrando antes el PID del proceso
y finalmente eliminamos.

