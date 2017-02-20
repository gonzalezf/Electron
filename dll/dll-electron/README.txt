Autor: Francisco Tobar

##Las tildes fueron omitidas para evitar problemas de compatibildad##
Intrucciones de instalcion:

Se debe tener previamente instalado cmake, algun compilador de c++ y nodeJs.
Este fue probado con Visual Studio 14.

Para que ejemplo funcione es necesario tener el dll y que este en la misma ruta indicada en el archivo main.js linea 64 (puede modificar al ruta o mover el archivo).
En el directorio ejemplo de la carpeta padre de esta se ecuentra el codigo e instrucciones para compilar el dll de ejemplo.

Para configurar electron se debe:
1.- Instalar las dependencias con:
    npm install
2.- se debe recompilar las liberias ffi y ref para que sean compatibles con electron, para esto debemos ejecutar los siguientes comandos:
    //desde la carpeta que contiene el main.js
    cd node_modules\ffi
    //se deben asegurar que se tiene asignado el path de node_gyp en el sistema
    node-gyp rebuild --target=1.4.1 --dist-url=https://atom.io/download/atom-shell
    cd ..\ref
    node-gyp rebuild --target=1.4.1 --dist-url=https://atom.io/download/atom-shell
    cd ..\..

Es un programa simple de ejemplo, sus resultados no son muy relevantes pero el codigo es util para entender lo basico de la libreria ffi y su conexion con electron.
