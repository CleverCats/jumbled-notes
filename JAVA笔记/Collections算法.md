```java
import java.io.ByteArrayOutputStream;
import java.util.*;

public class CollectionsClass {

	public static void main(String[] args) {

		// 创建一个列表
		List<Integer> numbers = new ArrayList<>();
		numbers.add(3);
		numbers.add(1);
		numbers.add(2);

		System.out.println("Original List: " + numbers);

		// 排序列表
		Collections.sort(numbers);
		System.out.println("Sorted List: " + numbers);

		// 反转列表
		Collections.reverse(numbers);
		System.out.println("Reversed List: " + numbers);

		// 随机打乱列表
		Collections.shuffle(numbers);
		System.out.println("Shuffled List: " + numbers);

		// 二分查找元素
		int index = Collections.binarySearch(numbers, 2);
		System.out.println("Index of 2: " + index);

		// 查找最大元素
		int max = Collections.max(numbers);
		System.out.println("Max Element: " + max);

		// 查找最小元素
		int min = Collections.min(numbers);
		System.out.println("Min Element: " + min);

		// 填充列表
		Collections.fill(numbers, 1);
		System.out.println("Filled List: " + numbers);

		// 复制列表
		/*
		 * List<Integer> copy = new ArrayList<>(numbers.size());
		 * System.out.println(copy.size()); 0 只开辟没定义
		 */
		
		/*Arrays.asList(new Integer[numbers.size()]) 数组转为大小相同的列表
		 *再次作为参数进行ArrayList构造*/
		List<Integer> copy = new ArrayList<>(Arrays.asList(new Integer[numbers.size()]));
		// 或者 List<Integer> copy = new ArrayList<>(numbers);
		System.out.println("copy.size(): "+ copy.size());
		
		Collections.copy(copy, numbers);
		System.out.println("Copied List: " + copy);

        // 替换元素(所有1替换为5)
        Collections.replaceAll(numbers, 1, 5);
        System.out.println("Replaced List: " + numbers);
	}
}

```
