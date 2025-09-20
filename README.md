# Citrus

64 битное Unix подобное ядро написанное с нуля на языке С, GAS, NASM.
--------------------------------------------------------------------

## Инсталяция ядра
*Примечание: установка на системах не имеющих отношения к unix может оказаться затруднительным процессом и наврядли плодоносным* 

1. Скачайте исходный код с этого репозитория
2. Создайте отдельную директорию для проекта пример: osproject/citrus-kernel/**citrus** < основной файл ядра
   
4. Установка кросс компилятора **x86_64-elf-gcc**
    к примеру:
    ```sh
    brew install x86_64-elf-gcc
    sudo apt install x86_64-elf-gcc
    sudo dnf install x86_64-elf-gcc
    ```
    или используйте метод сборки из исходников

5. Установка эмулятора qemu
	```sh
	sudo pacman -S qemu-full
	sudo apt install qemu-full
	sudo dnf insatll qemu-full
	```
6. Установка xorriso
	```sh
	sudo pacman -S xorriso
	sudo apt install xorriso
	sudo dnf insatll xorriso
	```
	
### Запуск ядра

для запуска ядра воспользуйтесь следующей командой

```sh
make clean && make && make run
```

 Если все прошло успешно вы увидите окно qemu в котором будет виден grub а далее текстовый интерфейс ядра
