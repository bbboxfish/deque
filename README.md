# deque(双向队列)
实现了头尾插入删除O(1),随机增删查O(\sqrt{n})的双向队列.采用大小为500(可随数据规模改变)的block,删除块/合并块(连续两块少于一半元素时)函数保证了块的利用率.实现了iterator和const_iterator的基本功能.