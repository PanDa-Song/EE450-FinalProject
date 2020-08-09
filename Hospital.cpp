#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>
#include <sys/wait.h>

#define PORT 6658     // the static TCP port of Healthcenter
#define MAXDATASIZE 1024 // max number of bytes we can get at once

#define PORT_H1 21758
#define PORT_H2 21858
#define PORT_H3 21958


int main(int argc, char *argv[])
{
    pid_t id1 = fork(); 
    pid_t id2 = fork(); 
    if (id1 > 0 && id2 > 0) { 
        wait(NULL);
        sleep(30);
    } 

    // Hospital C
    else if (id1 == 0 && id2 > 0) { 
  
        sleep(4); 
  

        int sock_hosp, numbytes;
        char buf[MAXDATASIZE];
        struct sockaddr_in hosp;
        
        memset(&hosp, 0, sizeof hosp);
        if ((sock_hosp = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        hosp.sin_family = AF_INET;
        hosp.sin_port = htons(PORT);
        socklen_t len = sizeof(hosp);
        
        if (inet_pton(AF_INET, "127.0.0.1", &hosp.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_hosp, (struct sockaddr *)&hosp, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_hosp, (struct sockaddr *)&hosp, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(hosp.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<HospitalC> has TCP port %d and IP address %s for Phase 1.\n", ntohs(hosp.sin_port), ip);
        printf("HospitalC is now connected to health center.\n");

        std::fstream inputFile;
        inputFile.open("HospitalC.txt",std::ios::in);
        int count = 1;
        usleep(500);
        while (count <= 3) {
            char ch [256];
            inputFile.getline(ch, '\n');
            send(sock_hosp, ch, strlen(ch), 0);
            printf("<Hospital C> has sent C%d to the health center\n", count);
            usleep(200);
            count++;
        }
        inputFile.close();
        printf("Updating the health center is done for <Hospital C>\n");
        printf("End of Phase 1 for <Hospital C>\n");
        close(sock_hosp);


        // phase 2 --- UDP part
        int sock_udp;
        struct sockaddr_in servaddr, cliaddr;
        if ( (sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr, 0, sizeof(servaddr)); 
        memset(&cliaddr, 0, sizeof(cliaddr)); 

        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        servaddr.sin_port = htons(PORT_H3);

        if ( bind(sock_udp, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The HospitalC has UDP port %d and IP address %s \n", PORT_H3, ip);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr);
        n = recvfrom(sock_udp, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len1); 
        buffer[n] = '\0'; 
        printf("%s has been admitted to <Hospital C> \n", buffer);  
  
        close(sock_udp);

    } 
  
    // Hospital B
    else if (id1 > 0 && id2 == 0) { 
        // sleep the process for 1 second 
        sleep(2); 




        int sock_hosp, numbytes;
        char buf[MAXDATASIZE];
        struct sockaddr_in hosp;
        
        memset(&hosp, 0, sizeof hosp);
        if ((sock_hosp = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        hosp.sin_family = AF_INET;
        hosp.sin_port = htons(PORT);
        socklen_t len = sizeof(hosp);
        
        if (inet_pton(AF_INET, "127.0.0.1", &hosp.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_hosp, (struct sockaddr *)&hosp, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_hosp, (struct sockaddr *)&hosp, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(hosp.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<HospitalB> has TCP port %d and IP address %s for Phase 1.\n", ntohs(hosp.sin_port), ip);
        printf("HospitalB is now connected to health center.\n");


        std::fstream inputFile;
        inputFile.open("HospitalB.txt",std::ios::in);
        int count = 1;
        usleep(500);
        while (count <= 3) {
            char ch [256];
            inputFile.getline(ch, '\n');
            send(sock_hosp, ch, strlen(ch), 0);
            printf("<Hospital B> has sent B%d to the health center\n", count);
            usleep(200);
            count++;
        }
        inputFile.close();
        printf("Updating the health center is done for <Hospital B>\n");
        printf("End of Phase 1 for <Hospital B>\n");
        close(sock_hosp);

        // phase 2 --- UDP part
        int sock_udp;
        struct sockaddr_in servaddr, cliaddr;
        if ( (sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr, 0, sizeof(servaddr)); 
        memset(&cliaddr, 0, sizeof(cliaddr)); 

        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        servaddr.sin_port = htons(PORT_H2);

        if ( bind(sock_udp, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The HospitalB has UDP port %d and IP address %s \n", PORT_H2, ip);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr);
        n = recvfrom(sock_udp, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len1); 
        buffer[n] = '\0'; 
        printf("%s has been admitted to <Hospital B> \n", buffer);  
        
  
        close(sock_udp);
    } 
  
    // Hospital A
    else { 
        // phase 1 --- TCP part
        int sock_hosp, numbytes;
        char buf[MAXDATASIZE];
        struct sockaddr_in hosp;
        
        memset(&hosp, 0, sizeof hosp);
        if ((sock_hosp = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        hosp.sin_family = AF_INET;
        hosp.sin_port = htons(PORT);
        socklen_t len = sizeof(hosp);
        
        if (inet_pton(AF_INET, "127.0.0.1", &hosp.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_hosp, (struct sockaddr *)&hosp, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_hosp, (struct sockaddr *)&hosp, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(hosp.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<HospitalA> has TCP port %d and IP address %s for Phase 1.\n", ntohs(hosp.sin_port), ip);
        printf("HospitalA is now connected to health center.\n");
        
        std::fstream inputFile;
        inputFile.open("HospitalA.txt",std::ios::in);
        int count = 1;
        usleep(500);
        while (count <= 3) {
            char ch [256];
            inputFile.getline(ch, '\n');
            send(sock_hosp, ch, strlen(ch), 0);
            printf("<Hospital A> has sent A%d to the health center\n", count);
            usleep(200);
            count++;
        }
        inputFile.close();
        printf("Updating the health center is done for <Hospital A>\n");
        printf("End of Phase 1 for <Hospital A>\n");
        close(sock_hosp);



        // phase 2 --- UDP part
        int sock_udp;
        struct sockaddr_in servaddr, cliaddr;
        if ( (sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr, 0, sizeof(servaddr)); 
        memset(&cliaddr, 0, sizeof(cliaddr)); 

        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        servaddr.sin_port = htons(PORT_H1);

        if ( bind(sock_udp, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The HospitalA has UDP port %d and IP address %s \n", PORT_H1, ip);

        while(1){
            char buffer[1024];
            int n;
            socklen_t len1 = sizeof(cliaddr);
            n = recvfrom(sock_udp, (char *)buffer, 1024,  
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len1); 
            buffer[n] = '\0'; 
            printf("%s has been admitted to <Hospital A> \n", buffer);  
        }
  
        close(sock_udp);


    } 

    
    return 0;
}