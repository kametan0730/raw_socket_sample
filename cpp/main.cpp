#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <linux/if_packet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

void send_frame(const int sock, const uint8_t *frame, size_t frame_len) {

  while(true){
    if (send(sock, frame, frame_len, 0) < 0) {
      perror("failed to send frame");
    } else {
      std::cout << "frame sent: ";
      for (size_t i = 0; i < frame_len; ++i) {
        printf("%02x", frame[i]);
      }
      std::cout << std::endl;
    }
    sleep(1);
  }
}

void receive_frame(const int sock) {

  uint8_t buffer[9000];
  while (true) {
    ssize_t frame_len = recv(sock, buffer, sizeof(buffer), 0);
    if (frame_len < 0) {
      perror("failed to receive frame");
    } else {
      std::cout << "frame received: ";
      for (ssize_t i = 0; i < (frame_len > 32 ? 32 : frame_len); ++i) {
        printf("%02x", buffer[i]);
      }
      std::cout << "..." << std::endl;
    }
  }
}

int main() {
  std::string interface = "eth0"; // 使用するインターフェース名を指定

  int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); // Raw Socketを作成
  if (sock < 0) {
    perror("failed to create socket");
    return 1;
  }

  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name, interface.c_str(), IFNAMSIZ - 1);

  if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0) { // インターフェースのIndexを取得
    perror("failed to get interface index");
    close(sock);
    return 1;
  }

  struct sockaddr_ll saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sll_family = AF_PACKET;
  saddr.sll_protocol = htons(ETH_P_ALL);
  saddr.sll_ifindex = ifr.ifr_ifindex;

  if (bind(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) { // インターフェースをBind
    perror("failed to bind socket");
    close(sock);
    return 1;
  }

  // 送信するイーサネットフレームを作成
  uint8_t dest_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // ブロードキャストアドレス
  uint8_t src_mac[6] = {0x00, 0x0c, 0x29, 0x12, 0x34, 0x56}; // 自分のMACアドレス
  uint8_t eth_type[2] = {0x00, 0x00}; // 適当なタイプ
  uint8_t payload[] = "Hello, Ethernet!";
  uint8_t frame[sizeof(dest_mac) + sizeof(src_mac) + sizeof(eth_type) + sizeof(payload)];

  memcpy(frame, dest_mac, sizeof(dest_mac));
  memcpy(frame + sizeof(dest_mac), src_mac, sizeof(src_mac));
  memcpy(frame + sizeof(dest_mac) + sizeof(src_mac), eth_type, sizeof(eth_type));
  memcpy(frame + sizeof(dest_mac) + sizeof(src_mac) + sizeof(eth_type), payload, sizeof(payload));

  // スレッドを作成して送受信を並列に実行
  std::thread send_thread(send_frame, sock, frame, sizeof(frame));
  std::thread recv_thread(receive_frame, sock);

  send_thread.join();
  recv_thread.join();

  return 0;
}