#include<stdio.h>
#include"mynetlib_client.h"

int main(int argc, char *argv[]){

	/* server address */
    char *deststr = "127.0.0.1";
   
    /* clientインスタンス作成 */
    struct client *client = new_client(0x000000FF);
     
    /* サーバに接続 */
    if(connect_server(client, deststr)){
  	  exit(1); // 接続失敗
    };
    
    /* client情報出力 */
    print_client_info(client);
    
    /* サーバからデータを受信 */
    char buf[32];
    memset(buf, 0, sizeof(buf));
    int n = read(client->sock, buf, sizeof(buf));
    if (n < 0) {
  	  perror("read ");
  	  return 1;
    }
  
    printf("%d, %ld, %ld, %s\n", n, sizeof(buf), sizeof(deststr), buf);
  
    /* clientインスタンス削除。*/
    delete_client(&client);
  
    return 0;
}
