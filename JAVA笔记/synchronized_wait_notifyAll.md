```java
/*synchronized:
public synchronized void produce() 和 synchronized (this) {代码块...} 的作用是相同的，
它们都用于实现同步访问方法或代码块synchronized (this) 是在代码块中使用synchronized关键字，以当前对象
（即this）作为锁对象。当线程进入到这个代码块时，它会获取当前对象的监视器锁，执行代码块内的内容，然后释放锁。
这样可以确保同一时间只有一个线程可以执行这个代码块。synchronized (this) 的作用范围更灵活，
可以将代码块的范围限定在需要同步的关键区域内，而不是整个方法。*/

/*	wait()和notifyAll()是Java中内置的用于实现条件变量的方法，而await()和signal()是Condition接口提供的方法。
wait()和notifyAll()是在Object类中定义的方法，用于实现基本的线程等待和唤醒机制。它们需要在synchronized代码块或方法中使用，
因为它们依赖于对象的监视器锁（即对象锁）。wait()用于使当前线程进入等待状态，并释放对象的监视器锁，等待其他线程调用notify()
或notifyAll()来唤醒它。notifyAll()则用于唤醒所有等待在该对象上的线程。
	await()和signal()需要在使用Lock对象创建的Condition上调用，因为它们依赖于特定的锁,
Condition接口提供了更多的灵活性和额外的特性，如支持多个条件、可中断的等待等。*/


import java.util.LinkedList;
import java.util.Queue;

public class SynchronizedClass {
    private final Queue<Integer> buffer = new LinkedList<>();
    private final int capacity = 5;

    // 或者 public synchronized void produce()
    public void produce() throws InterruptedException {
        synchronized (this) {
            // 检查缓冲区是否已满
            while (buffer.size() == capacity) {
                System.out.println("Buffer is full. Producer is waiting...");
                wait(); // 等待消费者唤醒
            }

            // 生成一个随机物品
            int item = (int) (Math.random() * 100);
            buffer.offer(item);
            System.out.println("Produced: " + item);

            notifyAll(); // 唤醒其他等待的线程（可能是生产者或消费者）
        }
    }

    // 或者 public synchronized void consume()
    public void consume() throws InterruptedException {
        synchronized (this) {
            // 检查缓冲区是否为空
            while (buffer.isEmpty()) {
                System.out.println("Buffer is empty. Consumer is waiting...");
                wait(); // 等待生产者唤醒
            }

            // 从缓冲区中取出一个物品并消费
            int item = buffer.poll();
            System.out.println("Consumed: " + item);

            notifyAll(); // 唤醒其他等待的线程（可能是生产者或消费者）
        }
    }

    public static void main(String[] args) {
        final SynchronizedClass demo = new SynchronizedClass();

        Runnable producerRunnable = new Runnable() {
            @Override
            public void run() {
                try {
                    for (int i = 0; i < 10; i++) {
                        demo.produce();
                        Thread.sleep(100);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };

        Runnable consumerRunnable = new Runnable() {
            @Override
            public void run() {
                try {
                    for (int i = 0; i < 10; i++) {
                        demo.consume();
                        Thread.sleep(150);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };

        Thread producerThread = new Thread(producerRunnable);
        Thread consumerThread = new Thread(consumerRunnable);

        producerThread.start();
        consumerThread.start();

        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

```
