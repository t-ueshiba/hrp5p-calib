hrp5p-calib インストール／動作確認手順
===================================

## 動作環境

以下の環境で動作確認済み

    ubuntu-14.04(64bit), ubuntu-16.04(64bit)


## 必要なパッケージのインストール

事前に必要なパッケージをインストールしておく.
```bash
$ sudo apt-get install build-essential cmake cmake-curses-gui \
  libboost-all-dev Xaw3dg-dev libraw1394-dev libusb-1.0-0-dev
```


## gcc-4.9のインストール(ubuntu-14.04のみ)

ubuntu-14.04のデフォルトのコンパイラはgcc-4.8であるが，C++14のサポートが不完全な
ため，本コードをコンパイルできない．そこで，以下の手順でgcc-4.9をインストールする．

```bash
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test

$ sudo apt-get update
$ sudo apt-get install g++-4.9

$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 10
$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 20

$ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 10
$ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 20

$ sudo rm /usr/bin/cpp
$ sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.8 10
$ sudo update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-4.9 20

$ sudo update-alternatives --install /usr/bin/cc cc /usr/bin/gcc 30
$ sudo update-alternatives --set cc /usr/bin/gcc

$ sudo update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++ 30
$ sudo update-alternatives --set c++ /usr/bin/g++
```


## hrp5p-calibのダウンロード

GitHubからダウンロードする．
```bash
$ git clone https://github.com/t-ueshiba/hrp5p-calib.git
```


## hrp5p-calibのコンパイルとインストール

次の手順でコンパイル，インストールする．

```bash
$ cd hrp5p-calib
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```
次のものがインストールされる：

    ~/usr/bin/testIIDCcamera	# IIDCカメラのテストプログラム
    ~/usr/bin/testv4l2camera	# V4L2(Video for Linux v.2)カメラのテストプログラム
    ~/usr/lib/libTUTools++.so	# 様々なツール
    ~/usr/lib/libTUIIDC++.so	# IIDCカメラドライバ
    ~/usr/lib/libTUV4L2++.so	# V4L2(Video for Linux v.2)カメラドライバ
    ~/usr/lib/libTUv++.so	# GUIツールキット
    ~/usr/include/TU/*.h
    ~/usr/include/TU/simd/*.h
    ~/usr/include/TU/simd/x86/*.h
    ~/usr/include/TU/simd/arm/*.h
    ~/usr/include/TU/v/*.h

IIDC規格に従ったFireWireまたはUSB接続のカメラを使用するには，IIDCカメラドライバが
必要である．また，Video for Linux v.2に従ったデバイスドライバで駆動されるUSB接続
のカメラを使用するには，V4L2カメラドライバが必要である．


## 共有ライブラリの検索パスの設定

~/.bashrc の中に

    export LD_LIBRARY_PATH=~/usr/lib:${LD_LIBRARY_PATH}

を追加して，~/usr/lib中の共有ライブラリを検索するようにする．


## 一般ユーザにカメラへのアクセス権を与える

デフォルトでは一般ユーザにはFireWire/USBデバイスを直接操作する権限がないので，
これを許可するために /etc/udev/rules.d/40-permissions.rules という
ファイルを作る．
```bash
$ sudo vi /etc/udev/rules.d/40-permissions.rules
```
そして，以下の内容を記入する．

    ### Begin ###
    SUBSYSTEM=="firewire",				GROUP="video"
    SUBSYSTEM=="usb device",				GROUP="video"
    SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device",	GROUP="video"
    ### End ###

これにより，グループ：video に属するユーザにアクセス権が与えられる．
そして，実際にカメラを使用するユーザを video グループに登録する．
（ubuntuの場合，videoグループ自体は既存なので，新たに作る必要はない）
```bash
$ sudo vi /etc/group
```
    ### 例：hrpuser を video に登録 ###
    video:x:44:hrpuser
    ###


## reboot

前項の設定を有効化するためにホストマシンをリブートする．
```bash
$ sudo reboot
```
再ログインして，自分がvideoグループに属していることを確かめる
```bash
$ id
```
と打って，groups= に44(video) が表示されればOK.


## カメラの動作確認

~/usr/bin に実行パスが通っていることを確認した上で
```bash
$ testIIDCcamera
```
と打つ．
    