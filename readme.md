# Environment Setup

1. Pull latest from QMK repo into local folder at (assuming /mnt/l/Git/Public/qmk_firmware)
2. Create symlink to this repo's local folder (assuming /mnt/l/Git/YourMatt/keyboards)

```
ln -s /mnt/l/Git/YourMatt/keyboards /mnt/l/Git/Public/qmk_firmware/keyboards/yourmatt
```


# Build Firmware

```
cd /mnt/l/Git/Public/qmk_firmware
qmk compile -kb yourmatt/foldername -km yourmatt
```


# Flash Firmware

1. Open QMK Toolbox
2. Select firmware (eg L:\Git\Public\qmk_firmware\.build\yourmatt_cajal_yourmatt.hex)
3. Load keyboard into bootloader mode
4. Flash


# Resources

https://docs.qmk.fm/
https://jayliu50.github.io/qmk-cheatsheet/
https://github.com/samhocevar/wincompose/releases


# Cajal Underglow Adjustment
This was to dim the LEDs below the arrow keys. They are closer to the edge of the case than the other LEDs, so they
appear brigher than all the other. I had adjusted QMK with an option that would result in these being dimmed to match
the intensity of the other. It no longer works after a QMK update, but it may still be workable. I decided to not use
the underglow anymore, so it wasn't worth the effort to re-evaluate.

## keymap.c
Add before including QMK_KEYBOARD_H:
`#define RGBLIGHT_CAJAL`

## quantum\rgblight\rgblight.c

Before:
```
                // same static color
#ifdef RGBLIGHT_LAYERS_RETAIN_VAL
                // needed for rgblight_layers_write() to get the new val, since it reads rgblight_config.val
                rgblight_config.val = val;
#endif
                rgb_t rgb = hsv_to_rgb((hsv_t){hue, sat, val > RGBLIGHT_LIMIT_VAL ? RGBLIGHT_LIMIT_VAL : val});
                rgblight_setrgb(rgb.r, rgb.g, rgb.b);
```

After:
```
            #ifdef RGBLIGHT_CAJAL
                uint8_t val_adj = val;
                for (int i = 0; i < rgblight_ranges.effect_num_leds; i++) {
                    LED_TYPE *ledp = led + i;
                    if (i == 1 || i == 2) val_adj = val * 0.5;
                    else val_adj = val;
                    sethsv(hue, sat, val_adj, ledp);
                }
                rgblight_set();
            #else
                // same static color
#ifdef RGBLIGHT_LAYERS_RETAIN_VAL
                // needed for rgblight_layers_write() to get the new val, since it reads rgblight_config.val
                rgblight_config.val = val;
#endif
                rgb_t rgb = hsv_to_rgb((hsv_t){hue, sat, val > RGBLIGHT_LIMIT_VAL ? RGBLIGHT_LIMIT_VAL : val});
                rgblight_setrgb(rgb.r, rgb.g, rgb.b);
            #endif
```


# Obsolete Old QMK Setup Notes

1. Install python3.7 or above
2. `python3 -m pip install --user qmk`
3. `qmk setup`
4. Accept default location in user folder
5. `cd ~/qmk_firmware`
6. `ln -s /mnt/l/Git/YourMatt/keyboards/build/ .build.personal.repo`
7. `cd keyboards`
8. `ln -s /mnt/l/Git/YourMatt/keyboards/ yourmatt`
9. Adjust paths.mk with `BUILD_DIR := .build.personal.repo`test