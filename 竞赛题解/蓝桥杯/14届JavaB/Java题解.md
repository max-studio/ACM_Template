##  A: 阶乘求和



**题目思路：**



因为累加的阶乘数非常大，暴力循环需要202320232023次，时间复杂度高且没有任何基本类型可以装下，题目告诉只需要S的末尾9位数字，所以当n！的后9位数都是0时往后的所有数据的后9位数都不会改变，当查找到n！% 1e9 == 0时退出循环即可。 答案： 420940313

```java
public class Main {
    public static final long MOD = 1000000000;
    public static void main(String[] args) {
        long n = 1;
        long i = 1;
        long s = 0;
        while (n % MOD != 0){
            n = (n * i) % MOD;
            s = (s + n) % MOD;
            i++;
        }
        System.out.println(s);
    }
}
```

