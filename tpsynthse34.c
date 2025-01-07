//TP Synthese 34

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
import random
import time


int main(int argc, char ** argv) {
    printf("TFTP Client \n");

    if (argc != 4){
        printf("Wrong command \n");
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo * result;
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;

    int status = getaddrinfo(argv[1],argv[2],&hints,&result);

    char ip_string[128]={0};
    char port_string[128]={0};

    getnameinfo(result->ai_addr,result->ai_addrlen,
                ip_string,128,port_string,128,
                NI_NUMERICHOST|NI_NUMERICSERV);

    printf("%s is resolved at : %s:%s",argv[1],ip_string,port_string);

    int sd = socket(result->ai_family,result->ai_socktype,
                    result->ai_protocol);

    char rrq[128]={0};
    rrq[1]=1;
    sprintf(rrq+2,"%s",argv[3]);
    sprintf(rrq+3+strlen(argv[3]),"octet");

    sendto(sd,rrq,strlen(argv[3])+9,NULL,
           result->ai_addr,result->ai_addrlen);

    freeaddrinfo(result);

    char wrq[128]={0};
    wrq[1]=1;
    sprintf(rrq+2,"%s",argv[3]);
    sprintf(rrq+3+strlen(argv[3]),"octet");

    sendto(sd,wrq,strlen(argv[3])+9,NULL,
           result->ai_addr,result->ai_addrlen);

 


/   // Fonction pour envoyer une requête RRQ avec l'option blksize au serveur
    void send_rrq_with_blksize(const char *server_ip, const char *filename, int block_size) {
    struct sockaddr_in server_addr;
    int sock;
    char rrq_packet[512];  // Paquet RRQ avec l'option blksize

    // Création du socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(69);  // Port TFTP standard
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    // Construction du paquet RRQ avec l'option blksize
    rrq_packet[0] = 0;
    rrq_packet[1] = 1;  // OpCode = 1 (RRQ)
    sprintf(rrq_packet + 2, "%s", filename);  // Nom du fichier
    sprintf(rrq_packet + 2 + strlen(filename) + 1, "blksize");  // Option blksize
    sprintf(rrq_packet + 2 + strlen(filename) + 1 + 8, "%d", block_size);  // Taille de bloc
    sprintf(rrq_packet + 2 + strlen(filename) + 1 + 8 + strlen("blksize") + 1, "octet");  // Mo

    // Envoi de la requête
    if (sendto(sock, rrq_packet, 4 + strlen(filename) + 1 + 8 + strlen("blksize") + 1 + 5, 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur lors de l'envoi de la requête");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Requête RRQ envoyée pour le fichier %s avec une taille de bloc de %d octets\n", filename, block_size);

    // Fermeture du socket
    close(sock);
}
    if (argc != 4) {
        printf("Usage : %s <IP_Serveur> <Nom_Fichier> <Taille_de_bloc_min> <Taille_de_bloc_max>\n", argv[0]);
        return 1;
    }

    int min_block_size = atoi(argv[3]);  // Taille de bloc minimum
    int max_block_size = atoi(argv[4]);  // Taille de bloc maximum

    // Tester les tailles de bloc entre min_block_size et max_block_size
    for (int block_size = min_block_size; block_size <= max_block_size; block_size *= 2) {
        // Calculer le temps avant d'envoyer la requête
        clock_t start = clock();
        
        send_rrq_with_blksize(argv[1], argv[2], block_size);  // Envoi de la requête avec la taille de bloc

        // Calculer le temps après l'envoi de la requête
        clock_t end = clock();
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("Temps de transfert avec taille de bloc %d : %f secondes\n", block_size, time_taken);
    }
    
    //Configuration des paramètres
    TOTAL_PACKETS = 10 // nombre de paquets à envoyer 
    LOSS_PROBABILITY = 0.3 // Prob de perte d'un paquet
    ERROR_PROPBABILITY = 0.1 //Prob que le paquet soit corrompu 
    MAX_RETRIES // Nombre maximal de tentatives pour un paquet perdu 
    TIMEOUT = 1  // Temps d'attente pour un acquittement

    def send_packet(packet_id):
        print(f"Envoi du paquet {packet_id}")
        time.sleep(0.5) // Simulation d'un petit délai de transmission 

        // Simuler la perte de paquet 
        if random.random() < LOSS_PROBABILITY 
        print(f"Paquet {packet_id} perdu.")
        return False // Packet perdu 

        // Si le paquet est correctement envoyé 
        if random.random() < ERROR_PROBABILITY
           print(f"Paquet {packet_id} corrompu.")
           return 'Error'

        // Si le paquet est correctement envoyé
        return True 

        // Fonction pour simuler la réception d'un acquittement ACK 
        def receive 


    return 0;
    
}

