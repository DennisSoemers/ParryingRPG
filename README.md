# Parrying RPG
[![C++23](https://img.shields.io/static/v1?label=standard&message=C%2B%2B23&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat)](#)
![GitHub](https://img.shields.io/github/license/DennisSoemers/ParryingRPG)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/DennisSoemers/ParryingRPG)

A reimplementation of fenix31415's [fenix31415's Parrying mod](https://www.nexusmods.com/skyrimspecialedition/mods/65133) for Skyrim, 
with some additional features. 

## Download

The plugin can be downloaded from [its NexusMods page](https://www.nexusmods.com/skyrimspecialedition/mods/81356).

## Runtime Requirements (for users)

At runtime, the plugin has the following requirements. Any user of this plugin (or mods that in turn require this plugin) need to have this installed locally.

- The Elder Scrolls V: Skyrim Special Edition.
  - Tested with version 1.5.97 (SSE).
  - Assumed compatible with version 1.6.353 (reported by users for [fenix31415's mod](https://www.nexusmods.com/skyrimspecialedition/mods/65133), 
  which uses the same hooks that I do.
  - Not compatible with other versions.
- [Skyrim Script Extender](https://skse.silverlock.org/)
- [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Build Requirements (for plugin developers)

Building the code in this repository has the following requirements.

- [Visual Studio](https://visualstudio.microsoft.com/).
- [CMake](https://cmake.org/).
- [Vcpkg](https://github.com/microsoft/vcpkg).

This project was set up exactly as in the [CommonLibSSE NG Sample Plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin), 
and I refer to that repository for highly detailed instructions on installation and building.

## Credits

Thanks to:
- [fenix31415](https://github.com/fenix31415) for the original implementation of the [Parrying -- Weapons Bounce on Impact](https://www.nexusmods.com/skyrimspecialedition/mods/65133) mod.
- [max-su-2019](https://github.com/max-su-2019/) and [doodlum](https://github.com/doodlum/) for source code from 
[MaxsuWeaponSwingParry-ng](https://github.com/doodlum/MaxsuWeaponSwingParry-ng).
- [powerof3](https://github.com/powerof3/) for code I used as example for reading/writing .ini files.
- CharmedBaryon for [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) and the [CommonLibSSE NG Sample Plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin).
- The SKSE authors for [SKSE](http://skse.silverlock.org/).
- Meh321 for [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444).

## Disclaimer

- THIS MATERIAL IS NOT MADE, GUARANTEED OR SUPPORTED BY ZENIMAX OR ITS AFFILIATES.
- ALL FILES IN THE DOWNLOAD ARE PROVIDED ''AS IS'' WITHOUT ANY WARRANTY OR GUARANTEE OF ANY KIND. IN NO EVENT CAN THE AUTHOR BE HELD RESPONSIBLE FOR ANY CLAIMS, WHETHER OR NOT THEY ARE RELATED TO THE DOWNLOAD.
