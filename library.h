#ifndef LIBRARY_H
#define LIBRARY_H

/*librerie standard del c*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
/*system call base*/
#include <unistd.h>
/*definizioni usate dalle system call*/
#include <fcntl.h>
/*libreria segnali*/
#include <signal.h>
/*gestione errori e messaggi di errore*/
#include <errno.h>
/* non necessarie ma richieste da alcune distribuzioni unix */
#include <sys/types.h>
#include <sys/stat.h>

/*gestione socket*/
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int DEBUG; 
//mutex per la gestione dei thread
pthread_mutex_t maxThreadsMutex;
pthread_mutex_t packageMutex;

//variabile globale per la gestione dei thread
int maxThread;


typedef enum statoarticoloT {

	STORAGE			= 0,	// magazzino
	TOBEDELIVERED	= 1,	// da consegnare
	DELIVERED		= 2,	// consegnato
	COLLECTED		= 3 	// ritirato

} Status;

typedef enum commandHashTable {

	ELENCASERVER 	= 0,	
	CONSEGNATO 		= 1,
	RITIRATO		= 2,	
	SMISTA			= 3,
	ELENCA 			= 4

} Hash;

typedef struct PKG {

	char codice_articolo[32];
	char descrizione_articolo[256];
	char indirizzo_destinazione[256];
	Status stato_articolo;
	pthread_mutex_t m_lock;
	struct PKG *next;
} Package;

typedef struct tmpStruct {

	int sockfd;
	int kPackages;
	Package *handler;


} Passaggio;



void connectionManager (int sockfd, int operatorsNumber, int kPackages, Package *handler, struct sockaddr_in client, int clientsize);

Package *	createList(Package *handler, int inputFile, int tokensNumber, int status);
int 		readLine (int inputFile, char *strbuffer);
void		getTokens (char *string[], char *strbuffer, int tokensNumber);
char 	* 	getSubstr (char *result, char *input, char separator, int stepup);


void pkglist_print (Package *handler);

void pkg_print (Package *handler);

Package * getStoredPackage (Package *, int);
Package * createListA (Package *handler, int inputFD, int tokensNumber, int status);
void elencaClientToServer (int sockfd);
void elencaServerToClient (int sockfd, Package *handler);

#endif


