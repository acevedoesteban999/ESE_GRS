# ESE_GRS v3.2.1 

Este proyecto tiene como objetivo el desarrollo de una aplicación
para simular el movimiento del brazo ESE_GRS de 6 articulaciones y 
generar superficies complejas utilizando planos y superficies a partir 
de puntos, líneas y curvas con un acabado final en el editor 3D Autodesk 
Inventor. Puede vincularse con el [ESE_GRSConnectionSimulator](https://github.com/Esteban1914/ESE_GRS_ConnectionSimulator)
para usar otros servicios.


## [Descargar ESE_GRS](https://github.com/Esteban1914/ESE_GRS/raw/master/media/ESE_GRS/ESE_GRS.rar)

![Foto de ESE_GRS](https://github.com/Esteban1914/ESE_GRS/blob/master/media/ESE_GRS.png)
![Foto de ESE_GRS](https://github.com/Esteban1914/ESE_GRS/blob/master/media/ESE_GRS1.png)

[![Video Pruebas de Lineas](https://github.com/user-attachments/assets/ec42e990-8856-42d3-9897-f8c5b3e9f17b)](https://youtube.com/shorts/k08Z69qYJ9E)
[![Video Pruebas de Uso]()](https://youtube.com/shorts/reRHz0o7SlI)

## Plataforma
>WindowsX64

## Lenguaje
>C++ 

## Librerias utilizadas
> - OpenGL(Simular el brazo en un entorno 3D)
> - winsock(Conexiones por Sockets)
> - libxl(Comunicación de la Aplicacion con Autodesk Inventor)

## Conexiones
> - Puerto Serie
> - Sockets(Eternet y Wifi)

## Sobre los desarrolladores
>***Creación y mantenimiento del brazo físico:***
> - Telegram:  @ACB273
>
>***Comunicación arduino PC y desarrollo de la aplicación:***
> - Telegram:  @EstebanACB2
> - Correo:    acevedoesteban999@gmail.com

***Importante para el desarrollo en Visual Studio 2012***
> 1. Configuration Properites->General->characterSet=Not Set
> 2. Configuration Properites->General->Common Language Runtime Support=No Common Language Runtime Support
> 3. C/C++->General->Additional Include Directories=.../libxl/include_cpp && .../freeglut/include
> 4. Linker->General->Additional Library Directories=.../freegut/lib/ && .../xlms/lib/)
> 5. Linker->Input->Additinal Dependencies=freeglut.lib && libxl.lib
