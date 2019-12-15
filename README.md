# 42_ft_ssl_md5: Cryptographic Hashing Algorithms 

### Pupose of the project is to recode md5(1) and openSSL (sha2) hashing algorithms that provide communications security over computer network by taking an input message to produce digital fingerprint.

#### Project file: [ft_ssl_md5](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/ft_ssl_md5.en.pdf)

Allowed C System Calls: open(2), close(2), read(2), write(2)

Allowed C functions: malloc(3), free(3)

Additional allowed C functions: strerror(3), exit(3).

---
# Table of Contents - Click a section to jump to it
* [Cloning Repository](#cloning-repository)
* [Installing ft_ssl macOS only](#installing-ft_ssl-macos-only)
* [ft_ssl Usage](#ft_ssl-usage)
* [Program Installation gif Demo](#program-installation-gif-demo)
* [Program Usage gif Demo](#program-usage-gif-demo)
* [Project Summary](#project-summary)
   * [What is hashing and why to use it](#what-is-hashing-and-whyto-useit)
   * [Parsing](#parsing)
      * [Parsing - Standard Input](#parsing---standard-input-Source-Code)
      * [Parsing -qr](#parsing--qr-source-code)
      * [Parsing -pqrs](#parsing--pqrs-source-code)
   * [Hash](#hashing)
      * [Hash MD5](#hash-md5-source-code)
      * [Hash SHA224](#hash-sha224-source-Code)
      * [Hash SHA256](#hash-sha256-source-Code)
      * [Hash SHA384](#hash-sha384-source-Code)
      * [Hash SHA512](#hash-sha512-source-Code)

      
* [Suggestions and tips](#suggestions-and-tips)
* [Resource and References](#resources-and-references)

# Cloning Repository
```
https://github.com/mohammadbutt/42_ft_ssl_md5.git
```

# Installing ft_ssl macOS only
```
make
```

# ft_ssl Usage
```
./ft_ssl md5 [-pqr] [-s string] [files ...]
./ft_ssl sha224 [-pqr] [-s string] [files ...]
./ft_ssl sha256 [-pqr] [-s string] [files ...]
./ft_ssl sha384 [-pqr] [-s string] [files ...]
./ft_ssl sha512 [-pqr] [-s string] [files ...]
```

# Program Installation gif Demo

# Program Usage gif Demo

# Project Summary

### What is hashing and why to use it

Test

### Parsing
#### Parsing - Standard Input [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_parse_standard_input.c)
When the user just enters `./ft_ssl`, then the program enters the standard input mode through the function called "read_stdin_loop" that takes in a string with a buffer of 8 to store the name of the hashing algorithm. "read_stdin_loop" reads in a continuous while loop and the loop keeps on running as long as one of the hashing alogrithms, "md5", "sha224", "sha256", "sha384", and "sha512", are not found. Function is_md_algorithm_valid compares the string entered by the user, if the string matches the hashing algorithm then the is_md_algorithm_valid returns true and read_stdin_loop returns the name of the hashing algorithm entered by the user. Function, "if_control_d_exit_program" allows the user to stop and exit the program by pressing `Control + D`, just like the original openssl.

Once the hashing algorithm has been stored, then the stream is ran again to allow the user to end the string they would like to hash. In order to store the string to hash, the program enters the functions called, "mini_gnl_stdin". Function "mini_gnl_stdin" reads 1 byte at a time, and stores the string by using "ft_strjoin", a pointer is set to the temporary string which points to the actual string where the message is being stored using ft_strjoin. A temporary pointer is created because the temporary pointer is used to free what was previously stored in the actual string. If this is not done properly, there will be memory leaks. And because the actual string gets the address of the new pointer, since "ft_strjoin" returns the memory address of newly allocated/malloced char * string.

#### Parsing -qr [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_parse_pqrs.c)
If there are more than 2 arugments and the hashing algorithm is one of the valid algorithms then the program enters the function called, "ft_ssl_parse_qr". One of the things this function does is to traverse through to check if `-p` or `-s` appear anywhere. If `-p` or `-s` dont appear in any of the arguments, but `-q` or `-r` appear then the program will call onto mini_gnl_stdin, which will read the text entered by the user in a stream, just like the program reads text in standard input. If `-p` or `-s` appear anywhere, then the program simply leaves that function, without returning a value.

#### Parsing -pqrs [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_parse_pqrs.c)
If there are more than 2 arguments and the hashing algorithm is one of the valid algorithms and `-s` or `-r` were detected in the function "ft_ssl_pase_qr", then the program enters the function, "ft_ssl_parse_pqrs". This is where the program collects flags. If `-q` appears then ssl->flag.q is set to true. If `-r` appears then ssl->flag.r is set to true. If `-q` or `-r` appear then the program conitnues to collect the remaining flags in that argument. But if `-p` appears, then ssl->flag.p is set to true, but then it is also processed to hash the message. Similar is true for `-s`, as soon as `-s` appears the program stops collecting flags, and if there are characters that appear after `-s` in the same argument will be considered a string. When `-q` is true then the hashing algorithm and the hashing string or file name are not printed, just the hash is printed. If the `-r` is set to true then the printing order is reversed to print the hash first and then the file name or string. When the `-r` flag is true name of the of hashing algorithm is not printed.

### Hash

After parsing is done, hashing algorithm and and the user message is stored. These are then passed through one of the hashing algorithms, MD5, SHA224, SHA256, SHA384, and SHA512. Below is a brief explanation of how these algorithms work with my implemented source code. 

#### Hash MD5 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_md5.c)



#### Hash SHA224 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha224.c)


#### Hash SHA256 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha256.c)


#### Hash SHA384 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha384.c)


#### Hash SHA512 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha512.c)



### Rules for `-s`

1. Anything after `-s` is a string. Even `p`, `q`, `r`.
   1. Example 1, `./ft_ssl md5 -spqr` will hash the string "pqr".
   2. Example 2, `./ft_ssl md5 -ss` will hash the string "s".
2. `-s` flag needs another string. There are one of two ways to have a string. One, there have to be characters in the same argument after -s. Two, there has to be a string argument after `-s` as shown below:
   1. `-sabc`
   2. `-s` abc
3. `./ft_ssl md5 -s` will result in the following error message:
   ``` 
   md5: option requires an argument -- s
   usage: md5 [-pqrtx] [-s string] [files ...]
   ```

### Rules for `-p`
1. `./ft_ssl md5 -p` allows for standard input stream.
2. `./ft_ssl md5 -pppp` allows for standard input stream for the first 'p', but second, third, and fourth p is hashed as an empty string. So there will be four hashes.
3. `./ft_ssl md5 -pqrqr` allows for standard input stream for the first 'p', but remaining 'qrqr' flags are only hashed once as an empty string. So there will be two hashes.
4. `./ft_ssl md5 -ps` allows for standard input stream for the first 'p' "abc" is entered, but for 's', following error message is printed:
   ```
   abc
   0bee89b07a248e27c83fc3d5951213c1
   md5: option requires an argument -- s
   usage: md5 [-pqrtx] [-s string] [files ...]
   ```
5. `./ft_ssl md5 -psss` allows for standard input stream for the first 'p' "abc" is entererd, for 's', it stores second and third s as a string as "ss", as shown below:
   ```
   abc
   0bee89b07a248e27c83fc3d5951213c1
   MD5 ("ss") = 3691308f2a4c2f6983f2880d32e29c84
   ```
6. `./ft_ssl md5 -psss -sss` will have the following hash:
   ```
   abc
   0bee89b07a248e27c83fc3d5951213c1
   MD5 ("ss") = 3691308f2a4c2f6983f2880d32e29c84
   MD5 ("ss") = 3691308f2a4c2f6983f2880d32e29c84
   ```
### Rules for `-r` and `-q`
1. If there are only three arguments as shown below, then the `q` and `r` behave in a similar manner to `-p` flag in reading the input from the stream, but it is only true if `-q` and `-r` are the only flags:
   ```
   ./ft_ssl md5 -q
   ./ft_ssl md5 -r
   ```
   
### Five steps are performed to compute the message digest of the message.
   1. Append padding bits. ✔
   2. Append Langth. ✔
   3. Initialize MD Buffer. ✔
   4. Process Message in 16-word blocks
   5. Final Output

# Resources and References
1. [Reading from stdin - stackoverflow](https://stackoverflow.com/questions/15883568/reading-from-stdin)
2. [Design Principles and Design Patterns by Robert C Martin](https://fi.ort.edu.uy/innovaportal/file/2032/1/design_principles.pdf)
4. [md5 47 parsing - Open Source Apple](https://opensource.apple.com/source/text_cmds/text_cmds-47/md5/md5.c.auto.html)
5. [md5 99 parsing - Open Source Apple](https://opensource.apple.com/source/text_cmds/text_cmds-99/md5/md5.c.auto.html)
6. [md5 algo - Open Source Apple](https://opensource.apple.com/source/cvs/cvs-19/cvs/lib/md5.c)
6. [md5 algo - Open Source Apple](https://opensource.apple.com/source/xnu/xnu-1504.7.4/libkern/crypto/md5.c)
6. [md5 padding - stackoverflow](https://crypto.stackexchange.com/questions/29685/computing-the-padding-of-md5)
7. [Big Endian, Little Endian - Stackoverflow](https://stackoverflow.com/questions/46109815/convert-string-from-big-endian-to-little-endian-or-vice-versa-in-python)
8. [Big Endian, Little Endian - Yolinux](http://www.yolinux.com/TUTORIALS/Endian-Byte-Order.html)
9. [MD5 - Wikipedia](https://en.wikipedia.org/wiki/MD5)
9. [The MD5 Message-Digest Algorithm - tools.ietf.org](https://tools.ietf.org/html/rfc1321)
10. [MD5 Implementation in C# - Rosettacode](https://rosettacode.org/wiki/MD5/Implementation#C)
11. [MD5 Implementation in C - Rosettacode](https://rosettacode.org/wiki/MD5#C)
11. [MD5 Source Code - tls.mbed.org](https://tls.mbed.org/md5-source-code)
12. [MD5 Source Code - Github](https://github.com/t-crest/patmos-benchmarks/tree/master/Mediabench/pgp/rsaref/source)
13. [SHA256 in Lua](http://lua-users.org/wiki/SecureHashAlgorithmBw)
14. [SHA256 - tls.mbed.org](https://tls.mbed.org/sha-256-source-code)
15. [SHA256 - Github](https://github.com/ogay/sha2/blob/master/sha2.c)
16. [SHA256 - Open Source Apple](https://opensource.apple.com/source/xnu/xnu-344/bsd/crypto/sha2/sha2.c.auto.html)
17. [SHA256 & SHA512 - Open Source Apple](https://opensource.apple.com/source/CommonCrypto/CommonCrypto-7/Source/sha2.c)
18. [SHA256 & SHA512 - tools.ietf.org](https://tools.ietf.org/html/rfc4634#page-6)
