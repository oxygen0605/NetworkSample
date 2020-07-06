#include"mynetlib_server.h"

struct server* new_server(int id){
	
    struct server *s = (struct server *)malloc(sizeof(struct server));
	  memset(s, 0, sizeof(struct server));
	
	  s->id = id;
	  return s;
}

int initialize_server(struct server *s){
    
    /* ソケットの作成 */
    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (s->sock < 0){
        perror("socket "); //errornoの内容を出力してくれる
        return 1;
    }
    
    /* ソケットの設定 */
    s->sock_info.sin_family = AF_INET;
    s->sock_info.sin_port = htons(12345);
    s->sock_info.sin_addr.s_addr = INADDR_ANY;
    
    int bind_retval = bind(s->sock, (struct sockaddr *)&(s->sock_info), sizeof(s->sock_info));
    if(bind_retval != 0){
        perror("bind ");
        return 1;
    }

    return 0;
}

int start_server_forever(struct server *s){
    
    int yes=1;
    
    /* TCPクライアントからの接続要求を持てる状態にする */
    if(listen(s->sock, 5) != 0){
        perror("listen ");
        return 1;       
    }
    
    setsockopt(s->sock,
        SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));
    
    int len, n;
    while(1){  
      /* TCPクライアントからの接続要求を受け付ける */
      len = sizeof(s->sock_client_info);
      s->sock_client = accept(s->sock, (struct sockaddr *)&(s->sock_client_info), &len);
    
      printf("accepted connection from %s, port=%d\n",
            inet_ntoa(s->sock_client_info.sin_addr), ntohs(s->sock_client_info.sin_port));
    
      if(send(s->sock_client, "HELLO", 5, 0) < 1){
          perror("send ");
          break;
      }	
    }
  return 0;
}

void delete_server(struct server **s){
    
    /* TCPセッションのclose */
    close((*s)->sock_client);
    /* listenするsocketのclose */
    close((*s)->sock);
    free(*s);
    *s = NULL;
}