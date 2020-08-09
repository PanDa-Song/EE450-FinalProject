#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

#define PORT 6658 // Static TCP port of Healthcenter

#define PORT_H1 21758
#define PORT_H2 21858
#define PORT_H3 21958
#define PORT_S1 22058
#define PORT_S2 22158
#define PORT_S3 22258
#define PORT_S4 22358
#define PORT_S5 22458

void store_hosp_info(char *dep1, char *dep2, char *dep3, int sock)
{

    FILE *fp = NULL;
    fp = fopen("hosp_info.txt", "a");
    fputs(dep1, fp);
    fputc('\n', fp);
    read(sock, dep2, 1024);
    fputs(dep2, fp);
    fputc('\n', fp);
    read(sock, dep3, 1024);
    fputs(dep3, fp);
    fputc('\n', fp);
    fclose(fp);
}

void store_stu_info(const char *stu, int sock)
{
    char symp[1024];
    char interest[2];
    char student[256];
    int n;
    FILE *fp = NULL;
    fp = fopen(stu, "a");
    read(sock, symp, 1024);
    fputs(symp, fp);
    fputc('\n', fp);
    read(sock, interest, 1024);
    fputs(interest, fp);
    fputc('\n', fp);
    if ((n = read(sock, interest, 1024)) > 0)
    {
        fputs(interest, fp);
        fputc('\n', fp);
    }
    if ((n = read(sock, interest, 1024)) > 0)
    {
        fputs(interest, fp);
        fputc('\n', fp);
    }
    fclose(fp);
    memcpy(student, stu, 8);
    printf("health center receive the application from <%s>\n", student);
}

void read_hosp(char *ch, char *pt, int d[2])
{
    pt = strtok(ch, "#");
    pt = strtok(NULL, ",");
    sscanf(pt, "%d", &d[0]);
    pt = strtok(NULL, ",");
    sscanf(pt, "%d", &d[1]);
}

void stu_udp(int stu_tag, int port, std::string stu[3], int symptom,
             int a1[2], int a2[2], int a3[2],
             int b1[2], int b2[2], int b3[2],
             int c1[2], int c2[2], int c3[2])
{

    int sock_stu;
    struct sockaddr_in stu_addr;
    if ((sock_stu = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&stu_addr, 0, sizeof(stu_addr));

    stu_addr.sin_family = AF_INET;
    stu_addr.sin_port = htons(port);
    stu_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(stu_addr);

    int cmp_flag = 0;
    for (int i = 0; i < 3; i++)
    {
        if (strncmp(stu[i].c_str(), "A1", 2) == 0)
        {
            if (symptom >= a1[0] && symptom <= a1[1])
            {

                sendto(sock_stu, "Accept#A1#hospitalA", strlen("Accept#A1#hospitalA"), 0, (struct sockaddr *)&stu_addr, sizeof(stu_addr));
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "A2", 2) == 0)
        {
            if (symptom >= a2[0] && symptom <= a2[1])
            {
                sendto(sock_stu, "Accept#A2#hospitalA", strlen("Accept#A2#hospitalA"), 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "A3", 2) == 0)
        {
            if (symptom >= a3[0] && symptom <= a3[1])
            {
                sendto(sock_stu, "Accept#A3#hospitalA", strlen("Accept#A3#hospitalA"), 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "B1", 2) == 0)
        {
            if (symptom >= b1[0] && symptom <= b1[1])
            {
                sendto(sock_stu, "Accept#B1#hospitalB", strlen("Accept#B1#hospitalB") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "B2", 2) == 0)
        {
            if (symptom >= b2[0] && symptom <= b2[1])
            {
                sendto(sock_stu, "Accept#B2#hospitalB", strlen("Accept#B2#hospitalB") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "B3", 2) == 0)
        {
            if (symptom >= b3[0] && symptom <= b3[1])
            {
                sendto(sock_stu, "Accept#B3#hospitalB", strlen("Accept#B3#hospitalB") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "C1", 2) == 0)
        {
            if (symptom >= c1[0] && symptom <= c1[1])
            {
                sendto(sock_stu, "Accept#C1#hospitalC", strlen("Accept#C1#hospitalC") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "C2", 2) == 0)
        {
            if (symptom >= c1[0] && symptom <= c1[1])
            {
                sendto(sock_stu, "Accept#C2#hospitalC", strlen("Accept#C2#hospitalC") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
        else if (strncmp(stu[i].c_str(), "C3", 2) == 0)
        {
            if (symptom >= c1[0] && symptom <= c1[1])
            {
                sendto(sock_stu, "Accept#C3#hospitalC", strlen("Accept#C3#hospitalC") + 1, 0, (struct sockaddr *)&stu_addr, sizeof stu_addr);
                cmp_flag = 1;
                if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
                {
                    perror("getsockname");
                }
                char udp_ip[1024];
                inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
                printf("The health center has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
                break;
            }
        }
    }
    if (cmp_flag == 0)
    {
        sendto(sock_stu, "Reject", strlen("Reject"), 0, (const struct sockaddr *)&stu_addr, sizeof(stu_addr));
        if (getsockname(sock_stu, (struct sockaddr *)&stu_addr, &len) == -1)
        {
            perror("getsockname");
        }
        char udp_ip[1024];
        inet_ntop(AF_INET, &(stu_addr.sin_addr), udp_ip, INET_ADDRSTRLEN);
        printf("The health center  has UDP port %d and IP address %s for Phase 2 - Student%d\n", ntohs(stu_addr.sin_port), udp_ip, stu_tag);
    }

    printf("The health center has send the application result to <Student%d>\n", stu_tag);
    close(sock_stu);
}

std::string to_string(int x)
{
    std::stringstream stream;
    stream << x;
    return stream.str();
}

int main(void)
{

    int server_fd, new_fd, valread;
    struct sockaddr_in address, cliaddr;
    int opt = 1;
    pid_t childpid;
    socklen_t clilen;

    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 6658

    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
    //                &opt, sizeof(opt)))
    // {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 4658
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    char ip[1024];
    inet_ntop(AF_INET, &(address.sin_addr), ip, INET_ADDRSTRLEN);
    printf("The health center has TCP port %d and IP address %s \n", PORT, ip);

    // store interest for each student
    std::string stu1[3], stu2[3], stu3[3], stu4[3], stu5[3];
    // store the hospital departments
    std::vector<std::string> total_departments;
    // store acceptable symptom range of each hospital department
    int a1[2], a2[2], a3[2], b1[2], b2[2], b3[2], c1[2], c2[2], c3[2];
    int hosp_count = 0;
    int status;
    int flag_count = 0;
    // accept loop for Hospital
    while (1)
    {
        if (hosp_count == 3)
        {
            break;
        }
        clilen = sizeof(cliaddr);
        //accept a connection
        new_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &clilen);
        if ((childpid = fork()) == -1)
        {
            close(new_fd);
            continue;
        }
        else if (childpid > 0)
        {
            close(new_fd);
            wait(NULL);
            if (hosp_count == 3)
                exit(1);
            break;
        }
        else if (childpid == 0)
        { //if it’s 0, it’s child process

            char dep1[1024];
            char dep2[1024];
            char dep3[1024];

            read(new_fd, dep1, 1024);
            if (strncmp(dep1, "A", 1) == 0)
            {
                store_hosp_info(dep1, dep2, dep3, new_fd);
                printf("Received the deparrtment list from <Hospital A>\n");
            }
            else if (strncmp(dep1, "B", 1) == 0)
            {
                store_hosp_info(dep1, dep2, dep3, new_fd);

                printf("Received the deparrtment list from <Hospital B>\n");
            }
            else if (strncmp(dep1, "C", 1) == 0)
            {
                store_hosp_info(dep1, dep2, dep3, new_fd);

                printf("Received the deparrtment list from <Hospital C>\n");
            }
            memset(dep1, '\0', sizeof(dep1));
            memset(dep2, '\0', sizeof(dep2));
            memset(dep3, '\0', sizeof(dep3));
        }
        //close socket of the server
        close(new_fd);
        hosp_count++;
    }
    printf("End of Phase 1 for the health center\n");

    int stu_count = 0;
    // accept loop for Students
    while (1)
    {
        if (stu_count == 5)
        {
            break;
        }
        clilen = sizeof(cliaddr);
        new_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &clilen);
        if ((childpid = fork()) == -1)
        {
            close(new_fd);
            continue;
        }
        else if (childpid > 0)
        {
            close(new_fd);
            wait(NULL);
            wait(NULL);
        }
        else if (childpid == 0)
        {

            char stu_num[1024];
            read(new_fd, stu_num, 1024);

            store_stu_info(stu_num, new_fd);
            send(new_fd, "1", strlen("1"), 0);
        }
        close(new_fd);
        stu_count++;
    }

    if (childpid > 0)
    {
        std::fstream hospfile;
        hospfile.open("hosp_info.txt", std::ios::in);
        int tag = 1;
        while (!hospfile.eof())
        {
            char ch[256];
            std::string str;
            getline(hospfile, str);
            strcpy(ch, str.c_str());
            char *pt;
            if (tag == 1)
            {
                read_hosp(ch, pt, a1);
            }
            else if (tag == 2)
            {
                read_hosp(ch, pt, a2);
            }
            else if (tag == 3)
            {
                read_hosp(ch, pt, a3);
            }
            else if (tag == 4)
            {
                read_hosp(ch, pt, b1);
            }
            else if (tag == 5)
            {
                read_hosp(ch, pt, b2);
            }
            else if (tag == 6)
            {
                read_hosp(ch, pt, b3);
            }
            else if (tag == 7)
            {
                read_hosp(ch, pt, c1);
            }
            else if (tag == 8)
            {
                read_hosp(ch, pt, c2);
            }
            else if (tag == 9)
            {
                read_hosp(ch, pt, c3);
            }

            tag++;
        }
        hospfile.close();
        // store symptom for each student
        int symptom_s1, symptom_s2, symptom_s3, symptom_s4, symptom_s5;

        std::fstream stu_file;
        stu_file.open("student1_info.txt", std::ios::in);
        int test = -1;
        while (!stu_file.eof())
        {
            char ch[256];
            std::string str;
            getline(stu_file, str);
            strcpy(ch, str.c_str());
            if (test == -1)
            {
                sscanf(ch, "%d", &symptom_s1);
            }
            else
            {
                stu1[test] = str;
            }
            test++;
        }
        stu_file.close();

        stu_file.open("student2_info.txt", std::ios::in);
        test = -1;
        while (!stu_file.eof())
        {
            char ch[256];
            std::string str;
            getline(stu_file, str);
            strcpy(ch, str.c_str());
            if (test == -1)
            {
                sscanf(ch, "%d", &symptom_s2);
            }
            else
            {
                stu2[test] = str;
            }
            test++;
        }
        stu_file.close();

        stu_file.open("student3_info.txt", std::ios::in);
        test = -1;
        while (!stu_file.eof())
        {
            char ch[256];
            std::string str;
            getline(stu_file, str);
            strcpy(ch, str.c_str());
            if (test == -1)
            {
                sscanf(ch, "%d", &symptom_s3);
            }
            else
            {
                stu3[test] = str;
            }
            test++;
        }
        stu_file.close();

        stu_file.open("student4_info.txt", std::ios::in);
        test = -1;
        while (!stu_file.eof())
        {
            char ch[256];
            std::string str;
            getline(stu_file, str);
            strcpy(ch, str.c_str());
            if (test == -1)
            {
                sscanf(ch, "%d", &symptom_s4);
            }
            else
            {
                stu4[test] = str;
            }
            test++;
        }
        stu_file.close();
        stu_file.open("student5_info.txt", std::ios::in);
        test = -1;
        while (!stu_file.eof())
        {
            char ch[256];
            std::string str;
            getline(stu_file, str);
            strcpy(ch, str.c_str());
            if (test == -1)
            {
                sscanf(ch, "%d", &symptom_s5);
            }
            else
            {
                stu5[test] = str;
            }
            test++;
        }
        stu_file.close();

        stu_udp(1, PORT_S1, stu1, symptom_s1,
                a1, a2, a3, b1, b2, b3, c1, c2, c3);
        stu_udp(2, PORT_S2, stu2, symptom_s2,
                a1, a2, a3, b1, b2, b3, c1, c2, c3);
        stu_udp(3, PORT_S3, stu3, symptom_s3,
                a1, a2, a3, b1, b2, b3, c1, c2, c3);
        stu_udp(4, PORT_S4, stu4, symptom_s4,
                a1, a2, a3, b1, b2, b3, c1, c2, c3);
        stu_udp(5, PORT_S5, stu5, symptom_s5,
                a1, a2, a3, b1, b2, b3, c1, c2, c3);

        std::vector<std::string> res1;
        std::vector<std::string> res2;
        std::vector<std::string> res3;

        for (int i = 0; i < 3; i++)
        {
            if (strncmp(stu1[i].c_str(), "A1", 2) == 0)
            {
                if (symptom_s1 >= a1[0] && symptom_s1 <= a1[1])
                {
                    res1.push_back("Student1#" + to_string(symptom_s1) + "#A1");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "A2", 2) == 0)
            {
                if (symptom_s1 >= a2[0] && symptom_s1 <= a2[1])
                {
                    res1.push_back("Student1#" + to_string(symptom_s1) + "#A2");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "A3", 2) == 0)
            {
                if (symptom_s1 >= a3[0] && symptom_s1 <= a3[1])
                {
                    res1.push_back("Student1#" + to_string(symptom_s1) + "#A3");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "B1", 2) == 0)
            {
                if (symptom_s1 >= b1[0] && symptom_s1 <= b1[1])
                {
                    res2.push_back("Student1#" + to_string(symptom_s1) + "#B1");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "B2", 2) == 0)
            {
                if (symptom_s1 >= b2[0] && symptom_s1 <= b2[1])
                {
                    res2.push_back("Student1#" + to_string(symptom_s1) + "#B2");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "B3", 2) == 0)
            {
                if (symptom_s1 >= b3[0] && symptom_s1 <= b3[1])
                {
                    res2.push_back("Student1#" + to_string(symptom_s1) + "#B3");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "C1", 2) == 0)
            {
                if (symptom_s1 >= c1[0] && symptom_s1 <= c1[1])
                {
                    res3.push_back("Student1#" + to_string(symptom_s1) + "#C1");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "C2", 2) == 0)
            {
                if (symptom_s1 >= c2[0] && symptom_s1 <= c2[1])
                {
                    res3.push_back("Student1#" + to_string(symptom_s1) + "#C2");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "C3", 2) == 0)
            {
                if (symptom_s1 >= c3[0] && symptom_s1 <= c3[1])
                {
                    res3.push_back("Student1#" + to_string(symptom_s1) + "#C3");
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(stu2[i].c_str(), "A1", 2) == 0)
            {
                if (symptom_s2 >= a1[0] && symptom_s2 <= a1[1])
                {
                    res1.push_back("Student2#" + to_string(symptom_s2) + "#A1");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "A2", 2) == 0)
            {
                if (symptom_s2 >= a2[0] && symptom_s2 <= a2[1])
                {
                    res1.push_back("Student2#" + to_string(symptom_s2) + "#A2");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "A3", 2) == 0)
            {
                if (symptom_s2 >= a3[0] && symptom_s2 <= a3[1])
                {
                    res1.push_back("Student2#" + to_string(symptom_s2) + "#A3");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "B1", 2) == 0)
            {
                if (symptom_s2 >= b1[0] && symptom_s2 <= b1[1])
                {
                    res2.push_back("Student2#" + to_string(symptom_s2) + "#B1");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "B2", 2) == 0)
            {
                if (symptom_s2 >= b2[0] && symptom_s2 <= b2[1])
                {
                    res2.push_back("Student2#" + to_string(symptom_s2) + "#B2");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "B3", 2) == 0)
            {
                if (symptom_s2 >= b3[0] && symptom_s2 <= b3[1])
                {
                    res2.push_back("Student2#" + to_string(symptom_s2) + "#B3");
                    break;
                }
            }
            else if (strncmp(stu1[i].c_str(), "C1", 2) == 0)
            {
                if (symptom_s2 >= c1[0] && symptom_s2 <= c1[1])
                {
                    res3.push_back("Student2#" + to_string(symptom_s2) + "#C1");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "C2", 2) == 0)
            {
                if (symptom_s2 >= c2[0] && symptom_s2 <= c2[1])
                {
                    res3.push_back("Student2#" + to_string(symptom_s2) + "#C2");
                    break;
                }
            }
            else if (strncmp(stu2[i].c_str(), "C3", 2) == 0)
            {
                if (symptom_s2 >= c3[0] && symptom_s2 <= c3[1])
                {
                    res3.push_back("Student2#" + to_string(symptom_s2) + "#C3");
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(stu3[i].c_str(), "A1", 2) == 0)
            {
                if (symptom_s3 >= a1[0] && symptom_s3 <= a1[1])
                {
                    res1.push_back("Student3#" + to_string(symptom_s3) + "#A1");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "A2", 2) == 0)
            {
                if (symptom_s3 >= a2[0] && symptom_s3 <= a2[1])
                {
                    res1.push_back("Student3#" + to_string(symptom_s3) + "#A2");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "A3", 2) == 0)
            {
                if (symptom_s3 >= a3[0] && symptom_s3 <= a3[1])
                {
                    res1.push_back("Student3#" + to_string(symptom_s3) + "#A3");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "B1", 2) == 0)
            {
                if (symptom_s3 >= b1[0] && symptom_s3 <= b1[1])
                {
                    res2.push_back("Student3#" + to_string(symptom_s3) + "#B1");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "B2", 2) == 0)
            {
                if (symptom_s3 >= b2[0] && symptom_s3 <= b2[1])
                {
                    res2.push_back("Student3#" + to_string(symptom_s3) + "#B2");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "B3", 2) == 0)
            {
                if (symptom_s3 >= b3[0] && symptom_s3 <= b3[1])
                {
                    res2.push_back("Student3#" + to_string(symptom_s3) + "#B3");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "C1", 2) == 0)
            {
                if (symptom_s3 >= c1[0] && symptom_s3 <= c1[1])
                {
                    res3.push_back("Student3#" + to_string(symptom_s3) + "#C1");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "C2", 2) == 0)
            {
                if (symptom_s3 >= c2[0] && symptom_s3 <= c2[1])
                {
                    res3.push_back("Student3#" + to_string(symptom_s3) + "#C2");
                    break;
                }
            }
            else if (strncmp(stu3[i].c_str(), "C3", 2) == 0)
            {
                if (symptom_s3 >= c3[0] && symptom_s3 <= c3[1])
                {
                    res3.push_back("Student3#" + to_string(symptom_s3) + "#C3");
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(stu4[i].c_str(), "A1", 2) == 0)
            {
                if (symptom_s4 >= a1[0] && symptom_s4 <= a1[1])
                {
                    res1.push_back("Student4#" + to_string(symptom_s4) + "#A1");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "A2", 2) == 0)
            {
                if (symptom_s4 >= a2[0] && symptom_s4 <= a2[1])
                {
                    res1.push_back("Student4#" + to_string(symptom_s4) + "#A2");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "A3", 2) == 0)
            {
                if (symptom_s4 >= a3[0] && symptom_s4 <= a3[1])
                {
                    res1.push_back("Student4#" + to_string(symptom_s4) + "#A3");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "B1", 2) == 0)
            {
                if (symptom_s4 >= b1[0] && symptom_s4 <= b1[1])
                {
                    res2.push_back("Student4#" + to_string(symptom_s4) + "#B1");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "B2", 2) == 0)
            {
                if (symptom_s4 >= b2[0] && symptom_s4 <= b2[1])
                {
                    res2.push_back("Student4#" + to_string(symptom_s4) + "#B2");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "B3", 2) == 0)
            {
                if (symptom_s4 >= b3[0] && symptom_s4 <= b3[1])
                {
                    res2.push_back("Student4#" + to_string(symptom_s4) + "#B3");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "C1", 2) == 0)
            {
                if (symptom_s4 >= c1[0] && symptom_s4 <= c1[1])
                {
                    res3.push_back("Student4#" + to_string(symptom_s4) + "#C1");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "C2", 2) == 0)
            {
                if (symptom_s4 >= c2[0] && symptom_s4 <= c2[1])
                {
                    res3.push_back("Student4#" + to_string(symptom_s4) + "#C2");
                    break;
                }
            }
            else if (strncmp(stu4[i].c_str(), "C3", 2) == 0)
            {
                if (symptom_s4 >= c3[0] && symptom_s4 <= c3[1])
                {
                    res3.push_back("Student4#" + to_string(symptom_s4) + "#C3");
                    break;
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (strncmp(stu5[i].c_str(), "A1", 2) == 0)
            {
                if (symptom_s5 >= a1[0] && symptom_s5 <= a1[1])
                {
                    res1.push_back("Student5#" + to_string(symptom_s5) + "#A1");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "A2", 2) == 0)
            {
                if (symptom_s5 >= a2[0] && symptom_s5 <= a2[1])
                {
                    res1.push_back("Student5#" + to_string(symptom_s5) + "#A2");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "A3", 2) == 0)
            {
                if (symptom_s5 >= a3[0] && symptom_s5 <= a3[1])
                {
                    res1.push_back("Student5#" + to_string(symptom_s5) + "#A3");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "B1", 2) == 0)
            {
                if (symptom_s5 >= b1[0] && symptom_s5 <= b1[1])
                {
                    res2.push_back("Student5#" + to_string(symptom_s5) + "#B1");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "B2", 2) == 0)
            {
                if (symptom_s5 >= b2[0] && symptom_s5 <= b2[1])
                {
                    res2.push_back("Student5#" + to_string(symptom_s5) + "#B2");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "B3", 2) == 0)
            {
                if (symptom_s5 >= b3[0] && symptom_s5 <= b3[1])
                {
                    res2.push_back("Student5#" + to_string(symptom_s5) + "#B3");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "C1", 2) == 0)
            {
                if (symptom_s5 >= c1[0] && symptom_s5 <= c1[1])
                {
                    res3.push_back("Student5#" + to_string(symptom_s5) + "#C1");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "C2", 2) == 0)
            {
                if (symptom_s5 >= c2[0] && symptom_s5 <= c2[1])
                {
                    res3.push_back("Student5#" + to_string(symptom_s5) + "#C2");
                    break;
                }
            }
            else if (strncmp(stu5[i].c_str(), "C3", 2) == 0)
            {
                if (symptom_s5 >= c3[0] && symptom_s5 <= c3[1])
                {
                    res3.push_back("Student5#" + to_string(symptom_s5) + "#C3");
                    break;
                }
            }
        }

        int sock_hos1;
        struct sockaddr_in hos1_addr;
        if ((sock_hos1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&hos1_addr, 0, sizeof(hos1_addr));
        hos1_addr.sin_family = AF_INET;
        hos1_addr.sin_port = htons(PORT_H1);
        hos1_addr.sin_addr.s_addr = INADDR_ANY;
        socklen_t len_hos1 = sizeof(hos1_addr);
        for (int i = 0; i < res1.size(); i++)
        {
            sendto(sock_hos1, res1[i].c_str(), strlen(res1[i].c_str()), 0, (const struct sockaddr *)&hos1_addr, sizeof(hos1_addr));
            printf("The health center has send one admitted student to <Hospital1>\n");
        }

        if (getsockname(sock_hos1, (struct sockaddr *)&hos1_addr, &len_hos1) == -1)
        {
            perror("getsockname");
        }
        char udp1_ip[1024];
        inet_ntop(AF_INET, &(hos1_addr.sin_addr), udp1_ip, INET_ADDRSTRLEN);
        printf("The health center has UDP port %d and IP address %s for Phase 2 - Hospital1\n", ntohs(hos1_addr.sin_port), udp1_ip);
        close(sock_hos1);

        int sock_hos2;
        struct sockaddr_in hos2_addr;
        if ((sock_hos2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&hos2_addr, 0, sizeof(hos2_addr));
        hos2_addr.sin_family = AF_INET;
        hos2_addr.sin_port = htons(PORT_H2);
        hos2_addr.sin_addr.s_addr = INADDR_ANY;
        socklen_t len_hos2 = sizeof(hos1_addr);
        for (int i = 0; i < res2.size(); i++)
        {
            sendto(sock_hos2, res2[i].c_str(), strlen(res2[i].c_str()), 0, (const struct sockaddr *)&hos2_addr, sizeof(hos2_addr));
            printf("The health center has send one admitted student to <Hospital2>\n");
        }

        if (getsockname(sock_hos2, (struct sockaddr *)&hos2_addr, &len_hos2) == -1)
        {
            perror("getsockname");
        }
        char udp2_ip[1024];
        inet_ntop(AF_INET, &(hos1_addr.sin_addr), udp2_ip, INET_ADDRSTRLEN);
        printf("The health center has UDP port %d and IP address %s for Phase 2 - Hospital2\n", ntohs(hos2_addr.sin_port), udp2_ip);
        close(sock_hos2);

        int sock_hos3;
        struct sockaddr_in hos3_addr;
        if ((sock_hos3 = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&hos3_addr, 0, sizeof(hos3_addr));
        hos3_addr.sin_family = AF_INET;
        hos3_addr.sin_port = htons(PORT_H3);
        hos3_addr.sin_addr.s_addr = INADDR_ANY;
        socklen_t len_hos3 = sizeof(hos3_addr);

        for (int i = 0; i < res3.size(); i++)
        {
            sendto(sock_hos3, res3[i].c_str(), strlen(res3[i].c_str()), 0, (const struct sockaddr *)&hos3_addr, sizeof(hos3_addr));
            printf("The health center has send one admitted student to <Hospital3>\n");

        }

        if (getsockname(sock_hos3, (struct sockaddr *)&hos3_addr, &len_hos3) == -1)
        {
            perror("getsockname");
        }
        char udp3_ip[1024];
        inet_ntop(AF_INET, &(hos3_addr.sin_addr), udp3_ip, INET_ADDRSTRLEN);
        printf("The health center has UDP port %d and IP address %s for Phase 2 - Hospital3\n", ntohs(hos3_addr.sin_port), udp3_ip);
        close(sock_hos3);
    }
    return 0;
}
