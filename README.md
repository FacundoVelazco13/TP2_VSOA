# TP2_VSOA
Trabajo practico 2 Virtualizacion de sistemas operativos avanzados.

# Modo de uso :

Dentro del directorio *ejecutables* se encuentran las carpetas : 
#### client
#### servAuth
#### servInteract

cada carpeta guarda un ejecutable y los archivos necesarios, en los ultimos dos casos.

Se puede copiar cada directorio dentro de un container y realizar pruebas.

Ejemplo auth (local) : ./clientSRPC -a 127.0.0.1 -u FacundoVelazco -p facu123

//*cambiar por ip del container*

Ejemplo rpc (local) : ./clientSRPC -a localhost -t token123 -o w -c "un contenidooo"

//*Cambiar la ip, como en el caso anterior, la opcion w (write) es la unica que hay*
