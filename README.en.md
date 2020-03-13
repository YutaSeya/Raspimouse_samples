# Raspimouse_samples

[English](README.en.md) | [日本語](README.md)

Raspberry Pi Mouse V2 sample program

Product pages:

https://www.rt-net.jp/products/raspimouse2

device driver page:

[Raspberry Pi Mouse Device Driver](https://github.com/rt-net/RaspberryPiMouse)

In this repository, We don't use device driver and use Raspberry Pi Mouse V2's peripheral function. So, We don't need to install device driver.

This repository aims to write device driver in c++.

## System Requirements
This program have been developed and tested on the following environment.

Raspberry Pi
- Raspberry Pi Mouse Model3B+
  
OS
- RasberryPi OS (Raspbian Stretch)
- Ubuntu 18.04LTS 32bit
- Ubuntu 18.04LTS 64bit

recording media
- Transcend microSDHC 16GB

## How to use
1. Set up a compilation environment.
 
For exsamples, gcc, g++ or make, we can install with the following commnad.

```
$ sudo apt install build-essential
```

2. Get this repository with a git.
   
```
$ cd ~
$ mkdir workspace && cd workspace
$ git clone https://github.com/YutaSeya/raspimouse
```
The Second line, we create the workspece directory if you need it.

3. Build this program.
The following commamd.
```
$ cd raspimouse
$ make all
```

4. Execute this program.

When we run a this repository program, this program reference /dev/mem.
Therefore, you need to empower super user. The following command.

```
sudo make run
```

You execute this program. LEDs 0 to 4 for UI light in binary order.When All LEDs light, ALL LEDs turn off and end this program.

## About raspimouse repository
This repository structure is as follows.
- Inc
  - various header files
- Src
  - various source files
- makefile
- .gitignore
- README.md
- LICENSE
- Doc
  - make Doxygen HTML file etc

Now, I update this repository. So this repository sturcture may change from time to time. I hope you will understand this.

Document is [this pages](./doc/html/index.html).

## About LICENSE

This repository is licensed under the GPLv3 License. if you want to know this LiCENSE, to see[LICENSE](https://github.com/YutaSeya/raspimouse/blob/master/LICENSE) pages.

## Other
Assume no responsibility.
