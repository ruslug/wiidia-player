# Wiidia Player

A media player for the Nintendo Wii.

## Prerequisites

- [devkitPro](https://devkitpro.org/) with devkitPPC installed
- `DEVKITPPC` environment variable set to your devkitPPC installation path
- Required libraries:

  ```sh
  dkp-pacman -S wii-dev ppc-sdl2 ppc-sdl2_ttf ppc-sdl2_mixer
  ```

## Building

```sh
make
```

This produces `wiidia-player.dol`, which can be loaded on a Wii or in an emulator like [Dolphin](https://dolphin-emu.org/).

To clean build artifacts:

```sh
make clean
```

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
