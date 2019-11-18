# 42_ft_ssl_md5: Cryptographic Hashing Algorithms 

### Pupose of the project is to recode md5(1) and openSSL (sha2) hashing algorithms that provide communications security over computer network by taking an input message to produce digital fingerprint.

#### Project file: [ft_ssl_md5](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/ft_ssl_md5.en.pdf)

Allowed C System Calls: open(2), close(2), read(2), write(2)

Allowed C functions: malloc(3), free(3)

Additional functions: strerror(3), exit(3).

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

# Resources and References:
1. [Reading from stdin - stackoverflow](https://stackoverflow.com/questions/15883568/reading-from-stdin)
2. [Design Principles and Design Patterns by Robert C Martin](https://fi.ort.edu.uy/innovaportal/file/2032/1/design_principles.pdf)
4. [md5 47 - Open Source Apple](https://opensource.apple.com/source/text_cmds/text_cmds-47/md5/md5.c.auto.html)
5. [md5 99 - Open Source Apple](https://opensource.apple.com/source/text_cmds/text_cmds-99/md5/md5.c.auto.html)
