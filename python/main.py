import socket
import time
import threading

ETH_P_ALL = 3

# イーサネットフレームの送信関数
def send_frame(sock, frame):
    while True:
        sock.send(frame)
        print(f"frame sent: {frame.hex()}")
        time.sleep(1)

# イーサネットフレームの受信関数
def receive_frame(sock):
    while True:
        frame = sock.recv(65535)
        print(f"frame received: {frame[0:32].hex()}")

# メイン関数
def main():
    interface = 'eth0'  # 使用するインターフェース名を指定

    sock = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(ETH_P_ALL)) # Raw Socketを作成
    sock.bind((interface, 0)) # インターフェースをBindする

    # 送信するイーサネットフレームを構築
    dest_mac = b'\xff\xff\xff\xff\xff\xff' # ブロードキャストMACアドレス
    src_mac = b'\x00\x0c\x29\x12\x34\x56' # 自分のMACアドレス
    eth_type = b'\x00\x00' # 適当なタイプ
    payload = b'Hello, Ethernet!'
    frame = dest_mac + src_mac + eth_type + payload

    # スレッドを作成して送受信を並列に実行
    send_thread = threading.Thread(target=send_frame, args=(sock, frame))
    recv_thread = threading.Thread(target=receive_frame, args=(sock,))

    send_thread.start()
    recv_thread.start()

    send_thread.join()
    recv_thread.join()

if __name__ == "__main__":
    main()
