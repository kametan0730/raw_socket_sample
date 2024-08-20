# raw_socket_sample

### 共通
- プログラムファイル内のインターフェース名(eth0)を環境に合わせて変更して下さい

### Python
#### Windows
- Python3とライブラリScapyのインストールが必要です
    - https://www.python.org/downloads/
    - https://scapy.net/
- WindowsにWinPcapをインストールする必要があります
    - Wiresharkのインストールウィザードの途中でWinPcapをインストール可能です
    - https://www.wireshark.org/download.html


```
cd python3
sudo python3 main_win.py
```


#### Linux
- 実行にはroot権限若しくはCAP_NET_RAWケーパビリティが必要です
```
cd python
sudo python3 main.py
```


### C++
#### Linux
- 実行にはroot権限若しくはCAP_NET_RAWケーパビリティが必要です
```
cd cpp
sudo make run
```