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

直接调用java内部API或者手写进制转换,再进行逐位求和，暴力判断到2023的结束。  答案：215040

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

要求分割两个子集，其中一个可以为空集，且两个集合为偶数，所有第一步判断集合的总和是否为偶数，如果不为偶数则直接判定为0个否则再进行深度收搜判断

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



## D: 矩形总面积

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
        int minI = Math.min(y1, y3);
        int maxI = Math.max(y2, y4);
        int minJ = Math.min(x1, x3);
        int maxJ = Math.max(x2, x4);
        long res = 0;
        for(int i = minI; i < maxI; i++){
            for(int j = minJ; j < maxJ; j++){
                if(i >= y1 && i < y2 && j >= x1 && j < x2){
                    res += x2 - j;
                    j = x2;
                }
                if(i >= y3 && i < y4 && j >= x3 && j < x4){
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

```java
import java.util.*;

public class Main {
    public static final double up = 1 / 0.7;
    public static final double down = 1 / 1.3;

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] arr = new int[n];
        for(int i = 0; i < n; i++){
            arr[i] = scan.nextInt();
        }
        ArrayList<int[]> list = new ArrayList<>();
        for(int i = 0; i < n - 1; i++){
            int a = scan.nextInt();
            int b = scan.nextInt();
            list.add(new int[]{a, b});
        }

        Queue<double[]> queue = new LinkedList<>();
        queue.offer(new double[]{arr[0], 0, 0, arr[0], 1}); // x, y ,idx, time, flag
        while (!queue.isEmpty()){
            double[] t = queue.poll();
            int idx = (int)t[2];
            if(arr[idx] == arr[n - 1] && t[1] == 0){
                System.out.printf("%.2f", t[3]);
                return;
            }
            if(t[4] == 0 && t[1] == 0 && idx + 1 < n){
                queue.add(new double[]{ // 向前
                        arr[idx + 1], 0, idx + 1, t[3] + arr[idx + 1] - t[0], 1
                });
            }else{
                if(t[1] == 0 && idx + 1 < n){
                    queue.add(new double[]{ // 向上到传送门
                            arr[idx + 1], list.get(idx)[1], idx + 1, t[3] + list.get(idx)[0] * up, 0
                    });
                }else{
                    queue.add(new double[]{ // 向下
                            t[0], 0, idx, t[3] + t[1] * down, 0
                    });
                    if(idx + 1 < n) {
                        queue.add(new double[]{ // 进入传送门
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
        Arrays.sort(a);
        Queue<Double> queue = new LinkedList<>();
        int res = 0;
        while (n >= 0){
            while (!queue.isEmpty()){
                if(queue.peek() > a[n]){
                    queue.poll();
                    n--;
                }else {
                    break;
                }
            }
            if(n > 0) {
                res += a[n];
            }
            if(n - 2 > 0) {
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
        dfs(a, c, 0, 0, n);
        for(int set : min.keySet()){
            System.out.println(set);
            System.out.println(min.get(set));
            break;
        }
    }
    public static void dfs(LinkedList<Integer> a, LinkedList<Integer> c, int index, int w, int cnt){
        for(int i = 0; i < cnt - 1; i++){
            int t1 = c.get(i);
            int t2 = c.get(i + 1);
            if(t1 == t2){
                int s1 = a.remove(i);
                int s2 = a.remove(i);
                a.add(i, s1 + s2);
                c.remove(i + 1);
                c.set(i, (t1 + 1) % 3);
                dfs(a, c, i, w + s1 + s2, cnt - 1);
                a.set(i, s1);
                a.add(i + 1, s2);
                c.set(i, (t1 + 2) % 3);
                c.add(i + 1, (t1 + 2) % 3);
            }
        }
        min.put(cnt, min.get(cnt) == null ? w : Math.min(min.get(cnt), w));
    }
}
```



## I: 最大开支

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

