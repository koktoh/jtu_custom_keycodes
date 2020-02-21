# jtu_custom_keycodes
JISキーボードで物理的にUS配列を実現するための [QMK Firmware][qmk] 用カスタムキーコード

# 定義されているキーコード

|キー|説明|
|:-:|:--|
|`JU_2`|`2` / Shift で `@`|
|`JU_6`|`6` / Shift で `^`|
|`JU_7`|`7` / Shift で `&`|
|`JU_8`|`8` / Shift で `*`|
|`JU_9`|`9` / Shift で `(`|
|`JU_0`|`0` / Shift で `)`|
|`JU_MINS`|`-` / Shift で `_`|
|`JU_EQL`|`=` / Shift で `+`|
|`JU_LBRC`|`[` / Shift で `{`|
|`JU_RBRC`|`]` / Shift で `}`|
|`JU_BSLS`|`\` / Shift で <code>&#124;</code>|
|`JU_SCLN`|`;` / Shift で `:`|
|`JU_QUOT`|`'` / Shift で `"`|
|`JU_GRV`|`` ` `` / Shift で `~`|
|`JU_CAPS`|英数の大文字/小文字切り替え|

# `default` と `ble_micro_pro` について

普通の [QMK Firmware][qmk] で使う場合は `default` 以下のファイルを使用してください

[BLE Micro Pro 標準ファームウェア][bmp]で使う場合は `ble_micro_pro` 以下のファイルを使用してください

# 使い方

使い方は主に2つあります

1. `keymap.c` にコピペする
1. ライブラリとして使う

どちらでも好きなほうで使用してください

詳しくはそれぞれの README を読んでください

**なお、私は Windows しか環境を持っていないため、それ以外の OS では未検証です**

[qmk]: https://github.com/qmk/qmk_firmware
[bmp]: https://github.com/sekigon-gonnoc/BLE-Micro-Pro/tree/master/AboutDefaultFirmware
