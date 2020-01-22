# 使い方

## `keymap.c` にコピペする

編集するのは適用したい `keymap.c` のみです

### `custom_keycodes` の追加

`keymap.c` でキーマップが定義されている部分の前に以下のように `custom_keycodes` を定義してください

```cpp
enum custom_keycodes {
  JU_2 = BMP_SAFE_RANGE,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS
};
```

すでに `custom_keycodes` が定義されている場合は、以下のように追加してください

```cpp
enum custom_keycodes {
  CUSTOM_KEY_CODE_A = BMP_SAFE_RANGE,
  CUSTOM_KEY_CODE_B,
  CUSTOM_KEY_CODE_C, // <- コンマを忘れない
  // 以下追加
  JU_2,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS
};
```

### `custom_keys_user` の編集

`custom_keycodes` や `custom_keys_user` が定義されていなかった場合、 `custom_keycodes` の下に以下を追加してください

```cpp
const key_string_map_t custom_keys_user = {
  .start_kc = JTU_START_KC,
  .end_kc = JTU_END_KC,
  .key_strings = JTU_KEY_STRINGS
};
```

すでに `custom_keys_user` が定義されていた場合、以下のように変更してください

```cpp
// このように custom_keycodes が定義されていたとする
enum custom_keycodes {
  CUSTOM_KEY_CODE_A = BMP_SAFE_RANGE,
  CUSTOM_KEY_CODE_B,
  CUSTOM_KEY_CODE_C,
  JU_2,
  JU_6,
  JU_7,
  JU_8,
  JU_9,
  JU_0,
  JU_MINS,
  JU_EQL,
  JU_LBRC,
  JU_RBRC,
  JU_BSLS,
  JU_SCLN,
  JU_QUOT,
  JU_GRV,
  JU_CAPS
};

// 以下のように custom_keys_user を定義
const key_string_map_t custom_keys_user = {
  .start_kc = CUSTOM_KEY_CODE_A,
  .end_kc = JTU_END_KC,
  .key_strings = "CUSTOM_KEY_CODE_A\0CUSTOM_KEY_CODE_B\0CUSTOM_KEY_CODE_C\0" JTU_KEY_STRINGS
};
```

### `process_record_user(...)` の編集

[`jtu_custom_keycodes.c`](jtu_custom_keycodes.c) に実装されている `process_record_user_jtu(...)` 内から、使いたいキーコードの `case` 文をコピペしてください

また、以下の宣言を関数の先頭に忘れず追加してください

```cpp
  static bool lshift = false;
  static bool rshift = false;
```

例

```cpp
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false; // 追加
  static bool rshift = false; // 追加

  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false) {
    return false;
  }

  switch (keycode) {
    case CUSTOM_KEY_CODE_A:
      // 処理
      return false;
    case CUSTOM_KEY_CODE_B:
      .
      .
      .
      return false;
    // 以下追加
    case JU_2:
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
        if (lshift || rshift) {
          if (lshift) unregister_code(KC_LSFT);
          if (rshift) unregister_code(KC_RSFT);
          register_code(KC_LBRC);
          unregister_code(KC_LBRC);
          if (lshift) register_code(KC_LSFT);
          if (rshift) register_code(KC_RSFT);
        } else {
          register_code(KC_2);
          unregister_code(KC_2);
        }
      }
      return false;
    case JU_6:
      if (record->event.pressed) {
    .
    .
    .
  }
  return true;
}
```

以上で使うことができます

## ライブラリとして使う

編集するのは以下のファイルです

* `rules.mk`
* `keymap.c`

### ファイル配置

全ファイルを適用したいキーマップディレクトリにコピーしてください

すでに `rules.mk` がある場合は `rules.mk` は不要です

### `rules.mk` の編集

**今回新たに `rules.mk` を作成した場合は、この手順を飛ばしてください**

もともとあった `rules.mk` の先頭にこのディレクトリの `rules.mk` の中身をコピペしてください

もともとあった `rules.mk` に `SRC += ...` のような文があった場合は、最後に `jtu_custom_keycodes.c` を追加します

```mk
...

SRC += something_a.c \
    something_b.c \        # <- バックスラッシュを忘れない
    jtu_custom_keycodes.c  # 追加

...
```

### `keymap.c` の編集

#### ヘッダーファイルの include

ファイルの `#include` の最後に以下を追加します

```cpp
#include "jtu_custom_keycodes.h"
```

#### `custom_keycodes` の編集

**`keymap.c` 内に `custom_keycodes` の定義がない場合は、この手順を飛ばしてください**

`BMP_SAFE_RANGE` を `JTU_SAFE_RANGE` に変更します

```cpp
...

enum custom_keycodes {
  CUSTOM_KEY_CODE_A = JTU_SAFE_RANGE, // 変更
  CUSTOM_KEY_CODE_B,
  CUSTOM_KEY_CODE_C
};

...
```

#### `custom_keys_user` の編集

`custom_keycodes` や `custom_keys_user` が定義されていなかった場合、 `custom_keycodes` の下に以下を追加してください

```cpp
const key_string_map_t custom_keys_user = {
  .start_kc = JTU_START_KC,
  .end_kc = JTU_END_KC,
  .key_strings = JTU_KEY_STRINGS
};
```

すでに `custom_keys_user` が定義されていた場合、以下のように変更してください

```cpp
// このように custom_keycodes が定義されていたとする
enum custom_keycodes {
  CUSTOM_KEY_CODE_A = JTU_SAFE_RANGE,
  CUSTOM_KEY_CODE_B,
  CUSTOM_KEY_CODE_C
};

// 以下のように custom_keys_user を定義
const key_string_map_t custom_keys_user = {
  .start_kc = JTU_START_KC,
  .end_kc = CUSTOM_KEY_CODE_C,
  .key_strings = JTU_KEY_STRINGS "CUSTOM_KEY_CODE_A\0CUSTOM_KEY_CODE_B\0CUSTOM_KEY_CODE_C\0"
};
```

#### `process_record_user(...)` の編集

`process_record_user(...)` の先頭に以下のように `process_record_user_jtu(...)` を追加してください

```cpp
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool continue_process = process_record_user_bmp(keycode, record);
  if (continue_process == false) {
    return false;
  }

  // 以下追加
  continue_process = process_record_user_jtu(keycode, record);
  if (continue_process == false) {
    return false;
  }
  // 追加ここまで

...
```

以上で使うことができます

なお、以前に何度かビルドしており、今回 `rules.mk` を編集して、新たにビルドすると失敗することがあります

その時は `qmk_firmware_bmp/.build/` 以下のファイルを削除してから `make` コマンドを実行してください

また、ファームウェアを書き込んだあと、`KEYMAP.JSN` にキーコード文字列が反映されていない場合がありますので、一応確認してください
キーコード文字列自体は内部の辞書に登録されているので、問題なく認識されるはずです
