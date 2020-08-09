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

// using namespace std;

#define PORT 6658 // static TCP port of Healthcenter
#define MAXDATASIZE 1024
#define PORT_S1 22058
#define PORT_S2 22158
#define PORT_S3 22258
#define PORT_S4 22358
#define PORT_S5 22458


int main()
{

    pid_t id1 = fork(); 
    pid_t id2 = fork(); 
    pid_t id3 = fork();


    if (id1 > 0 && id2 > 0 && id3 > 0) {
        // wait(NULL);
        // wait(NULL);
        // wait(NULL);
        sleep(20);
    }
    else if (id1 == 0 && id2 > 0 && id3 > 0) {
        // wait(NULL);
        sleep(4);
        /**
         * TCP socket part of Student5
         */
        int sock_stu;
        char buf[MAXDATASIZE];
        struct sockaddr_in stu;
        
        memset(&stu, 0, sizeof stu);
        if ((sock_stu = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        stu.sin_family = AF_INET;
        stu.sin_port = htons(PORT);
        socklen_t len = sizeof(stu);
        
        if (inet_pton(AF_INET, "127.0.0.1", &stu.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_stu, (struct sockaddr *)&stu, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_stu, (struct sockaddr *)&stu, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(stu.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<Student5> has TCP port %d and IP address %s.\n", ntohs(stu.sin_port), ip);

        std::fstream inputFile;
        inputFile.open("student5.txt", std::ios::in);
        int count = 0;
        const char* stu_num = "student5_info.txt";
        send(sock_stu, stu_num, strlen(stu_num), 0);
        usleep(750);
        while (!inputFile.eof()) {
            char ch [256];
            std::string str;
            getline(inputFile, str);
            strcpy(ch, str.c_str());
            char * pt;
            pt = strtok(ch, ":");
            pt = strtok(NULL, ":");
            send(sock_stu, pt, strlen(pt), 0);
            usleep(200);
        }
        inputFile.close();
        printf("Completed sending application for <Student5>.\n");

        // char flag[1];
        // read(sock_stu, flag, 1);
        printf("<Student5> has received the reply from the health center\n");
        close(sock_stu);


        int sock_udp1;
        struct sockaddr_in servaddr1, cliaddr1;
        if ( (sock_udp1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr1, 0, sizeof(servaddr1)); 
        memset(&cliaddr1, 0, sizeof(cliaddr1)); 


        // Filling server information 
        servaddr1.sin_family = AF_INET; 
        servaddr1.sin_addr.s_addr = INADDR_ANY; 
        servaddr1.sin_port = htons(PORT_S5);

        if ( bind(sock_udp1, (const struct sockaddr *)&servaddr1,  
            sizeof(servaddr1)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr1.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The Student %d has UDP port %d and IP address %s \n", 5, PORT_S5, ip_udp);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr1);
        n = recvfrom(sock_udp1, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr1, 
                &len1); 
        buffer[n] = '\0'; 
        printf("<Student5> has received the application result, the result is : %s\n", buffer);    
        close(sock_udp1);
    }
    else if (id1 > 0 && id2 == 0 && id3 > 0) {
        // wait(NULL);
        sleep(3);
        /**
         * TCP socket part of Student4
         */
        int sock_stu;
        char buf[MAXDATASIZE];
        struct sockaddr_in stu;
        
        memset(&stu, 0, sizeof stu);
        if ((sock_stu = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        stu.sin_family = AF_INET;
        stu.sin_port = htons(PORT);
        socklen_t len = sizeof(stu);
        
        if (inet_pton(AF_INET, "127.0.0.1", &stu.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_stu, (struct sockaddr *)&stu, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_stu, (struct sockaddr *)&stu, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(stu.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<Student4> has TCP port %d and IP address %s.\n", ntohs(stu.sin_port), ip);

        std::fstream inputFile;
        inputFile.open("student4.txt",std::ios::in);
        int count = 0;
        const char* stu_num = "student4_info.txt";
        send(sock_stu, stu_num, strlen(stu_num), 0);
        usleep(750);
        while (!inputFile.eof()) {
            char ch [256];
            std::string str;
            getline(inputFile, str);
            strcpy(ch, str.c_str());
            char * pt;
            pt = strtok(ch, ":");
            pt = strtok(NULL, ":");
            send(sock_stu, pt, strlen(pt), 0);
            usleep(200);
        }
        inputFile.close();
        printf("Completed sending application for <Student4>.\n");

        char flag[1];
        read(sock_stu, flag, 1);
        printf("<Student4> has received the reply from the health center\n");
        close(sock_stu);

        int sock_udp1;
        struct sockaddr_in servaddr1, cliaddr1;
        if ( (sock_udp1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr1, 0, sizeof(servaddr1)); 
        memset(&cliaddr1, 0, sizeof(cliaddr1)); 


        // Filling server information 
        servaddr1.sin_family = AF_INET; 
        servaddr1.sin_addr.s_addr = INADDR_ANY; 
        servaddr1.sin_port = htons(PORT_S4);

        if ( bind(sock_udp1, (const struct sockaddr *)&servaddr1,  
            sizeof(servaddr1)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr1.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The Student %d has UDP port %d and IP address %s \n", 4, PORT_S4, ip_udp);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr1);
        n = recvfrom(sock_udp1, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr1, 
                &len1); 
        buffer[n] = '\0'; 
        printf("<Student4> has received the application result, the result is : %s\n", buffer);    
        close(sock_udp1);
    }
    else if (id1 > 0 && id2 > 0 && id3 == 0) {
        // wait(NULL);
        sleep(2);
        /**
         * TCP socket part of Student3
         */
        int sock_stu;
        char buf[MAXDATASIZE];
        struct sockaddr_in stu;
        
        memset(&stu, 0, sizeof stu);
        if ((sock_stu = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        stu.sin_family = AF_INET;
        stu.sin_port = htons(PORT);
        socklen_t len = sizeof(stu);
        
        if (inet_pton(AF_INET, "127.0.0.1", &stu.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_stu, (struct sockaddr *)&stu, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_stu, (struct sockaddr *)&stu, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(stu.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<Student3> has TCP port %d and IP address %s.\n", ntohs(stu.sin_port), ip);

        std::fstream inputFile;
        inputFile.open("student3.txt",std::ios::in);
        int count = 0;
        const char* stu_num = "student3_info.txt";
        send(sock_stu, stu_num, strlen(stu_num), 0);
        usleep(750);
        while (!inputFile.eof()) {
            char ch [256];
            std::string str;
            getline(inputFile, str);
            strcpy(ch, str.c_str());
            char * pt;
            pt = strtok(ch, ":");
            pt = strtok(NULL, ":");
            send(sock_stu, pt, strlen(pt), 0);
            usleep(200);
        }
        inputFile.close();
        printf("Completed sending application for <Student3>.\n");

        char flag[1];
        read(sock_stu, flag, 1);
        printf("<Student3> has received the reply from the health center\n");
        close(sock_stu);


        int sock_udp1;
        struct sockaddr_in servaddr1, cliaddr1;
        if ( (sock_udp1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr1, 0, sizeof(servaddr1)); 
        memset(&cliaddr1, 0, sizeof(cliaddr1)); 


        // Filling server information 
        servaddr1.sin_family = AF_INET; 
        servaddr1.sin_addr.s_addr = INADDR_ANY; 
        servaddr1.sin_port = htons(PORT_S3);

        if ( bind(sock_udp1, (const struct sockaddr *)&servaddr1,  
            sizeof(servaddr1)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr1.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The Student %d has UDP port %d and IP address %s \n", 3, PORT_S3, ip_udp);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr1);
        n = recvfrom(sock_udp1, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr1, 
                &len1); 
        buffer[n] = '\0'; 
        printf("<Student3> has received the application result, the result is : %s\n", buffer);    
        close(sock_udp1);
    }
    else if (id1 == 0 && id2 == 0 && id3 > 0) {
        // wait(NULL);
        sleep(1);
        /**
         * TCP socket part of Student2
         */
        int sock_stu;
        char buf[MAXDATASIZE];
        struct sockaddr_in stu;
        
        memset(&stu, 0, sizeof stu);
        if ((sock_stu = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        stu.sin_family = AF_INET;
        stu.sin_port = htons(PORT);
        socklen_t len = sizeof(stu);
        
        if (inet_pton(AF_INET, "127.0.0.1", &stu.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_stu, (struct sockaddr *)&stu, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_stu, (struct sockaddr *)&stu, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(stu.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<Student2> has TCP port %d and IP address %s.\n", ntohs(stu.sin_port), ip);
        printf("Completed sending application for <Student>\n");

        std::fstream inputFile;
        inputFile.open("student2.txt",std::ios::in);
        int count = 0;
        const char* stu_num = "student2_info.txt";
        send(sock_stu, stu_num, strlen(stu_num), 0);
        usleep(750);
        while (!inputFile.eof()) {
            char ch [256];
            std::string str;
            getline(inputFile, str);
            strcpy(ch, str.c_str());
            char * pt;
            pt = strtok(ch, ":");
            pt = strtok(NULL, ":");
            send(sock_stu, pt, strlen(pt), 0);
            usleep(200);
        }
        inputFile.close();

        char flag[1];
        read(sock_stu, flag, 1);
        printf("<Student2> has received the reply from the health center");
        close(sock_stu);


        int sock_udp1;
        struct sockaddr_in servaddr1, cliaddr1;
        if ( (sock_udp1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr1, 0, sizeof(servaddr1)); 
        memset(&cliaddr1, 0, sizeof(cliaddr1)); 


        // Filling server information 
        servaddr1.sin_family = AF_INET; 
        servaddr1.sin_addr.s_addr = INADDR_ANY; 
        servaddr1.sin_port = htons(PORT_S2);

        if ( bind(sock_udp1, (const struct sockaddr *)&servaddr1,  
            sizeof(servaddr1)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr1.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The Student %d has UDP port %d and IP address %s \n", 2, PORT_S2, ip_udp);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr1);
        n = recvfrom(sock_udp1, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr1, 
                &len1); 
        buffer[n] = '\0'; 
        printf("<Student2> has received the application result, the result is : %s\n", buffer);    
        close(sock_udp1);
    }
    else if (id1 > 0 && id2 == 0 && id3 == 0) {
        /**
         * TCP socket part of Student1
         */
        int sock_stu;
        char buf[MAXDATASIZE];
        struct sockaddr_in stu;
        
        memset(&stu, 0, sizeof stu);
        if ((sock_stu = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        stu.sin_family = AF_INET;
        stu.sin_port = htons(PORT);
        socklen_t len = sizeof(stu);
        
        if (inet_pton(AF_INET, "127.0.0.1", &stu.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock_stu, (struct sockaddr *)&stu, len) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        if (getsockname(sock_stu, (struct sockaddr *)&stu, &len) == -1)
        {
            perror("getsockname");
        }


        char ip[1024];
        inet_ntop(AF_INET, &(stu.sin_addr), ip, INET_ADDRSTRLEN);
        printf("<Student1> has TCP port %d and IP address %s.\n", ntohs(stu.sin_port), ip);
        printf("Student1 is now connected to health center.\n");

        std::fstream inputFile;
        inputFile.open("student1.txt",std::ios::in);
        int count = 0;
        const char* stu_num = "student1_info.txt";
        send(sock_stu, stu_num, strlen(stu_num), 0);
        usleep(750);
        while (!inputFile.eof()) {
            char ch [256];
            std::string str;
            std::getline(inputFile, str);
            strcpy(ch, str.c_str());
            char * pt;
            pt = strtok(ch, ":");
            pt = strtok(NULL, ":");
            send(sock_stu, pt, strlen(pt), 0);
            usleep(200);
        }
        inputFile.close();

        char flag[1];
        read(sock_stu, flag, 1);
        printf("<Student1> has received the reply from the health center");
        close(sock_stu);



        int sock_udp1;
        struct sockaddr_in servaddr1, cliaddr1;
        if ( (sock_udp1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        memset(&servaddr1, 0, sizeof(servaddr1)); 
        memset(&cliaddr1, 0, sizeof(cliaddr1)); 


        // Filling server information 
        servaddr1.sin_family = AF_INET; 
        servaddr1.sin_addr.s_addr = INADDR_ANY; 
        servaddr1.sin_port = htons(PORT_S1);

        if ( bind(sock_udp1, (const struct sockaddr *)&servaddr1,  
            sizeof(servaddr1)) < 0 ) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        char ip_udp[1024];
        inet_ntop(AF_INET, &(servaddr1.sin_addr), ip_udp, INET_ADDRSTRLEN);
        printf("The Student %d has UDP port %d and IP address %s \n", 1, PORT_S1, ip_udp);

        char buffer[1024];
        int n;
        socklen_t len1 = sizeof(cliaddr1);
        n = recvfrom(sock_udp1, (char *)buffer, 1024,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr1, 
                &len1); 
        buffer[n] = '\0'; 
        printf("<Student1> has received the application result, the result is : %s\n", buffer);
        close(sock_udp1);
    }



}
