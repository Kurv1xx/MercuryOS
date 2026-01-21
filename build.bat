@echo off

:: Setup directories
if not exist build mkdir build
if not exist boot\EFI\BOOT mkdir boot\EFI\BOOT

:: Compiling
echo INFO: [1/3] Compiling...
clang -target x86_64-unknown-elf -ffreestanding -fno-builtin -mno-red-zone -c kernel/kernel.c -o build/kernel.o
clang -target x86_64-pc-windows -ffreestanding -fno-builtin -fno-stack-protector -fno-stack-clash-protection -mno-red-zone -c kernel/boot.c -o build/boot.o

:: Linking
echo INFO: [2/3] Linking...
ld.lld -T kernel/linker.ld -o boot/kernel.elf build/kernel.o
lld-link /subsystem:efi_application /entry:efi_main /nodefaultlib build/boot.o /out:boot/EFI/BOOT/BOOTX64.EFI

:: Booting MercuryOS in QEMU
echo INFO: Build complete!
echo INFO: [3/3] Booting virtual machine...
qemu-system-x86_64 ^
  -machine q35 ^
  -m 512M ^
  -drive if=pflash,format=raw,readonly=on,file="C:\Packages\MSYS2\ucrt64\share\qemu\edk2-x86_64-code.fd" ^
  -drive if=pflash,format=raw,file="C:\Packages\MSYS2\ucrt64\share\qemu\vars.fd" ^
  -drive file=fat:rw:boot,format=raw ^
  -serial stdio

:: Cleanup
rmdir /s /q build
rmdir /s /q boot
