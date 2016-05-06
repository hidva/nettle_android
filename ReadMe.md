
## 模块介绍

*   [nettle][0] 加解密的 Android 构建.首先 nettle 官方是没提供 Android 构建支持的,而且其原生构
    建方式是:

    ```shell
    ./configure --args
    make
    make check
    make install
    ```

    所以如果要在 Android 构建时,将 nettle 的所有特性都引入进来,那么会造成配置复杂,而且肯定会
    引入了不少坑,比如之前老版本加解密方案中总是将宏`SIZEOF_LONG`定义为`8`!那么在 32 位 Android
    上就有可能导致会有 4 字节处于未被加密

*   所以这里只是将 nettle 的 AES,SHA3 算法引入.

*   最关键是,为什么不使用 openssl,因为在我这个时代(20160507),Openssl 还不支持构建 Android
    64 位 so!!!天啦撸



## 参考

*   [nettle.git][0]
*   [nettle 官网][1]

[0]: <https://git.lysator.liu.se/nettle/nettle>
[1]: <https://www.lysator.liu.se/~nisse/nettle/>
