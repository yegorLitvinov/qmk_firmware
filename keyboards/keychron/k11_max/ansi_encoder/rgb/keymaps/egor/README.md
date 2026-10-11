# Egor's Velvet layout for K11 Max

This macOS keymap follows the six layers in
[Velvet's keymap](../../../../../../../../ergohaven-zmk-config/config/velvet_v3_ruen.keymap).
The stock K11 Mac media, lighting, and wireless layer is the seventh layer.
Its keycodes and encoder actions are unchanged.

## Physical keys

| K11 key | Action |
| --- | --- |
| Top-left Escape | Transparent (no base-layer action) |
| Tab | Tab |
| Caps Lock | Escape |
| Left Control | Hold Numbers/Media |
| Left Option | Left Option |
| Both Command keys | Hold Apps/Nav |
| Left spacebar | Left Command |
| Fn1 | Space |
| Fn2 | Right Control |
| Right spacebar | Hold Symbols for the current language |
| Right duplicate B | Switch EN/RU |
| Home | Hold the stock K11 media layer |
| `[` | Backspace; Shift selects Delete |
| `;` | Apostrophe in EN; ж in RU |
| `'` | Enter |
| Main Enter | Hold Numbers/Media |
| `/` | Slash in EN; э in RU |

The number row, arrow cluster, original Backspace, and other extra
keys keep their normal actions. The encoder controls volume. On the stock K11
media layer, it controls keyboard lighting brightness.

## Layers

VIA displays layers starting at 0.

| VIA layer | Name | Access |
| --- | --- | --- |
| 0 | English | Selected on connection or with EN/RU |
| 1 | Russian | EN/RU |
| 2 | English Symbols | Hold right spacebar in EN |
| 3 | Russian Symbols | Hold right spacebar in RU |
| 4 | Apps/Nav | Hold either physical Command key |
| 5 | Numbers/Media | Hold physical Left Control |
| 6 | K11 Media | Hold Home |

Apps/Nav keeps Velvet's Command+Control+Option app shortcuts, navigation, and
Command+Shift+5 screenshot shortcut. Numbers/Media keeps its number pad and
media controls. Its Y/U/I keys select the K11's three Bluetooth hosts. The K11
has no fourth or fifth Bluetooth host, so those two Velvet bindings and the
Bluetooth-clear binding are left empty. Pairing and 2.4 GHz controls remain on
the stock K11 layer.

Symbols follow Velvet, including `%` on physical Left Command and `'` on
physical Right Command while holding Symbols. In RU, the English-only symbols
select English before their press and restore Russian after their release.
If several English symbol keys overlap, Russian returns after the last release.
The Russian Symbols question-mark key also uses this behavior, so it sends the
same `?` shortcut that works with your English input source.

The base layer includes the changes from your October 12 Launcher export.

## macOS language setup

Keep the direct input-source shortcuts used by Velvet:

- Control+Shift+1 selects English.
- Control+Shift+2 selects Russian.

The firmware sends these direct selectors. Configure both in macOS before
using this keymap. The Russian HID codes follow the same layout as Velvet.
Switching input sources outside the keyboard can make its EN/RU state differ
from macOS. Press EN/RU to select the desired source again.

EN/RU runs once on key press. A language change also leaves the current
Symbols or Apps/Nav layer, as it does on Velvet. The firmware selects English
after USB or wireless connection. It waits 500 ms, or selects English before
the first key if typing starts sooner. The physical Mac/Win switch does not
change the layer map for this macOS-only keymap.

## Combos

Press both keys within 50 ms:

- U+I in Russian: х.
- I+O in Russian: ъ.
- Left spacebar (Command)+Fn1 (Space): Spotlight.
- Both Shift keys: Caps Word. It supports English and Russian letters.

The Russian combos are limited to the Russian base layer. Combos are disabled
on the stock K11 media layer. VIA edits to the base keys used by a combo also
change where that combo can be triggered.

## Build and VIA

From the QMK repository or this keyboard directory:

```sh
qmk compile -kb keychron/k11_max/ansi_encoder/rgb -km egor
```

The build creates `keychron_k11_max_ansi_encoder_rgb_egor.bin` in the QMK
repository root. Use this `.bin` for the K11 Max ANSI RGB model.

For VIA, connect over USB. Enable the Design tab in VIA settings and load
[via.json](via.json) there. It provides names for EN/RU, Backspace/Delete, and
the English symbol keys. Use VIA's Save + Load page to export your edited map.
The keyboard definition is separate from that saved layout.

The first boot with this keymap resets the old VIA keymap and macros because
the layer count and EEPROM offsets changed. Later boots keep VIA edits.
Updating from layout version 1 to 2 replaces only the old Russian question-mark
binding, if it is still there. Other VIA edits are kept by that update.
QMK's existing VIA build-date check can also reset the map after a build made
on a different date. Export VIA edits before future firmware changes.

Home+J+Z held for three seconds replaces the stock Fn+J+Z factory-reset chord.
