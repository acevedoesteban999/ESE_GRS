# Proyecto ESE_GRS 
```
Este proyecto tiene como objetivo el desarrollo de una aplicación
para simular el movimiento del brazo ESE_GRS de 6 articulaciones; 
generar planos y superficies a partir de puntos, líneas y curvas 
con un acabado final en el editor 3D Autodesk Inventor. 
```
##Tipo de Conexiones
> - Puerto serie
- Sokets(Eternet o Wifi)

##Lenguaje
>C++ 

##Librerias utilizadas
> - OpenGL(Simular el brazo en un entorno 3D)
- winsock(Conexiones por Sokets)
- libxl(Comunicación de la Aplicacion con Autodesk Inventor)

Creación y mantenimiento del brazo físico:*Telegram:@ACB273*
Comunicación entre sensores y arduino:*Telegram:@Andros_Cuba_98*
Comunicación arduino PC y desarrollo de la aplicación:*Telegram:@EstebanACB2*

***Importante para el desarrollo en Visual Studio 2012***
>- Configuration Properites->General->characterSet=Not Set
- Configuration Properites->General->Common Language Runtime Support=No Common Language Runtime Support
- C/C++->General->Additional Include Directories=.../libxl/include_cpp && .../freeglut/include
- linker->General->Additional Library Directories=.../lib(For freegut && xlms)
- linker->Input->Additinal Dependencies=freeglut.dll && libxl.dll