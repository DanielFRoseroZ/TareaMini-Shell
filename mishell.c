#include "leercadena.h"
#include <assert.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char command[256];
    char **comando;

    char *tareas[100];    // Creamos un array de caracteres para mostrar los procesos creados.
    int tareaid = 0;      // Definimos la variable tareaid para manejar la posicion de las tareas dentro de nuestro arreglo "tareas".
    int segundoPlano = 0; // definimos la variable segundo plano para poder seguir las tareas que mandamos a segundo plano.
    int pid[100];         // En este array almacenamos el id de los procesos.

    while (1)
    {
        int i;
        printf(" -> ");
        leer_de_teclado(256, command);

        //Termina de correr la linea de comandos al recibir la orden "Salir".
        if (strcmp(command, "salir") == 0)
        {
            kill(0, SIGKILL);
        }

        comando = de_cadena_a_vector(command);
        i = 0;

        while (comando[i])
        {
            i++;
        }
        pid_t wpid;
        //Condicional que identifica si en la orden se encuentra un "&"
        segundoPlano = 0;
        if (strcmp(comando[i - 1], "&") == 0)
        {
            segundoPlano = 1;
            comando[i - 1] = NULL;

            tareas[tareaid] = (char *)malloc(sizeof(char) * 257);
            strcpy(tareas[tareaid], command);
        }
        //Definición del comando "tareas"
        if (strcmp(command, "tareas") == 0)
        {
            if (tareas[0])
            {
                for (int i = 0; y < tareaid; i++)
                {
                    printf("[%i]", pid[i]);
                    printf(" %s\n", tareas[i]);
                }
            }
        }

        i = 0;

        int x;
        //Proceso Hijo
        wpid = fork();
        //Definición del comando detener.
        if (strcmp(comando[0], "detener") == 0)
        {
            int procesoIdDetener = atoi(comando[1]);
            kill(procesoIdDetener, SIGKILL);
            for (int s = 0; s < tareaid; s++)
            {
                if (pid[s] == procesoIdDetener)
                {
                    printf("<< deteniendo proceso >>");
                    for (int contador = s; contador < tareaid; contador++)
                    {
                        strcpy(tareas[contador], tareas[contador + 1]);
                        pid[contador] = pid[contador + 1];
                    }
                    break;
                }
            }
            printf("\n<< El proceso se ha detenido correctamente >>");
        }

        assert(wpid >= 0);
        //Desliga la ejecución del proceso hijo de la ejecución del proceso padre.
        if (wpid == 0) 
        {
            execvp(comando[0], comando);
            printf("\n -> ");
        }
        else
        {
            if (segundoPlano == 0)
            {
                waitpid(wpid, &x, 0);
                printf(" -> ");
            }
            else
            {
                pid[tareaid] = wpid;
                tareaid++;
                printf("Ejecución en segundo plano\n");
                printf(" -> ");
            }
        }
    }

    return 0;
}