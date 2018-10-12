# nXORE

## Version 1.0.0
nXORE - is a simple CUI based encryptor program that uses XOR cipher encryption method.

## Prerequisites
What you need to compile this program is `Boost` and `nCurse` library.

## Compiles
Follow these steps to compile the program.
```
1. Go to inside the nXORE folder
2. mkdir bin
3. cd bin
4. cmake ..
5. make
6. ./nXORE
```
Or you could also use cmake-gui.

## Usage
1. Open the program, it's better to run it with sudo command `sudo ./nXORE`.
2. After that, you need to login. The default password is `root`, you may change it later in the setting.
3. Set key first before to encrypt in the **SELECT KEY** option.
4. Select the file in **SELECT FILES** option. Press right key to select and spacebar if you done.
5. Finally, choose **ENCRYPT/DECRYPT** option to encrypt or decrypt it depending the files.

## Known Limitations
* For now, it only could select multiple files in the **same folder**.
* The encrypted/decrypted result will be placed same as the original files path.
* Using simple setting storage.

## Known Bugs

## Change Log
See [CHANGELOG.md](CHANGELOG.md) for more.

## Built With
* [Code::Blocks](http://www.codeblocks.org/) - My favorite C/C++ IDE
* [nCurse](https://www.gnu.org/software/ncurses/) - For the console graphic
* [Boost](https://www.boost.org/) - For file management

## Contributors
Ivan Ongko Sampurna(Cathean) - ivanshadow19@gmail.com

## License & Copyright
See [LICENSE.md](LICENSE.md) for more.
