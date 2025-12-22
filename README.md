This project has been created as part of the 42 curriculum by adaza-ru.

Descripción

	Get Next Line es un proyecto que consiste en programar una función que lee y devuelve una línea de un file descriptor. El principal objetivo es aprender a manejar la lectura de archivos en C, gestionar memoria dinámica de manera eficiente y comprender el uso de variables estáticas para preservar el estado entre llamadas sucesivas a la función.

	La función get_next_line permite leer un archivo línea por línea, manejando diferentes tamaños de buffer definidos durante la compilación. El proyecto enseña conceptos fundamentales como la manipulación de strings, gestión de memoria y el uso del sistema de llamadas read().

Instrucciones
	
	Compilación
	Para compilar el proyecto, utiliza los siguientes comandos.

	Versión obligatoria:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl

	Versión bonus:
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus

	Ejecución
    Crea en el directorio un archivo de texto con un texto de prueba, y crea una main abriendo el archivo y con una función en bucle para leer el archivo completo, algo parecido a:

	#include <fcntl.h>
	#include <stdio.h>
	int	main()
	{
		int fd = open("archivo.txt", O_RDONLY);
		char *line;
		while ((line = get_next_line(fd)) != NULL)
		{
		    printf("%s", line);
		    free(line);
		}
		close(fd);
		return (0);
	}
	Para el bonus simplemente crea más archivos y llama read con los diferentes file descriptors.

Recursos

	P2P

	Stack Overflow
    

	Uso de IA en el proyecto:

    Clarificar conceptos teóricos: Comprender el funcionamiento de read(), file descriptors, variables estáticas y dangling pointers.

    Discusión de estructura lógica: Analizar el pseudocódigo y el flujo del programa.

    Debugging asistido: Interpretar reports de Valgrind para detectar memory leaks y segmentation faults.

    Entender errores específicos: Diagnosticar causas de segmentation faults en implementaciones iniciales.