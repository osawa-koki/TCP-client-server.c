#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
  // ソケットを作成
  int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // サーバのアドレス情報を設定
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345); // ポート番号
  serverAddr.sin_addr.s_addr = INADDR_ANY; // サーバのIPアドレス

  // サーバに接続
  connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

  while (true) {
    // 送信するメッセージを受け取る
    std::string message;
    std::getline(std::cin, message);

    // サーバにメッセージを送信
    send(clientSocket, message.c_str(), message.size(), 0);

    // サーバからのメッセージを受信
    char buffer[1024];
    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);

    // 受信したメッセージを表示
    std::cout << "Received: " << buffer << std::endl;
  }

  // ソケットを閉じる
  close(clientSocket);

  return 0;
}
