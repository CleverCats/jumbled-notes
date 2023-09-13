epoll触发的两种工作模式:LT / ET

LT: level trigged 水平触发【保姆式触发】
释:在epoll_wait时如果返回的event未被处理,那么在下次调用epoll_wait时会直接返回上次未被处理的事件,
    如此反复,直到此次epoll事件被处理,才会返回下一次的epoll事件
作用:在进行TCP接入时一般采取LT保姆式触发,保证每一个完成TCP握手的客户端都能成功被accept
       ps:在非客户端接入事件处理中一般不采用该方法,会导致效率较低【低速模式】,这也是epoll默认的工作模式
           如果需要调用ET模式,需要指定EPOLLET参数


ET: edge trigged 边缘触发模式,不同于LT模式,边缘触发模式只会触发一次,如果epoll_wait返回了的事件未被处理
    那么下一个epoll_wait【系统内核】也不会在通知该事件【只对非阻塞socket有用】
