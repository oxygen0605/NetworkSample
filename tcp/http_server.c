#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
  int sock0, sock;
  int len, n;
  int yes=1;
  struct sockaddr_in addr;
  struct sockaddr_in client;

  char buf[2048];
  char inbuf[2048];  

  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  if (sock0 < 0){
    perror("socket "); //errornoの内容を出力してくれる
    return 1;
  }
  
  /* ソケットの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  
  /* TIME_WAIT状態回避 */
  setsockopt(sock0,
    SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

  int bind_retval = bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  if(bind_retval != 0){
    perror("bind ");
    return 1;
  }
  
  /* TCPクライアントからの接続要求を持てる状態にする */
  if(listen(sock0, 5) != 0){
    perror("listen ");
    return 1;       
  }
  
  /* HTTP response message */
  memset(buf, 0, sizeof(buf));
  snprintf(buf, sizeof(buf),
    "HTTP/1.0 200 OK\r\n"
    "Content-Length: 6\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "HELLO\r\n");

  while(1){  
    /* TCPクライアントからの接続要求を受け付ける */
    len = sizeof(client);
    sock = accept(sock0, (struct sockaddr *)&client, &len);
    if (sock < 0) {
	   perror("accept");
	   break;
    }
    printf("accepted connection from %s, port=%d\n",
          inet_ntoa(client.sin_addr), ntohs(client.sin_port));
  
    if(send(sock, buf, (int)strlen(buf), 0) < 1){
      perror("send ");
      break;
    }
    /* TCPセッションのclose */
    close(sock);
  }
  
  /* listenするsocketのclose */
  close(sock0);

  return 0;
}

