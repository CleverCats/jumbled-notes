```java
public class throwClass {
    public static void main(String[] args) {
        try {
            methodWithThrows();
        } catch (Exception e) {
            // getMessage打印异常的简短描述信息(推荐),
            // printStackTrace()打印异常的详细堆栈跟踪信息，包括异常类型、异常消息以及导致异常的方法调用链
            System.out.println("Caught exception: " + e.getMessage());
        } finally {
            System.out.println("finally run");
        }

        methodWithoutThrows();
    }

    /**
     * 在方法声明中加入了 throws Exception，表示该方法可能会抛出 Exception 异常。
     */
    public static void methodWithThrows() throws Exception {
        throw new Exception("Exception thrown from methodWithThrows");
    }

    /**
     * 没有在方法声明中加入任何异常声明,程序中断,try无法捕获(Threed.sleep是进行了throws的所以可被捕获)。
     */
    public static void methodWithoutThrows() {
        throw new RuntimeException("RuntimeException thrown from methodWithoutThrows");
    }
}
```
