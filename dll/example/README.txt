Autor: Francisco Tobar

##Las tildes fueron omitidas para evitar problemas de compatibildad##
Intrucciones de instalcion:

Se debe tener previamente instalado cmake, algun compilador de c++ y nodeJs.
Este fue probado con Visual Studio 14.

El archivo cuenta con cmake para ser compilado se debe:

1.- Primero generar los archivos para compilar a traves de comand cmake build, se recomienda hacer esto dentro una carpeta
build para mantener el orden.
 Se debe ejecutar cmake build $ruta al directorio raiz$ si lo hará en otra carpeta. Por ejemplo, al hacerlo en un carpeta build dentro del directorio raiz*
se debe ejecutar ** , cmake build ..

* El directorio raiz es la carpeta 3D-NNSearch que contiene el CmakeList.txt
** Al momento de ejecutar el cmake se debe comprobar que se escoga la misma arquitectura que la del node instalado, cmake escoge 32bits por defecto, esto se puede hacer mediante la flag -G "visual Studio XX XXXX win 64" para 64 bits.
2.- Dentro del direcotrio donde se ejecuto el comando anterior se debe ejucutar el comando cmake --build . --config Release
3.- De salir todo bien se deberia haber generado un carpeta bin el directorio raiz el cual contiene el ejecutable.

Una vez compilado todo es necesario instalar las dependencias de node a traves del comando en la carpeta raiz:

npm install

El programa debe ejecutarse mediante el comando:

node example.js

Es un programa simple de ejemplo, sus resultados no son muy relevantes pero el codigo es util para entender lo basico de la libreria ffi.
Se recomienda revisar los archivos:
-C_src/Bindings.cpp
-C_src/Bindings.h
-C_src/basicHandler.cpp
-C_src/basicHandler.h
-example.js

para entender su funcionamiento
