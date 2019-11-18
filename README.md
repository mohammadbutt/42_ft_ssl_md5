# 42_ft_ssl_md5: Cryptographic Hashing Algorithms 

### Pupose of the project is to recode md5(1) and openSSL (sha2) hashing algorithms that provide communications security over computer network by taking an input message to produce digital fingerprint.

#### Project file: [ft_ssl_md5](https://github.com/mohammadbutt/42_ft_ssl_md5/blob/master/docs_and_media/ft_ssl_md5.en.pdf)

Allowed C System Calls: open(2), close(2), read(2), write(2)

Allowed C functions: malloc(3), free(3)

Additional functions: strerror(3), exit(3).

### Rules for `-s`

1. Anything after `-s` is a string. Even `p`, `q`, `r`. Example 1, `./ft_ssl md5 -spqr` will hash the string "pqr". Eample 2, `./ft_ssl md5 -ss` will hash the string "s".
2. `-s` flag needs another string. There are one of two ways to have a string. One, there have to be characters in the same argument after -s. Two, there has to be a string argument after `-s` as shown below:
   1. `-sabc`
   2. `-s` abc



# Resources and References:
1. [Reading from stdin - stackoverflow](https://stackoverflow.com/questions/15883568/reading-from-stdin)
2. [Design Principles and Design Patterns by Robert C Martin](https://fi.ort.edu.uy/innovaportal/file/2032/1/design_principles.pdf)
3. [Testing vogsphere git](https://fi.ort.edu.uy/innovaportal/file/2032/1/design_principles.pdf)
