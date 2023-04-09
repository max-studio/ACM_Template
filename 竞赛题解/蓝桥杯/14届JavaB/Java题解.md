##  A: 阶乘求和

**题目思路：**

因为累加的阶乘数非常大，暴力循环需要202320232023次，时间复杂度高且没有任何基本类型可以装下，题目告诉只需要S的末尾9位数字，所以当n！的后9位数都是0时往后的所有数据的后9位数都不会改变，当查找到n！% 1e9 == 0时退出循环即可。 答案： 420940313

```java
public class Main {
    public static final long MOD = 1000000000;
    public static void main(String[] args) {
        long n = 1; // 记录n！
        long i = 1;	// 累加变量
        long s = 0; // 存储Sn
        while (n % MOD != 0){
            n = (n * i) % MOD;
            s = (s + n) % MOD;
            i++;
        }
        System.out.println(s);
    }
}
```



## B: 幸运数字

**题目思路:**

直接调用java内部API：

```Integer.toBinaryString(); //10 -> 2 ```

```Integer.toOctalString() // 10 -> 8```

```Integer.toHexString() // 10 - 16```

或者手写进制转换,再进行逐位求和，暴力判断到2023的结束。  答案：215040

```java
/*
* 解法1:
* 利用api
*/
public class Main {
    public static void main(String[] args) {
        int cnt = 0;	//记录成立个数
        int num = 1;	//判断数字
        while (true){
            if(isB(num) && isO(num) && isD(num) && isH(num)){//2,8,10,16进制判断
                cnt++;
            }
            if(cnt == 2023){ // 到2023个成立的数输出并退出
                System.out.println(num);
                break;
            }
            num++;
        }
    }
    public static boolean isD(int num){
        int sum = 0;
        int t = num;
        while (t != 0){
            sum += t % 10;
            t /= 10;
        }
        return num % sum == 0;
    }
    public static boolean isB(int num){
        int sum = 0;
        String t = Integer.toBinaryString(num); // api转换后是String类型需要用字符串操作
        for(int i = 0; i < t.length(); i++){
            sum += t.charAt(i) - '0';
        }
        return num % sum == 0;
    }
    public static boolean isO(int num){
        int sum = 0;
        String t = Integer.toOctalString(num);
        for(int i = 0; i < t.length(); i++){
            sum += t.charAt(i) - '0';
        }
        return num % sum == 0;
    }
    public static boolean isH(int num){
        int sum = 0;
        String t = Integer.toHexString(num);
        for(int i = 0; i < t.length(); i++){
            if(t.charAt(i) >= 'a'){
                sum += t.charAt(i) - 'a' + 10;	// 字母情况特殊判断
            }else{
                sum += t.charAt(i) - '0';
            }
        }
        return num % sum == 0;
    }
}

```

```java
/*
* 解法2:
* 手写进制转换判断
*/
public class Main {
    public static void main(String[] args) {
        int cnt = 0;
        int num = 1;
        while (true) {
            if (check(2, num) && check(8, num) && check(10, num) && check(16, num)) {
                cnt++;
            }
            if (cnt == 2023) {
                System.out.println(num);
                break;
            }
            num++;
        }
    }
    public static boolean check(int base, int num){
        int t = num;
        int sum = 0;
        while (t != 0){
            sum += t % base;
            t /= base;
        }
        return num % sum == 0;
    }
}
```



## C: 数组切分

**题目思路：**

要求分割两个子集，其中一个可以为空集，且两个集合为偶数，所有第一步判断集合的总和是否为偶数，如果不为偶数则直接判定为0个，再进行深度收搜判断

```java
import java.util.Scanner;

public class MainC {
    public static final long MOD = 1000000007;
    public static long cnt;
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int T = scan.nextInt();
        while (T-- > 0){
            int n = scan.nextInt();
            int[] a = new int[n];
            int sum = 0;
            for(int i = 0; i < n; i++){
                a[i] = scan.nextInt() % 2;
                sum += a[i];
            }
            if(sum % 2 == 1){
                System.out.println(0);
                continue;
            }
            cnt = 0;
            dfs(a, 0, 0, sum, new boolean[n]);
            System.out.println(cnt);
        }
    }
    public static void dfs(int[] a, int index, int left, int sum, boolean[] flag){
        if(left % 2 == 0 && (sum - left) % 2 == 0){
            cnt = (cnt + 1) % MOD;
        }
        if(index == a.length){
            return;
        }
        for(int i = index; i < a.length; i++){
            if(flag[i]){
                continue;
            }
            flag[i] = true;
            dfs(a, index + 1, left + a[i], sum, flag);
            flag[index] = false;
        }
    }
}
```







