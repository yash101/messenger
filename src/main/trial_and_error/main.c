#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <threads.h>


#if defined(_WIN32) || defined(WIN32)
#include <dos.h>
#else
#include <unistd.h>
#endif

#define PORT 6969
#define BUFLEN 1024 * 1024 * 16

void server()
{
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  char* buffer = malloc(BUFLEN);
  memset(buffer, 0, BUFLEN);

  struct sockaddr_in srv_addr;
  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(PORT);
  srv_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
  {
    printf("Bind failed");
    exit(-1);
  }

  printf("Listening...\n");

  while(1)
  {
    struct sockaddr_in cli_addr;
    unsigned int len = sizeof(cli_addr);

    int recvd = recvfrom(
      fd,
      (char*) buffer,
      BUFLEN,
      MSG_WAITALL,
      (struct sockaddr*) &cli_addr,
      &len
    );

    char addr[64] = { 0 };
    strncpy(addr, (const char*) inet_ntoa(cli_addr.sin_addr), 63);
    
    printf("Packet from %s:%d\n", addr, ntohs(cli_addr.sin_port));

    int sent = sendto(fd, (void*) buffer, strlen(buffer) + 1, 0x0, (struct sockaddr*) &cli_addr, sizeof(cli_addr));
  }

  free(buffer);
}

void client()
{
  int num = 0;
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  unsigned int len;
  char* buffer = calloc(sizeof(char), BUFLEN);
  char* buffer2 = calloc(sizeof(char), BUFLEN);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  inet_aton("127.0.0.1", &addr.sin_addr);


  for (int i = 0; i < 3; i++)
  {
    printf("Sending data...%d\n", num);
    sprintf(buffer, "Hello world %d\n", num++);
    int sent = sendto(fd, (void*) buffer, strlen(buffer) + 1, 0x0, (struct sockaddr*) &addr, (socklen_t) sizeof(addr));
    len = sizeof(addr);
    int recv = recvfrom(fd, (void*) buffer2, BUFLEN, MSG_CONFIRM, (struct sockaddr*) &addr, &len);
  }

  free(buffer);
  free(buffer2);
}

void* serverThread(void* arg)
{
  server();
  return NULL;
}

int main(int argc, char** argv)
{
  thrd_t server_thrd;
  int rc;

  rc = thrd_create(&server_thrd, (thrd_start_t) serverThread, NULL);
  sleep(1);

  for (int i = 0; i < 5; i++)
  {
    client();
  }

  thrd_join(server_thrd, NULL);

  return 0;
}