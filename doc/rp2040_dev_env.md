# 開発環境構築(Windows)
## Arduino IED
- `基本設定`から👇下記URLを追加
- `ボードマネージャ`から`Raspberry Pi Pico/RP2040 by Earle F Philhower, III`をダウンロード or 更新

```shell
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```

#s# VSCode
### `Raspberry Pi Pico`をインストール
- VSCodeの拡張機能で`Raspberry Pi Pico`をインストール

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/3fb53d261f08-20241015.png">
</div>

### プロジェクトを作成
- `Name` ... プロジェクト名を入力する
- `Board type` ... `pico`を選択する
- `location` ... プロジェクトの保存先を選択する
- `Select Pico SDK version` ... `Pico SDKの最新バージョン`を選択する
- `Features` ... 使用する機能を選択する
- `Stdio support` ... C/C++の`printf()`の出力先を`USB`か`UART`から決める
- `Code generation options` ... `Generate C++ code`でPico SDKのコードを生成する
- `Debbugger` ... `DebugProbe(CMSIS-DAP)[Default]`を選択する

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/93e5a68afb64-20241015.png">
</div>

### ビルド＆デバッグ

- `ビルド` ... `Compile Project`でコンパイルを実行
- F/Wを書き込む ... `Run Project`でPicoにF/Wを書き込む
- `デバッグ` ... `Debug Project`でデバッグ開始（※）

※Picoでデバッグをするには`デバッガ`が必要🥲
- 下記の`デバッガの準備`を参考にご準備ください

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/7b86d616bf51-20241015.png">
</div>


### デバッガの準備

Picoでデバッグするためには`デバッガ`がつくる💁‍♀️
- Picoをもう一つ用意 ... `debugprobe`のF/Wを書き込む

まず、デバッガ`debugprobe`の最新F/W(`debugprobe_on_pico.uf2`)をダウンロード
- https://github.com/raspberrypi/debugprobe/releases/latest

[F/Wの書き込む]
- Picoの **`BOOTSEL`ボタンを押しながら** USBをPCに接続する
- `debugprobe_on_pico.uf2`をPicoにドロップ＆ドラック

[他のPicoとの接続]
```
Pico(A) GND -> Pico(B) GND
Pico(A) GP2 -> Pico(B) SWCLK
Pico(A) GP3 -> Pico(B) SWDIO
Pico(A) GP4/UART1 TX -> Pico(B) GP1/UART0 RX
Pico(A) GP5/UART1 RX -> Pico(B) GP0/UART0 TX
```

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/4e1aedab768d-20241015.png">
</div>

## 開発環境構築(Linux)
PICO SDKはLinux環境が必須
- UbuntuやWindowsのWSL2で構築する方法を記載する

### pico_setup.sh
`pico_setup.sh`でPICO SDKの構築を自動化

[Github]
https://github.com/raspberrypi/pico-setup/tree/master

```shell
wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh
chmod +x ./pico_setup.sh
./pico_setup.sh
```

# 参考文献
- [Pico SDK 公式URL](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)
- [公式マニュアル（英語）※最新](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*anhnfe*_ga*MTE3MTIyMDMzMS4xNzI4OTQ5MzU2*_ga_22FD70LWDS*MTcyODk2NTE2OC42LjAuMTcyODk2NTE3MS4wLjAuMA..)
- [公式マニュアル（日本語）※更新が2021年で止まっている](https://datasheets.raspberrypi.com/pico/getting-started-with-pico-JP.pdf)

- Zenn『Pico SDKの開発環境構築の最適解 📝』 by ちみ
  - https://zenn.dev/chimipupu/articles/039597a904849f