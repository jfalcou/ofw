# OFW - One File Wonders

[![OFW CI](https://github.com/jfalcou/ofw/actions/workflows/main.yml/badge.svg?branch=main)](https://github.com/jfalcou/ofw/actions/workflows/main.yml)
[![Licence](https://img.shields.io/github/license/jfalcou/ofw?style=plastic)](https://img.shields.io/github/license/jfalcou/ofw?style=plastic)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.com/channels/692734675726237696/828012535361830942)

## WTF is OFW

**OFW** is a loose collection of One File C++20 library solving various problems in, we hope, an interesting way by using modern C++ 20.

## Contents
Currently, the libraries' roaster is made of:

* [**Raberu**](https://github.com/jfalcou/ofw/wiki/RABERU) - A Python-like keyword library
* [**Kumi**](https://github.com/jfalcou/ofw/wiki/KUMI) - A flexible tuple implementation

## Installation and Usage
Installing a library from **OFW** is rather straightforward.

  1. Download the one header file for the library. For example, you can download
     [**kumi**](kumi.md.html) this way:
     ```
     wget https://raw.githubusercontent.com/jfalcou/ofw/main/include/kumi.hpp
     ```

  2. Copy it in the location of your choice.

Using the library then boils down to including its include files and compile your applications using C++20.

You can also use CMake FetchContent operation and use the `ofw::ofw` library target that our CMake exports.

## License
This library is licensed under the MIT License as specified in the LICENSE.md file.
If you use any One File Wonders in your project or product, feel free to send us
an email so we can advertise it here.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The MIT License (MIT)

Copyright (c) 2020-2021 Joel FALCOU

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
