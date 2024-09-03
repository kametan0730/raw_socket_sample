from scapy.all import *
import threading
import time

# イーサネットフレームの送信関数
def send_frame(frame, iface):
    while True:
        sendp(frame, iface=iface, verbose=False)  # Scapyのsendp関数を使用
        print(f"frame sent: {frame.summary()}")
        time.sleep(1)

# イーサネットフレームの受信関数
def receive_frame(iface):
    def packet_handler(packet):
        # Ethernetレイヤーが存在するか確認
        if packet.haslayer(Ether):
            eth = packet.getlayer(Ether)
            # 送信元MACアドレスがターゲットMACアドレスと一致するか確認
            if eth.src != '00:0c:29:12:34:56':
                print(f"Captured packet : {packet.summary()}")

    sniff(iface=iface, prn=packet_handler, store=False)  # Scapyのsniff関数を使用

# メイン関数
def main():
    interface = 'イーサネット 1'  # 使用するインターフェース名を指定

    # 送信するイーサネットフレームを構築
    dest_mac = 'ff:ff:ff:ff:ff:ff'  # ブロードキャストMACアドレス
    src_mac = '00:0c:29:12:34:56'  # 自分のMACアドレス
    eth_type = 0x0800  # IPプロトコル
    payload = b'Hello, Ethernet!'
    frame = Ether(dst=dest_mac, src=src_mac, type=eth_type) / payload

    # スレッドを作成して送受信を並列に実行
    send_thread = threading.Thread(target=send_frame, args=(frame, interface))
    recv_thread = threading.Thread(target=receive_frame, args=(interface,))

    send_thread.start()
    recv_thread.start()

    send_thread.join()
    recv_thread.join()

if __name__ == "__main__":
    main()
