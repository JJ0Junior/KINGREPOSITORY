#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BLOCK_DIM 1024
#define PROGRAM "writer"
//a
/**
 * @brief cCrea un nuovo processo e esegue un programma in esso
 *
 * @param program Il nome del programma da eseguire
 * @param argument Gli argomenti passati al programma
 * @return 0 se l'esecuzione ha successo nel processo figlio, -1 in caso di errore nel processo genitore
 */
 
int spawn(char program[], char* argument[])
{
 int pid;
 
 pid = fork ();
 if (pid < 0)
   return -1;
 if (pid > 0)
   return 0;
 execv(program, argument);
 abort();
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_DIM 1024
#define PROGRAM "writer"

/**
 * @brief Copia una stringa in un'altra
 *
 * @param dest La stringa di destinazione dove verrà copiata la stringa sorgente
 * @param src La stringa sorgente da copiare
 * @return Un puntatore alla stringa di destinazione
 */
 
//strcpy()

/**
 * @brief Alloca una quantità di memoria specificata
 *
 * @param size La dimensione della memoria da allocare in byte
 * @return Un puntatore alla memoria allocata, o NULL in caso di fallimento
 */
 
//malloc()

/**
 * @brief Libera la memoria precedentemente allocata da malloc, calloc o realloc
 *
 * @param ptr Il puntatore alla memoria da liberare
 */
 
//free()


/**
 * @brief Apre o crea un file per la scrittura
 *
 * @param pathname Il percorso del file da aprire o creare
 * @param flags Le opzioni di apertura del file
 * @param mode Le autorizzazioni da applicare se il file viene creato
 * @return Il file descriptor se l'operazione ha successo, altrimenti -1 in caso di errore
 */
//open()

/**
 * @brief Apre un file in una modalità specificata
 *
 * @param filename Il nome del file da aprire
 * @param mode La modalità di apertura del file
 * @return Un puntatore al FILE se l'operazione ha successo, NULL in caso di errore
 */
//fopen()

/**
 * @brief Scrive dati in un file.
 *
 * @param ptr Il puntatore ai dati da scrivere
 * @param size La dimensione di ogni elemento da scrivere in byte
 * @param nmemb Il numero di elementi da scrivere
 * @param stream Il puntatore al file di destinazione
 * @return Il numero di elementi scritti con successo
 */
//fwrite()


int main(int argc, char* argv[])
{
    FILE* file;
    int fifo;
    unsigned char buffer[BLOCK_DIM];
    int n;
    char* arg[3];

    if (argc != 3)
    {
        printf("Uso: %s file-origine file-destinazione\r\n", argv[0]);
        return 0;
    }

    arg[0] = (char*)malloc(strlen(PROGRAM) + 1);
    strcpy(arg[0], PROGRAM);
    arg[1] = (char*)malloc(strlen(argv[2]) + 1);
    strcpy(arg[1], argv[2]);
    arg[2] = NULL;

    if (spawn(PROGRAM, arg) < 0)
    {
        printf("Errore creazione processo\r\n");
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    fifo = open("my_fifo", O_WRONLY);
    if (fifo < 0)
    {
        printf("Errore apertura FIFO\r\n");
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Errore apertura file \"%s\"\r\n", argv[1]);
        close(fifo);
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
        write(fifo, buffer, n);

    fclose(file);
    close(fifo);
    free(arg[0]);
    free(arg[1]);
    return 1;
}

