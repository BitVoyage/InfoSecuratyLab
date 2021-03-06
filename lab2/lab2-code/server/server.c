#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "http.h"

#define HOST_PORT 8899
#define DEBUG 1
#define BUF_SIZE 1024

#define DIE(msg)						\
  do{								\
    fprintf (stderr, "Error: %s:%d: %s\n",			\
	     __FILE__, __LINE__, msg);				\
    exit (0);							\
  }while(0)							\

int main (int argc, char **argv)
{
  int sockfd, client_sockfd;
  int host_port;
  int yes;
  char buffer[BUF_SIZE];
  struct sockaddr_in host_addr, client_addr;

  host_port = HOST_PORT;
  if (argc>1)
    host_port = atoi(argv[1]);

  if ((sockfd = socket (PF_INET, SOCK_STREAM, 0))==-1){
    DIE("creating a socket");
  }

  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    DIE("setting socket option SO_REUSEADDR");

  memset(&(host_addr), '\0', sizeof(host_addr)); // zero off the structure
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(host_port);
  host_addr.sin_addr.s_addr = 0;

  if (bind(sockfd, (struct sockaddr *)&host_addr
	   , sizeof(struct sockaddr)) == -1)
    DIE("binding to socket");

  if (listen(sockfd, 1000) == -1)
    DIE("listening on socket");

  signal(SIGCHLD, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);

  int pid;
  int fds[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds))
       DIE("socketpair");

  if ((pid=fork())==0){
    close (fds[1]);
    char pipe_fd_str[32] = {'\0'};
    char *child_name = "./httpd";
    sprintf (pipe_fd_str, "%d", fds[0]);
    char *child_argv[] = {child_name
			  , pipe_fd_str
			  , 0};
    if (DEBUG)
      printf ("%s\n", pipe_fd_str);

    if (execv (child_name, child_argv)==-1)
      DIE("execve");
  }

  close (fds[0]);
  while (1){
    int size;
    if ((client_sockfd = accept
	 (sockfd, (struct sockaddr *)&client_addr, &size))==-1)
      DIE("accepting client connection");

  printf("1\n");
    printf("Parent process client_sockfd = %d\n",client_sockfd);

    if (DEBUG)
      printf ("server: accepting a client from %s port %d\n"
	      , inet_ntoa (client_addr.sin_addr)
	      , ntohs (client_addr.sin_port));

    char sock_fd_str[32] = {'\0'};
    sprintf (sock_fd_str, "%d", client_sockfd);
    if (DEBUG){
      printf ("sending a socket to the client:\n");
    }
     sendfd(fds[1],sock_fd_str, strlen(sock_fd_str)+1,client_sockfd);

     close(client_sockfd);
  }
  return 0;
}

