# NTFS DRIVER with cmd application on JAVA

## Compile Java App

```
javac -h . Main.java
```

## Launch Java App

```
sudo java -Djava.library.path=cmake-build-debug Main %launch_mode% %args%
```

##Launch Modes
* list
* shell %path_to_fs%

### List mode

Show available block devices

Example:

```
Drive loop1
Drive nvme0n1
	- partition nvme0n1p1
	- partition nvme0n1p2
Drive loop8
Drive loop6
Drive loop4
Drive loop2
Drive loop0
Drive loop7
Drive loop5
Drive loop3
```

### Shell mode

1. cd [directory] - change working directory
2. pwd - print working directory full name
3. cp - [directory] [target directory] - copy dir or file from mounted device
4. ls - show working directory elements
5. exit - terminate program
6. help - print help