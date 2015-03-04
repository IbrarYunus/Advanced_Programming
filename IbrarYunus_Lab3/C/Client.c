#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void)
{
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[512];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;


    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n !Cannot Create Socket \n");
        exit(0);
    }


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n !Cannot Connect \n");
        exit(0);
    }

 
    FILE *fp;
    fp = fopen("recieved.png", "ab"); 
    if(NULL == fp)
    {
        printf("!Cannot Open file");
        exit(0);
    }


    while((bytesReceived = read(sockfd, recvBuff, 512)) > 0)
    {
        //printf("Bytes received %d\n",bytesReceived);    

        fwrite(recvBuff, 1,bytesReceived,fp);

    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }

    printf("File Recieved!");


    return 0;
}