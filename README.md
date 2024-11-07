# 📍RP2040評価F/W by ちみ
📍RP2040評価F/W 個人開発リポジトリ🥳

- 📍CPU ... [RP2040🔗](https://www.raspberrypi.com/products/rp2040/)
  - 📍CPU0 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)
  - 📍CPU1 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)

- 📍OS ... [FreeRTOS🔗](https://www.freertos.org/)
  - 📍CPU0 ... ✅FreeRTOS (搭載済み)
  - 📍CPU1 ... ✅FreeRTOS (搭載済み)

## 📍開発環境
- [開発環境の詳細🔗](/doc/rp2040_dev_env.md)

- 📍IDE
  - 📍[Arduino IDE v2.33🔗](https://github.com/arduino/arduino-ide/releases/tag/2.3.3)
    - [Raspberry Pi Pico/RP2040/RP2350 by Earle F. Philhower, III🔗](https://github.com/earlephilhower/arduino-pico)

- 📍基板
  - 📍RP2040
    - [VCC-GND YD-RP2040🔗](https://www.aliexpress.us/item/1005004004120604.html?gatewayAdapt=4itemAdapt)

## 📍実装機能
**凡例(✅実装＆テスト完了、🆗実装済み、🚩TODO、❌TBD)**

- 📍CPU (ARM Cortex-M0+)(clk_sys = 133MHz)
  - 📍Core0 ... ドライバCPU
    - 📍OS ... FreeRTOS
      - ✅Core0メインタスク
        - ✅状態遷移、LED処理
      - ✅ボタンタスク
        - 🚩ボタン処理
          - 🚩ボタン単押し ... TODO
          - 🚩ボタン複数押し判定 ... TODO
          - 🚩ボタン長押し判定 ... TODO
          - 🚩ボタン超長押し判定 ... TODO
  - 📍Core1 ... アプリCPU
    - 📍OS ... FreeRTOS
      - ✅Core1メインタスク
        - 🚩TODO
      - ✅モニタプログラムタスク
        - ✅レジスタ
          - M0PLUS CPUIDレジスタ、SIOレジスタのRead
        - ✅計算
          - マンデルブロ集合、円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根

- 📍RGB LED (@GPIO 35)
  - ✅赤🔴 : 初期化中、オフライン状態(WiFi,Bluetooth未接続)
  - ✅青🔵 : オンライン状態（WiFi,Bluetooth接続中）
  - ✅緑🟢 : F/W正常（FreeRTOSで処理中）
  - ✅白⚪ : F/W正常（FreeRTOSはアイドル状態）
  - ✅紫🟣 : F/Wエラー

- 📍割込み(IRQ)）
  - ✅タイマーIRQ⏰
    - ✅アラーム 0 ⏰(TIMER_IRQ_0) ... 1ms周期 (🚩実行時間計測用)
    - ✅アラーム 1 ⏰(TIMER_IRQ_1) ... 20ms周期 (🚩メインタスク起床)
    - ✅アラーム 2 ⏰(TIMER_IRQ_2) ... 100ms周期 (🚩ボタンタスク起床)
    - ✅アラーム 3 ⏰(TIMER_IRQ_3) ... 1000ms周期 (🚩TBD)
  - ✅ボタンIRQ (@GPIO24)
    - ✅ボタン単押し判定 ... ボタン一回押しを検知
    - ✅ボタン複数押し判定 ... 短時間に複数回ボタン押しを検知
    - ✅ボタン長押し判定 ... ボタン長押しを検知（1000ms = 1s）
    - ✅ボタン超長押し判定 ... ボタン長押しを検知（3000ms = 3s)