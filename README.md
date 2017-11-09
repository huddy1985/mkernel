mkeykernel
=======

This is a kernel that can read the characters a-z and 0-9 from the keyboard and print them on screen.

See the repo [mkernel](http://github.com/arjun024/mkernel) which is a minimal kernel that prints a string on the screen. mkeykernel just extends this to include keyboard support. 


####Blog post####

Kernel 201 - Let’s write a Kernel with keyboard and screen support

(http://arjunsreedharan.org/post/99370248137/kernel-201-lets-write-a-kernel-with-keyboard-and)

####Build commands####
* The kernel is Multiboot compliant and loads with GRUB.


#### Blog post ####

Kernel 101 – Let’s write a Kernel

(http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel)

#### Build commands ####
```
nasm -f elf32 kernel.asm -o kasm.o
```
```
gcc -m32 -c kernel.c -o kc.o
```
```
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
```

If you get the following error message:
```
kc.o: In function `idt_init':
kernel.c:(.text+0x129): undefined reference to `__stack_chk_fail'
```

compile with the `-fno-stack-protector` option:
```
gcc -fno-stack-protector -m32 -c kernel.c -o bin/kc.o
```

#### Test on emulator ####
```
qemu-system-i386 -kernel kernel
```

#### Get to boot ####
GRUB requires your kernel executable to be of the pattern `kernel-<version>`.

So, rename the kernel:

```
mv kernel kernel-701
```

Copy, it to your boot partition (assuming you are superuser):

```
cp kernel-701 /boot/kernel-701
```

Configure your grub/grub2 similar to what is given in `_grub_grub2_config` folder.

Reboot.

Voila !!

![kernel screenshot](http://static.tumblr.com/gltvynn/yOdn443dr/mkernel.png "Screenshot")

#### The next step ####
see [mkeykernel repo](//github.com/arjun024/mkeykernel)
