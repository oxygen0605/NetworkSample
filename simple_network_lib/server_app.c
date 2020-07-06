#include<stdio.h>
#include"mynetlib_server.h"

int main(){
    
    struct server *server = new_server(0x00000001);

    if(initialize_server(server)){
      exit(1); //socket作成エラー
    }; 

    /* Server listen 開始*/
    if(start_server_forever(server)){
      exit(1); //listenエラー
    };

    /* ここまで到達しない */
    delete_server(&server);
    
    return 0;
}

