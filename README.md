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
  * [MD5](#md5)
  * [SHA224](#sha224)
  * [SHA256](#sha256)
* [Program Installation gif Demo](#program-installation-gif-demo)
* [Program Usage gif Demo](#program-usage-gif-demo)
* [Project Summary](#project-summary)
   * [What is hashing and why use it](#what-is-hashing-and-why-use-it)
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

      
* [Acknowledgment](#acknowledgment)
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
![](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/Media/installation_720p_24fps.gif)

Yes! This is all you need to do to install the program! Scroll down for usage.
# Program Usage gif Demo
## MD5
![](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/Media/usage_md5_4k_24fps.gif)

## SHA224
![](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/Media/usage_sha224_1080p_24fps.gif)

## SHA256
![](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/Media/usage_sha256_1080p_24fps.gif)

# Project Summary

### What is hashing and why use it

Hashing is the process of taking a piece of information and then passing it through an algorithm to generate new values. For instance, if the piece of information was the word, "cat", is passed through MD5 hashing algorithm, then the generated hash will be "d077f244def8a70e5ea758bd8352fcd8". Now if an extra character is added or appended at the word, let's say, '1', to make it "cat1", this will generate a new MD5 hash value, which is "a980d10665f268b0ec6c13ebea43034f". These hashing algorithms are one way, what that means is, someone can not take, "a980d10665f268b0ec6c13ebea43034f" to retrieve the word, "cat1". These hashing algorithms are designed to be one way, to take a piece of information and then turn it into a hash, but of course, it is possible to store commonly used everyday words with hashes, and there are some websites that already have commonly used hashes stored with the original piece of information. Matter of fact, if you searched, "a980d10665f268b0ec6c13ebea43034f", in a search enigine it will give you search results, that mention "cat1". I looked up the hash in bing, msn, yahoo, duckduckgo, google and they all showed search results that mentioned "cat1". This is why md5 is not a good hashing algoritm to use because the generated hash is 32 characters long. SHA2 has been the industry standard, with SHA256 producing a 64 character long hash and SHA512 producing a 128 characters long hash. More detail about each hashing algorithm is below.

This unique nature to take a message and turn it into a completely different value or a hash is why these hashing algorithms are so useful. For instance, when people set up their bank account online logins then it is highly likely that the banks will use one of the hashing methods to convert the password and credit card numbers into a hash, so in case there is a cybersecuritry attack it would make it hard for hackers to readily use the information. And when the user enters their password, the system is designed to take the entered password and then turn that into a hash, this hash will be compared with the hash of the password that was set up.

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

Each hashing algorithm goes through what is known as "padding". First the length of the information, or the string is calculated. For instance, if the inforamtion or string is, "github", then the length of this string will be 6. This length is first set equal to a variable called padding because this padding number is what will be incremeted during the padding process. The process of padding is to pad until the (padding number) % 512bits = 448bits. The generated number will be 64 bits less than 512, which is a multiple of 448. The goal is to have multiples of 448 because 64 bits are added afterwards to bring it upto 512bits. I did all my calculations in bytes so in my case as long as (padding) % (64 bytes) is not equal to (56 bytes), I would (add one to padding). If a word is already exactly a multiple of 56 in length, it still gets padded and 64 bytes are added to it. At least 1, and at most 64 bytes are added to the padding. Once it has been determined how much padding needs to be performed, that number + 8 more bytes are allocated using ft_memalloc. ft_memalloc, does three things. One, allocates memory. Two, checks if memory was allocated succesfully. Three, bzeros entire string using ft_bzero to fill the string with with zeros to ensure that the newly allocated string does not have garbagae values, and the string is clean. 

Now the original string "github" is copied onto the new string that was just allocated memory using ft_strcpy. 1 is appended at the index of the original length of the string. MD5 source code documentation and a lot of MD5 references refer to this part of padding as "appending 1". Literal 1 does not get appended. Value 128, which is equal to 0x80 in hexadecimal is what gets appended at the last index of the allocated string. From here rest of the string gets filled with literal zeros upto the number that was calculated for padding. Since I used ft_memalloc to allocate memory, where I have also added a functionality to fill the string with zeros, I was able to skip this part of filling the string with literal zeros.

Last step in MD5 for padding is to append the length of the original message in the form of 64 bit representation to the message that was just padded. I multiplied the length of the message with 8, so lenght of, "github" 6 mulitplied by 8 is equal to 48 bits are set equal to the last index of the padded message.

Next the padded messaged is processed in 16-word blocks which is also known as "chunking". When chunking is done, chunking is performed on uint32_t data type. Suppose padded_message is equal to "abcdefghijklmnopqrstuvwxyz", then padded_message at index 0 is 'a', index 1 is 'b', index 2 is 'c', and index 3 is 'd', but when the padded message is saved to a uint32_t data type, then index 0 will be 'a', but index 1 will be 'e', index 2 will be 'i', and index 3 will be 'm'. This may seem strange behavior, but it is not. Since char data type uses 1 byte, which is why it will show value of every cosecutive character, but uint32_t uses 4 bytes of memory which is why it stores and shows value of every 4th character. Memcpy or strcpy were not performed for this step, I just simply set a uint32_t pointer to the padded message and then type casted padded message with uint32_t. This new string of uint32_t data type is used with bitwise manipulation to constantly update a, b, c, d values. When values a, b, c, and d are done getting updated, their bits are swapped which is also known as Endianness because the original source code is written in little-endian. Swapping bits of each value for a, b, c, and d converts them from little-endian to big endian, which is then printed in hexadecimal to produce a 32 characters long hash

#### Hash SHA224 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha224.c)
SHA224 is relatively similar to SHA256. Below are the differences of SH224:
1. In SHA224 there are different initilizations values for h. These are also known as "init"
2. In SHA224 only 7 h values are printed, that are h0, h1, h2, h3, h4, h5, and h6. Value h7 is omittied when hash is printed. Each h value will print 8 characters, this produces a 56 characters long hash for SHA224.

I did SHA256 first, which allowed me to use all of the core and helper SHA256 functions for SHA224.

#### Hash SHA256 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha256.c)
Padding in SHA256 is similar to MD5. I did some things differently to perform padding for SHA256. After I calculate the number for padding which is done the same way as it is done in MD5, chunk of 512 bits is calculated. In order to calculate the chunk of 512 bits. Padded number will always be a multiple of 56. 8 is added to this padded number to bring this upto a multiple of 64. Equation that I was able to formulate to caluclate the chunks of 512 bits is (padded_message + 8) is divided by 64 to get the chunk of 512 bits. Suppose a string is 70 characters long, when padding is calculated, padded number will be 120. (120 + 8) / 64 = 2.

There will be two chunks of 512bits. Copying user message or string and appending 1 is done the same way as it is done in MD5, but in SHA256 destination data type will be a unit32_t data type, which is also known as unsigned integer 32, because all of the calculations in SHA256 are performed on unit32_t data types.

In SHA256 before appending the length at the last index of the string, uint32_t values of the destination variable are swapped.

Finally to append the length of the original string, index is calculated by multiplying 16 with chunk of 512 bit and subtracting 1 from it. Length of the original string is appended at this index.

The destination variable are used to constantly update the values of h0, h1, h2, h3, h4, h5, h6, and h7. Bitwise with rotating and shifting bits are used to constantly modify the h values.

Once the h values are done getting updated all of the h values are printed in hex. Each h value will print 8 characters, this produces a 64 characters long hash for SHA256.

#### Hash SHA384 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha384.c)
SHA384 is also relatively similar to SHA512. Below are the difference for SHA384:
1. SHA384 also uses different initialization values for h. These are also known as "init".
2. SHA384 only prints 6 h values. These h values are, h0, h1, h2, h3, h4, and h5. Values for h6 and h7 are omitted when the hash is printed. Each h value will print 16 characters, this produces a 96 characters long hash for SHA384.

I did SHA512 first, which allowed me to use all of the core and helper SHA512 functions for SHA384.


#### Hash SHA512 [Source Code](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/srcs/ft_ssl/ssl_hash_message_sha512.c)
Padding in SHA512 is a lot similar to SHA256 then it is to MD5. Some things are modified in SHA512 when padding is performed. First thing that is different in SHA512 is that I used uint64_t data type for all of the variables to store the information instead of uint32_t. Second thing that is different in SHA512 is how the padded number is calculated. In SHA512, multiples of 896 and 1024 bits are used, but since I have done all my calculations in bytes, I used multiples of 112 and 128 bytes. So if a string was a 100 characters long then 12 more bytes are to it, bringing it upto 112 bytes a mutliple of 112, and then 16 bytes are added to it bring it upto 128 making it a multiple of 128.

When string copy is performed to stored the user message into a destination variable, the only thing that is different from SHA256 is that the destination variable for SHA512 is uint64_t data type, so it will store every 8th character of the string.

SHA512 also uses what is known as "chunking" to process messages in 1024 bits. Equation that I formulated to calculate chunk of 1024 bits is (padded_message + 16) / 128. If the user message is less than 112 characters long than this equation will give 1 chunk of 1024 bits. And suppose if the user message is 130 characters long then this equation will produce 2 chunks of 1024 bits.

Once user message has be copied to destination variable and chunks of 1024 bits have been calculated, the values of the destination variable are swapped. Since the destination variable is uint64_t data type, I created a function ft_swap_64bit, which swaps the values of a unit64_t data type variable.

Finally to append the length of the original string, index is calculated by multiplying 16 with chunk of 1024 bit and subtracting 1 from it. Length of the original string is appended at this index.

The destination variable is used to constantly updated the values of h0, h1, h2, h3, h4, h5, h6, and h7. Just like SHA256, bitwise with rotating and shifting bits are used to constatnyl modify the h values.

Once the h values are done getting updated all of the h values are printed in hex. Each h value will print 16 characters, this produces a 128 characters long hash for SHA512.

# Acknowledgment
Thank you to [JC](https://github.com/JCTGY) for encouraging me to go the extra mile and also covering SHA224, SHA384, and SHA512. Reading and understanding his code was also instrumental for me to recode this project.

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
