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

直接调用 java 内部 API 或者手写进制转换,再进行逐位求和，暴力判断到 2023 的结束。  答案：215040

```java
/*
* 解法 1:
* 利用 api
*/
public class Main {
    public static void main(String[] args) {
        int cnt = 0;	//记录成立个数
        int num = 1;	//判断数字
        while (true){
            if(isB(num) && isO(num) && isD(num) && isH(num)){//2, 8, 10, 16 进制判断
                cnt++;
            }
            if(cnt == 2023){ // 到 2023 个成立的数输出并退出
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
        String t = Integer.toBinaryString(num); // api 转换后是 String 类型需要用字符串操作
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
* 解法 2:
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

要求分割两个子集，其中一个可以为空集，且两个集合为偶数，所有第一步判断集合的总和是否为偶数，如果不为偶数则直接判定为 0 个否则再进行深度收搜判断，也可以利用奇数个数与偶数个数的排列组合实现（未实现，待定）

```java
import java.util.Scanner;

public class Main {
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
            if(sum % 2 == 1){ // 总数为奇，没有一个条件成立
                System.out.println(0);
                continue;
            }
            cnt = 0;
            dfs(a, 0, 0, sum, new boolean[n]); // 数组，下标位置，子集总和，总数，记录重复情况 
            System.out.println(cnt);
        }
    }
    public static void dfs(int[] a, int index, int left, int sum, boolean[] flag){
        if(left % 2 == 0 && (sum - left) % 2 == 0){ // 子集合与补集满足条件自增
            cnt = (cnt + 1) % MOD;
        }
        if(index == a.length){ // 越界退出
            return;
        }
        for(int i = index; i < a.length; i++){ 
            if(flag[i]){ // 防止重复选择
                continue;
            }
            flag[i] = true; // 记录已选择
            dfs(a, index + 1, left + a[i], sum, flag); // 指针向前，子集累计
            flag[index] = false; // 删除标记
        }
    }
}
```



## D: 矩形总面积

**题目思路：**

先将两个矩形需要占的最大板块的左下角与右上角找出来，然后依次遍历这个板块被占领的地区

如图所示遍历情况是不会重复计算多层矩形覆盖的面积

![image-20230409204744348](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230409204744348.png)

```java
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int x1 = scan.nextInt();
        int y1 = scan.nextInt();
        int x2 = scan.nextInt();
        int y2 = scan.nextInt();
        int x3 = scan.nextInt();
        int y3 = scan.nextInt();
        int x4 = scan.nextInt();
        int y4 = scan.nextInt();
        // 寻找最远左下角边界
        int minI = Math.min(y1, y3);
        int minJ = Math.min(x1, x3);
        // 寻找最远右上角边界
        int maxI = Math.max(y2, y4);
        int maxJ = Math.max(x2, x4);
        long res = 0;
        for(int i = minI; i < maxI; i++){
            for(int j = minJ; j < maxJ; j++){      
                if(i >= y1 && i < y2 && j >= x1 && j < x2){ // 判断当前点是否属于矩形内
                    res += x2 - j; // 加当前行最右列到当前列的位置
                    j = x2;	// 指针到当前矩形最右边
                }
                if(i >= y3 && i < y4 && j >= x3 && j < x4){ // 同上
                    res += x4 - j;
                    j = x4;
                }
            }
        }
        System.out.println(res);
    }
}
```





## E: 蜗牛

**题目思路：**

BFS解最短路径，蜗牛能走的情况:

​	1.现在在地面可以往前的情况向前到下一个竹竿（之后必须往上，用一个 flag 标记  0，不可继续向前）

​	2.在地面不能向前只能向上进入传送门入口到下个竹竿传送门的出口

​	3.现在 传送门出口有两个方案，A. 进入当前竹竿的传送门入口；B.向下到竹竿底部，flag 标记 1，可以直接向前

注意:在出口的时候入口在出口上面还是下面的速度是不同的!

```java
import java.util.*;

public class Main {
    public static final double up = 1 / 0.7;	//向上配速
    public static final double down = 1 / 1.3;	//向下配速

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] arr = new int[n];
        for(int i = 0; i < n; i++){
            arr[i] = scan.nextInt();
        }
        ArrayList<int[]> list = new ArrayList<>(); // 也可以用数组存放
        for(int i = 0; i < n - 1; i++){
            int a = scan.nextInt();
            int b = scan.nextInt();
            list.add(new int[]{a, b});	//存放当前竹竿的入口与下一个竹竿出口
        }

        Queue<double[]> queue = new LinkedList<>();
        queue.offer(new double[]{arr[0], 0, 0, arr[0], 1}); // 数组分别对应 x, y, idx(竹竿序号), time(花费时间), flag(是否可以直接向前的标记) 现在记录的是 (0, 0) -> (arr[0], 0) 的位置花费的时间，即到第一个竹竿花费的时间
        while (!queue.isEmpty()){
            double[] t = queue.poll(); // 取出并删除头结点
            int idx = (int)t[2];	// 记录竹竿序号
            if(arr[idx] == arr[n - 1] && t[1] == 0){	// 最先到达 (x, y) -> (arr[n - 1], 0) 结束输出花费的时间
                System.out.printf("%.2f", t[3]); // 精度修饰自动四舍五入
                return;
            }
            if(t[4] == 0 && t[1] == 0 && idx + 1 < n){ // (情况 1) 在地面且可以往前不越界的情况
                queue.add(new double[]{ // 向前 idx + 1, y 轴不变 0,时间累计 到下一个竹竿花费的时间 (arr[idx + 1] - t[0]),将 flag 打上不能向上的标记  
                        arr[idx + 1], 0, idx + 1, t[3] + arr[idx + 1] - t[0], 1
                });
            }else{
                if(t[1] == 0 && idx + 1 < n){ // (情况 2) 在地面不能向前的情况
                    queue.add(new double[]{ // 向上到传送门到下一个竹竿的出口位置 (arr[idx + 1], list.get(idx)[1]),自动向前 idx + 1,只花费(地面到传送门路径 * up ), flag 打上可以当到地面可以向前的标记 
                            arr[idx + 1], list.get(idx)[1], idx + 1, t[3] + list.get(idx)[0] * up, 0
                    });
                }else{ //
                    queue.add(new double[]{ // (情况 3A) 向下到地面, flag 标记可以向前
                            t[0], 0, idx, t[3] + t[1] * down, 0
                    });
                    if(idx + 1 < n) {
                        queue.add(new double[]{ // (情况 3B) 在上一个传送门出口进入现在的传送门的入口,判断向上还是向下
                                arr[idx + 1], list.get(idx)[1], idx + 1,
                                t[3] + (list.get(idx)[0] > t[1] ?
                                        (list.get(idx)[0] - t[1]) * up :                              
                                        (t[1] - list.get(idx)[0]) * down), 0
                        });
                    }
                }
            }
        }
    }
}
```



## F: 合并区域

**有特殊情况未考虑,待修改**

```java
import java.util.Scanner;

public class Main {
    public static int max = 0;
    public static int n;
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        int[][] a = new int[n + 1][n + 1];
        int[][] b = new int[n + 1][n + 1];
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                a[i][j] = scan.nextInt();
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                b[i][j] = scan.nextInt();
            }
        }
        int[][] resA = new int[n + 1][n + 1];
        int[][] resB = new int[n + 1][n + 1];
        int maxA = 0;
        int maxB = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(a[i][j] != 0) {
                    if (resA[i - 1][j] > 0) {
                        resA[i][j] = resA[i - 1][j];
                    } else if (resA[i][j - 1] > 0) {
                        resA[i][j] = resA[i][j - 1];
                    } else {
                        resA[i][j] = dfs(i, j, a, new boolean[n + 1][n + 1]);
                    }
                }
                if(b[i][j] != 0) {
                    if (resB[i - 1][j] > 0) {
                        resB[i][j] = resB[i - 1][j];
                    } else if (resB[i][j - 1] > 0) {
                        resB[i][j] = resB[i][j - 1];
                    } else {
                        resB[i][j] = dfs(i, j, b, new boolean[n + 1][n + 1]);
                    }
                }
                max = Math.max(max, Math.max(resA[i][j], resB[i][j]));
                if(i == 1 || i == n || j == 1 || j == n){
                    maxA = Math.max(maxA, resA[i][j]);
                    maxB = Math.max(maxB, resB[i][j]);
                }
            }
        }
        int res = Math.max(max, maxA + maxB);
        System.out.println(res);

    }
    public static int[] py = new int[]{1, -1, 0, 0};
    public static int[] px = new int[]{0, 0, 1, -1};
    public static int dfs(int i, int j, int[][] map, boolean[][] flag){
        if(map[i][j] == 0){
            return 0;
        }
        int cnt = 0;
        for(int idx = 0; idx < 4; idx++){
            int y = i + py[idx];
            int x = j + px[idx];
            if(y > 0 && y <= n && x > 0 && x <= n){
                if(!flag[y][x] && map[y][x] == 1) {
                    flag[y][x] = true;
                    cnt += dfs(y, x, map, flag) + 1;
                }
            }
        }
        return cnt;
    }
}
```



## G: 买二赠一

**题目思路：**

贪心，先排升序，先买最大两个将可以免费的机会用队列存放，后续判断数量低于免费的就直接免费掉

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] a = new int[n + 1];
        for(int i = 1; i <= n; i++){
            a[i] = scan.nextInt();
        }
        Arrays.sort(a);	// 升序排序
        Queue<Double> queue = new LinkedList<>(); // 存放免费机会
        int res = 0;
        while (n >= 0){
            while (!queue.isEmpty()){	
                if(queue.peek() > a[n]){ // 取出最大免费机会比较可以免费则指针向后并删除当前免费机会
                    queue.poll();
                    n--;
                }else {
                    break;	// 否则退出
                }
            }
            if(n > 0) {
                res += a[n]; 
            }
            if(n - 2 > 0) { // 防止越界,并取买的两个数中最小的价值的一半添加到免费机会
                res += a[n - 1];
                queue.offer(a[n  - 1] / 2.0);
            }
            n -= 2;
        }
        System.out.println(res);
    }
}
```



## H: 合并石子

**题目思路：**

利用 `java api TreeMap` 升序特性 key 存放合并后最小堆数 value 存放最小权值，合并操作用链表较方便，DFS 深度优先遍历每种合并情况；

利用取模性质：

合并`(0 -> 1, 1 -> 2, 2 -> 0)` 合并时用 `(color + 1) % 3`；

回溯`(0 -> 2, 1 -> 0, 2 -> 1)` 回溯时用 `(color + 2) % 3`。

```java
import java.util.*;

public class Main {
    public static Map<Integer, Integer> min = new TreeMap<>();
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        LinkedList<Integer> a = new LinkedList<>();
        for(int i = 0; i < n; i++){
            a.add(scan.nextInt());
        }
        LinkedList<Integer> c = new LinkedList<>();
        for(int i = 0; i < n; i++){
            c.add(scan.nextInt());
        }
        dfs(a, c, 0, 0, n); // 堆情况，颜色情况，当前堆的位置，权值，合并后剩余数量
        for(int set : min.keySet()){ // 取第一个值
            System.out.println(set);
            System.out.println(min.get(set));
            break;
        }
    }
    public static void dfs(LinkedList<Integer> a, LinkedList<Integer> c, int index, int w, int cnt){
        for(int i = 0; i < cnt - 1; i++){ // 合并操作
            // 取相邻两个石子的颜色
            int t1 = c.get(i);	
            int t2 = c.get(i + 1);
            if(t1 == t2){	// 相同合并操作
                // 临时存储，待回溯，且删除
                int s1 = a.remove(i); 
                int s2 = a.remove(i); 
                // 合并
                a.add(i, s1 + s2);
                c.remove(i + 1);
                // 改变颜色
                c.set(i, (t1 + 1) % 3);
                // 深搜 刷新权值与剩余堆数
                dfs(a, c, i, w + s1 + s2, cnt - 1);
                // 回溯
                a.set(i, s1);
                a.add(i + 1, s2);
                c.set(i, (t1 + 2) % 3);
                c.add(i + 1, (t1 + 2) % 3);
            }
        }
        // 上面循环完毕后没有可以进行合并的情况进行存放，若有同堆数情况取最小权值
        min.put(cnt, min.get(cnt) == null ? w : Math.min(min.get(cnt), w));
    }
}
```



## I: 最大开支

**暴力超时，待修改**

```java
import java.util.Scanner;

public class MainI {
    public static long max = 0;
    public static int n, m;
    public static long[] k, b;

    public static long H(long k, long b, long x){
        return Math.max(k * x + b, 0) * x;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        n = scan.nextInt();
        m = scan.nextInt();
        k = new long[m];
        b = new long[m];
        for(int i = 0; i < m; i++){
            k[i] = scan.nextLong();
            b[i] = scan.nextLong();
        }
        dfs(n, 0,0);
        System.out.println(max);
    }

    public static void dfs(int people, int idx, long sum){
        if(people == 0 || idx == m){
            return;
        }
        for(int i = 0; i < people; i++){
            for(int j = idx; j < m; j++){
                long h = sum + H(k[j], b[j], i);
                max = Math.max(max , h);
                System.out.println(h);
                dfs(people - i, j + 1, h);
            }
        }
    }
}
```

