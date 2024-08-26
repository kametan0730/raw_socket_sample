# raw_socket_sample
セキュリティ・ミニキャンプ2024 沖縄の課題用プログラム

## 共通
- プログラムファイル内のインターフェース名(Linuxでは`eth0`など, Windowsでは`イーサネット 1`など)を環境に合わせて変更して下さい

## Python
### Windows
#### インストール
- Python3, Scapy, Npcapのインストールが必要です
    - Python:
        - WindowsのStoreアプリまたは以下のサイトのインストーラーからインストールしてください
        - https://www.python.org/downloads/
    - Scapy: 
	    - Pythonに付属するパッケージ管理コマンドのpipでインストールできます
	    - `pip install scapy`
    - Npcap:
        - Windowsでは、標準でアプリケーションからイーサネットレイヤで通信を扱う機能がないため、 Npcapはカーネルモードドライバによってそれを可能にします
        - Scapyが内部でNpcapを使用しているため、インストールしてください
        - WiresharkのインストールウィザードでNpcapをインストールできます
            - https://www.wireshark.org/download.html

#### 実行(VSCode)
- VSCodeでmain_win.pyファイルを作成
- Python拡張機能をVSCodeに追加する
- プログラムのコード(https://github.com/kametan0730/raw_socket_sample/blob/master/python/main_win.py )を貼り付け
- ▶ボタン(`Run Python File`)をクリックして実行する


#### 実行(CUIの場合)
```
git clone https://github.com/kametan0730/raw_socket_sample
cd raw_socket_sample/python3
python3 main_win.py
```

### Linux
#### インストール
- Python3, Scapyのインストールが必要です
    - Python3をインストール後`pip install scapy`


#### 実行
- 実行にはroot権限若しくはCAP_NET_RAWケーパビリティが必要です
```
git clone https://github.com/kametan0730/raw_socket_sample
cd raw_socket_sample/python
sudo python3 main.py
```


## C++
### Linux
#### インストール
- 何かしらのcppコンパイラなど
- Ubuntuなら`sudo apt install build-essential`でOK

#### 実行

- 実行にはroot権限若しくはCAP_NET_RAWケーパビリティが必要です
```
git clone https://github.com/kametan0730/raw_socket_sample
cd raw_socket_sample/cpp
sudo make run
```
