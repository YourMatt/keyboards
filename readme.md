# QMK Setup

1. Install python3.7 or above
2. `python3 -m pip install --user qmk`
3. `qmk setup`
4. Accept default location in user folder
5. `cd ~/qmk_firmware`
6. `ln -s /mnt/l/Git/YourMatt/keyboards/build/ .build.personal.repo`
7. `cd keyboards`
8. `ln -s /mnt/l/Git/YourMatt/keyboards/ yourmatt`
9. Adjust paths.mk with `BUILD_DIR := .build.personal.repo`test