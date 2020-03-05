# raspimouse

Raspberry Pi Mouse V2 のサンプルプログラムのリポジトリです。

製品ページはこちらです。

[Raspberry Pi Mouse V2 人工知能やロボットの学習に最適なプラットフォームロボット](https://www.rt-net.jp/products/raspimouse2)

デバイスドライバはこちらです。

[Raspberry Pi Mouse Device Driver](https://github.com/rt-net/RaspberryPiMouse)

本リポジトリでは、デバイスドライバを使用せずに、デバイスドライバと同様の機能をプログラム内で使用するサンプルプログラムとなっております。そのため、デバイスドライバをインストールする必要はありません。

このリポジトリでは、デバイスドライバをc++で書くことを目標としています。

## 動作環境について
このプログラムは、以下の環境で開発及びテストを行っております。

Raspberry Pi
- Raspberry Pi Mouse Model3B+
  
OS
- RasberryPi OS (Raspbian Stretch)
- Ubuntu 18.04LTS 32bit
- Ubuntu 18.04LTS 64bit

使用記録媒体
- Transcend microSDHC 16GB

## 使用方法
1. プログラムのコンパイルの環境の構築を行います。
 
c/c++のコンパイラやmake等は以下のコマンドで一括でインストールすることが可能です。
```
$ sudo apt install build-essential
```

1. gitを使用して本リポジトリをクローンします。
```
$ cd ~
$ mkdir workspace && cd workspace
$ git clone https://github.com/YutaSeya/raspimouse
```
2行目のディレクトリの作成は各自の判断で行っていただければと思います。

3. このリポジトリのビルドを行います。

```
$ cd raspimouse
$ make all
```

4. プログラムの実行を行います。

このリポジトリのプログラムの実行を行う際に、デバイスのメモリの参照を行います。
そのため、実行時にスーパーユーザーの権限が必要になります。
```
sudo make run
```

このプログラムを実行すると、UI用のLED0~4が2進数の数字の順にインクリメントされながら光り、全てのLEDが光ったら消灯して終了します。

## リポジトリの概要
このリポジトリのディレクトリ構成は以下のようになっています。
- Inc
  - 各種ヘッダファイル
- Src
  - 各種ソースファイル 
- makefile
- .gitignore
- README.md
- LICENSE

現在、ソフトウェアを随時更新しているためIncやSrc直下のディレクトリ構造等は随時変化する可能性があります。ご了承ください。

## ライセンスについて
このリポジトリはGPLv3ライセンスで公開されています。詳細は[LICENSE](https://github.com/YutaSeya/raspimouse/blob/master/LICENSE)を確認してください。

## その他
このプログラムにより生じた問題等に責任は一切負いません。