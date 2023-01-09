#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

  std::cout << "🐸🐸🐸 Starting server..." << std::endl;

  // ソケットを作成
  int listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // ソケットアドレス構造体を作成し、サーバのアドレス情報を設定
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(12345); // ポート番号
  serverAddr.sin_addr.s_addr = INADDR_ANY; // すべてのローカルIPアドレスを使用

  // ソケットにアドレスをバインド
  bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

  // クライアントからの接続要求を待機
  listen(listenSocket, 5);

  std::cout << "🐬🐬🐬 Waiting for client..." << std::endl;

  while (true) {
    // クライアントからの接続要求を受け入れる
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    std::cout << "🐙🐙🐙 Client connected..." << std::endl;

    // クライアントからのメッセージを受信
    char buffer[1024];
    int recvSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    // 受信したデータの末尾にNULL文字を追加
    buffer[recvSize] = '\0';

    // 受信したメッセージを表示
    std::cout << "Received: " << buffer << std::endl;

    std::cout << "🐳🐳🐳 Sending message to client..." << std::endl;

    // クライアントにメッセージを送信
    std::string message = "Hello, client!";
    send(clientSocket, message.c_str(), message.size(), 0);

    // ソケットを閉じる
    close(clientSocket);
  }

  // リスニングソケットを閉じる
  close(listenSocket);

  return 0;
}
