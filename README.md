# Parallels Utils

A collection of utils for using with [Parallels Desktop 9](http://www.parallels.com/products/desktop/). 

![Parallels Logo](imgs/parallels_small.png)

### Building

* Requires [Parallels Virtualization SDK 9 for Mac](http://www.parallels.com/downloads/desktop/), download and install it.

* Build

```
make
```
All binaries are built into ```bin/```. Add it to you path.

## Usage

#### prltype

A simple tools to send keyboard events to a Virtual Machine.
```prltype <vm_name> <scan codese...>```

Example:
```prltype MyVm 1e 146 30 158``` will send ```ab``` to the virtual machine _MyVm_.

For a complete set of keyboard scan codes see:
[Keyboard scancodes](http://www.win.tue.nl/~aeb/linux/kbd/scancodes-10.html#ss10.6) column _**Set 1**_

Every key is sent with two codes, first the _pressed_ and then the _release_ code. The _release_ code is the same as _pressed_ (listed in the table) plus ```0x128```. 

### Install with Homebrew

TODO

## License

This code is distributed under the MIT license, see LICENSE.

© 2014 Rickard von Essen

---

Parallels Desktop is a registered trademark of Parallels Software International, Inc. The Parallels logo is a trademark of Parallels Holdings, Ltd.