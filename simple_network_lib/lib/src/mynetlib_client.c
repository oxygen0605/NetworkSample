#include "mynetlib_client.h"

struct client* new_client(int id){
	
	struct client *c = (struct client *)malloc(sizeof(struct client));
	memset(c, 0, sizeof(struct client));
	
	c->id = id;
	return c;
}

int connect_server(struct client *c, char* deststr){

	/* サーバアドレスの格納 */
	c->ipv4_deststr = deststr;

    /* ソケットの作成 */
    c->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sock < 0) {
  	 perror("socket");
  	 return 1;
    }
    
    /* 接続先指定用構造体の準備 */
    c->server.sin_family = AF_INET;
    c->server.sin_port = htons(12345);
  
    /* 名前解決 参考：https://www.geekpage.jp/programming/linux-network */  
    c->server.sin_addr.s_addr = inet_addr(deststr);
   if (c->server.sin_addr.s_addr == 0xffffffff) {
  	 struct hostent *host;
  
  	 host = gethostbyname(deststr);
  	 if (host == NULL) {
  		 if (h_errno == HOST_NOT_FOUND) {
  			 /* h_errnoはexternで宣言されています */
  			 printf("host not found : %s\n", deststr);
  		 } else {
  			/*
  			HOST_NOT_FOUNDだけ特別扱いする必要はないですが、
  			とりあえず例として分けてみました
  			*/
  			printf("%s : %s\n", hstrerror(h_errno), deststr);
  		 }
  		 return 1;
  	 }
  
  	 c->addrptr = (unsigned int **)host->h_addr_list;
  
  	 while (*(c->addrptr) != NULL) {
  		 c->server.sin_addr.s_addr = *(*(c->addrptr));
  
  		 /* connect()が成功したらloopを抜けます */
  		 if (connect(c->sock,
  				(struct sockaddr *)&c->server,
  				sizeof(c->server)) == 0) {
  			break;
  		 }
  
  		 c->addrptr++;
  		 /* connectが失敗したら次のアドレスで試します */
  	 }
  
  	 /* connectが全て失敗した場合 */
  	 if (*(c->addrptr) == NULL) {
  		 perror("connect");
  		 return 1;
  	 }
   } else {
  	 /* inet_addr()が成功したとき */
  	 /* connectが失敗したらエラーを表示して終了 */
  	 if (connect(c->sock,
                       (struct sockaddr *)&c->server, sizeof(c->server)) != 0) {
  		 perror("connect");
  		 return 1;
  	 }
   }

   return 0;
}

/* 
 * 呼び出し元のポインタにNULLを書き込むために
 * 引数型を(struct client **)としている。
 * NULLで上書きする理由は、freeを呼んでも動作環境によっては
 * 引き続きclientポインタが参照できるためバグの引き金になる。
 * それを防ぐためである。
*/
void delete_client(struct client **c){
    /* socketの終了 */
    close((*c)->sock);
	free(*c);
	*c = NULL;
}

void print_client_info(struct client *client){
  printf("client ID: %d,\ndest adderss: %s,\nsocket no: %d\n",
   			client->id, client->ipv4_deststr, client->sock);
}