hrp5p-calib インストール／動作確認手順

[1] 動作環境
以下の環境で動作確認済み

    ubuntu-14.04(64bit), ubuntu-16.04(64bit)


[2] 必要なパッケージのインストール
事前に必要なパッケージをインストールしておく.

    $ sudo apt-get install build-essential cmake cmake-curses-gui \
      libboost-all-dev Xaw3dg-dev libraw1394-dev libusb-1.0-0-dev


[3] gcc-4.9のインストール(ubuntu-14.04のみ)
ubuntu-14.04のデフォルトのコンパイラはgcc-4.8であるが，C++14のサポートが不完全な
ため，本コードをコンパイルできない．そこで，以下の手順でgcc-4.9をインストールする．

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


[4] hrp5p-calibのダウンロード
GitHubからダウンロードする．

    $ git clone https://github.com/t-ueshiba/hrp5p-calib.git


[5] hrp5p-calibのコンパイルとインストール
次の手順でコンパイル，インストールする．

    $ cd hrp5p-calib
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ sudo make install

次のものがインストールされる：

    /usr/local/bin/flowIIDCcamera	# カメラからの画像ストリームを標準出力へ
    /usr/local/bin/fv			# 標準入力からの画像ストリームを表示
    /usr/local/lib/libTUTools++.*	# 様々なツール
    /usr/local/lib/libTUIIDC++.*	# カメラドライバ
    /usr/local/lib/libTUv++.*		# GUIツールキット
    /usr/local/lib/libTUvIIDC++.*	# カメラ制御用GUIのwidget
    /usr/local/include/TU/*.h
    /usr/local/include/TU/simd/*.h
    /usr/local/include/TU/simd/x86/*.h
    /usr/local/include/TU/simd/arm/*.h
    /usr/local/include/TU/v/*.h


[6] 共有ライブラリの検索パスの設定
~/.bashrc の中に

    export LD_LIBRARY_PATH=/usr/local/lib:${LD_LIBRARY_PATH}

を追加して，/usr/local/lib中の共有ライブラリを検索するようにする．


[7] 一般ユーザにカメラへのアクセス権を与える
デフォルトでは一般ユーザにはFireWire/USBデバイスを直接操作する権限がないので，
これを許可するために /etc/udev/rules.d/40-permissions.rules という
ファイルを作る．

    $ sudo vi /etc/udev/rules.d/40-permissions.rules

そして，以下の内容を記入する．

    ### Begin ###
    SUBSYSTEM=="firewire",				GROUP="video"
    SUBSYSTEM=="usb device",				GROUP="video"
    SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device",	GROUP="video"
    ### End ###

これにより，グループ：video に属するユーザにアクセス権が与えられる．
そして，実際にカメラを使用するユーザを video グループに登録する．
（ubuntuの場合，videoグループ自体は既存なので，新たに作る必要はない）

    $ sudo vi /etc/group

    ### 例：hrpuser を video に登録 ###
    video:x:44:hrpuser
    ###


[8] reboot
[7]の設定を有効化するためにホストマシンをリブートする．

    $ sudo reboot

再ログインして，自分がvideoグループに属していることを確かめる

    $ id

と打って，groups= に44(video) が表示されればOK.


[9] カメラの動作確認
/usr/local/bin に実行パスが通っていることを確認した上で

    $ flowIIDCcamera 0 | fv

と打つ．fvのウィンドウが現れてカメラからの画像が表示されれば
成功である．

    $ flowIIDCcamera 0 0 | fv

と打てば2台のカメラからの画像が同時に表示される．
本来は，左カメラと右カメラの固有IDが分かっていれば

    $ flowIIDCcamera <left camera id> <right camera id> | fv

と打つことにより，第1のカメラを左，第2のカメラを右にそれぞれ設定できる．
しかし，最初に起動する時はIDが不明なので，0を与えることによって，順序は
不明ながら，とにかく見つかった順に2つのカメラをオープンする．


[10] カメラパラメータの制御
次のように flowIIDCcamera に -G オプションを付けて起動すると，
カメラ制御用のGUIが現れて様々なパラメータを変えることができる．

    $ flowIIDCcamera -G 0 0 | fv

なお，-G を付けた場合は，flowIIDCcamera はカメラからの画像出力を
停止した状態で起動する．よって，GUIの"Continuous shot"ボタンを
押して画像出力を開始しないと，fvに画像が表示されない．


[11] 異なるホストに接続されたカメラからの画像の表示
カメラを接続しているホスト(remoteとする)と画像を表示するホスト
(localとする)が異なる時は，

    local$ ssh remote flowIIDCcamera 0 | fv

とすれば良い．もちろん，localからremoteへsshで接続でき，
なおかつ接続先で/usr/local/binに実行パスが，/usr/local/libに
共有ライブラリ検索パスがそれぞれ通っていることが前提である．

    