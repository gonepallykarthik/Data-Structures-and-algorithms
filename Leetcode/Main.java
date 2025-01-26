package Leetcode;

import java.util.*;

public class Main {

    public static int minimumOperationsToMakeArraySorted(List<Integer> arr) {
        if (arr.size() == 1)
            return 0;
        int n = arr.size();
        List<Integer> sorted = new ArrayList<>(arr);
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < n; i++) {
            map.put(arr.get(i), i);
        }
        int cnt = 0;
        sorted.sort(Integer::compareTo);

        int i = 0;
        while (i < n) {
            if (arr.get(i).equals(sorted.get(i))) {
                i++;
            } else {
                System.out.println("second executed " + arr.get(i) + " " + sorted.get(i));
                cnt += 1;
                int idx = map.get(sorted.get(i));
                map.put(arr.get(i), idx);
                map.put(arr.get(idx), i);
                int temp = arr.get(i);
                arr.set(i, arr.get(idx));
                arr.set(idx, temp);

                i += 1;
            }
        }

        return cnt;
    }

    public static int minimumOperations(TreeNode root) {
        int cnt = 0;
        Queue<TreeNode> q = new LinkedList<>();
        q.add(root);

        while (!q.isEmpty()) {
            int n = q.size();
            List<Integer> level = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                TreeNode node = q.poll();
                level.add(node.val);

                if (node.left != null)
                    q.add(node.left);
                if (node.right != null)
                    q.add(node.right);
            }
            System.out.println(level);
            cnt += minimumOperationsToMakeArraySorted(level);
        }

        return cnt;
    }

    public static int helper(int idx, int[] nums, int target, int n, int currsum, int[][] dp, int offset) {
        if (idx == n) {
            return target == currsum ? 1 : 0;
        }

        if (dp[idx][currsum + offset] != -1)
            return dp[idx][currsum + offset];

        int add = helper(idx + 1, nums, target, n, currsum + nums[idx], dp, offset);
        int sub = helper(idx + 1, nums, target, n, currsum - nums[idx], dp, offset);

        return dp[idx][currsum + offset] = add + sub;
    }

    public static int findTargetSumWays(int[] nums, int target) {
        int n = nums.length;
        int currsum = 0;
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        int offset = totalSum;
        int[][] dp = new int[n][2 * totalSum + 1];
        for (int i = 0; i < dp.length; i++) {
            Arrays.fill(dp[i], -1);
        }

        return helper(0, nums, target, n, currsum, dp, offset);
    }

    public static int maxScoreSightseeingPair(int[] values) {
        int n = values.length;
        int max = Integer.MIN_VALUE;
        int[] vec = new int[n];
        vec[0] = values[0] + 0;

        for (int i = 1; i < n; i++) {
            vec[i] = Math.max(vec[i - 1], values[i] + i);
        }

        for (int j = 1; j < n; j++) {
            max = Math.max(max, vec[j - 1] + (values[j] - j));
        }

        return max;
    }

    public static int countGoodStrings(int low, int high, int zero, int one) {
        int MOD = 1000000007;
        int[] dp = new int[high + 1];
        Arrays.fill(dp, -1);
        int len = 0;
        return countGoodStringsHelper(len, low, high, zero, one, dp, MOD);
    }

    public static int countGoodStringsHelper(int len, int low, int high, int zero, int one, int[] dp, int mOD) {
        if (len > high)
            return 0;

        if (dp[len] != -1)
            return dp[len];
        int res = 0;
        if (len >= low && len <= high) {
            res = 1;
            int left = countGoodStringsHelper(len + zero, low, high, zero, one, dp, mOD);
            int right = countGoodStringsHelper(len + one, low, high, zero, one, dp, mOD);
            res = (res + left + right) % mOD;
        }

        return dp[len] = 1 + res % mOD;
    }

    public static int helper2(int idx, int[] days, Map<Integer, Integer> mp, int n, int[] dp) {
        if (idx >= n)
            return 0;
        if (dp[idx] != -1)
            return dp[idx];
        int res = Integer.MAX_VALUE;
        for (Map.Entry<Integer, Integer> hmap : mp.entrySet()) {
            int j = idx;
            int duration = hmap.getKey();
            int cost = hmap.getValue();
            while (j < n && days[j] < days[idx] + duration) {
                j += 1;
            }
            res = Math.min(res, cost + helper2(j, days, mp, n, dp));
        }

        return dp[idx] = res;
    }

    public static int mincostTickets(int[] days, int[] costs) {
        Map<Integer, Integer> mp = new HashMap<>();
        int n = days.length;
        int[] dp = new int[n + 1];
        Arrays.fill(dp, -1);
        mp.put(1, costs[0]);
        mp.put(7, costs[1]);
        mp.put(30, costs[2]);
        return helper2(0, days, mp, n, dp);
    }

    public static int[] vowelStrings(String[] words, int[][] queries) {
        Set<Character> st = new HashSet<>();
        st.add('a');
        st.add('e');
        st.add('i');
        st.add('o');
        st.add('u');
        int n = words.length;
        int[] res = new int[queries.length];
        int[] prefix = new int[n];
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            String curr = words[i];
            int len = curr.length();
            if (st.contains(curr.charAt(0)) && st.contains(curr.charAt(len - 1))) {
                cnt += 1;
            }
            prefix[i] = cnt;
        }

        for (int i = 0; i < queries.length; i++) {
            int left = queries[i][0];
            int right = queries[i][1];

            if (left == 0) {
                res[i] = prefix[right];
            } else {
                int val = prefix[right] - prefix[left - 1];
                res[i] = val;
            }
        }

        for (int p : res) {
            System.out.println(p);
        }

        return res;
    }

    public static boolean existHelper(int row, int col, int idx, String word, char[][] board, int m, int n,
            boolean[][] visited) {
        if (idx == word.length())
            return true;

        if (row < 0 || row >= m || col < 0 || col >= n || visited[row][col] || word.charAt(idx) != board[row][col]) {
            return false;
        }
        visited[row][col] = true;
        boolean res = false;
        res = res || existHelper(row - 1, col, idx + 1, word, board, m, n, visited);
        res = res || existHelper(row + 1, col, idx + 1, word, board, m, n, visited);
        res = res || existHelper(row, col - 1, idx + 1, word, board, m, n, visited);
        res = res || existHelper(row, col + 1, idx + 1, word, board, m, n, visited);

        visited[row][col] = false;
        return res;
    }

    public static boolean exist(char[][] board, String word) {
        if (word.length() == 0)
            return true;
        int m = board.length;
        int n = board[0].length;
        boolean[][] visited = new boolean[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(visited[i], false);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (existHelper(i, j, 0, word, board, m, n, visited))
                    return true;

            }
        }

        return false;
    }

    public static int minimumDeleteSumHelper(int idx1, int idx2, String s1, String s2, int[][] dp) {
        if (idx1 == s1.length() && idx2 == s2.length()) {
            return 0;
        }

        if (idx1 == s1.length() && idx2 != s2.length()) {
            return (int) s2.charAt(idx2) + minimumDeleteSumHelper(idx1, idx2 + 1, s1, s2, dp);
        }

        if (idx2 == s2.length() && idx1 != s1.length()) {
            return (int) s1.charAt(idx1) + minimumDeleteSumHelper(idx1 + 1, idx2, s1, s2, dp);
        }

        if (s1.charAt(idx1) == s2.charAt(idx2)) {
            return 0 + minimumDeleteSumHelper(idx1 + 1, idx2 + 1, s1, s2, dp);
        }

        if (dp[idx1][idx2] != -1) {
            return dp[idx1][idx2];
        }

        int first_deletion = (int) s1.charAt(idx1) + minimumDeleteSumHelper(idx1 + 1, idx2, s1, s2, dp);
        int second_deletion = (int) s2.charAt(idx2) + minimumDeleteSumHelper(idx1, idx2 + 1, s1, s2, dp);

        return dp[idx1][idx2] = Math.min(first_deletion, second_deletion);
    }

    public static int minimumDeleteSum(String s1, String s2) {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m][n];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }
        return minimumDeleteSumHelper(0, 0, s1, s2, dp);
    }

    public static int[] minOperations(String boxes) {
        int n = boxes.length();
        int[] res = new int[n];
        
        for(int i=0; i<n; i++) {
            int moves = 0;
            for(int j=0; j<n; j++) {
                if(i != j && boxes.charAt(j) == '1') {
                    moves += Math.abs(i-j);
                }
            }
            res[i] = moves;
        }
        
        return res;
    }

    public static int findTarget(int[] nums, int target) {
        int idx = -1;
        int left = 0;
        int right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) return mid;
            else if(target < nums[mid]) {
                idx = mid;
                right = mid-1;
            }
            else if (target > nums[mid]) {
                left = mid + 1;
            }
        }
        return idx == -1 ? nums.length : idx;
    }

    public static void main(String[] args) {
        System.out.println("Hello, World!");
        // int res = findTargetSumWays(new int[] { 1, 1, 1, 1, 1 }, 3);
        // System.out.println(res);
        // System.out.println(maxScoreSightseeingPair(new int[] { 8, 1, 5, 2, 6 }));
        // String[] words = { "aba", "bcb", "ece", "aa", "e" };
        // int[][] queries = new int[][] { { 0, 2 }, { 1, 4 }, { 1, 1 } };
        // vowelStrings(words, queries);
//        String s1 = "delete";
//        String s2 = "leet";
//        System.out.println(minimumDeleteSum(s1, s2));
//        int length = 5;
//        int[][] updates = new int[][] { { 1, 3, 2 }, { 2, 4, 3 }, { 0, 2, -2 } };
//        diffArrayTechnique(length, updates);
//        System.out.println(findTarget(new int[]{1,3,5,6}, 0));
//        removeDuplicates("pbbcggttciiippooaais", 2);
        deleteAndEarn(new int[]{2,2,3,3,3,4});
    }

    // Important difference array technique
    public static int[] diffArrayTechnique(int length, int[][] arr) {
        int[] res = new int[length];

        for (int i = 0; i < arr.length; i++) {
            int start = arr[i][0];
            int end = arr[i][1];
            int val = arr[i][2];

            res[start] += val;
            if (end + 1 < length) {
                res[end + 1] -= val;
            }
        }
        int cumulativeSum = 0;
        for (int i = 0; i < res.length; i++) {
            cumulativeSum += res[i];
            res[i] = cumulativeSum;
        }
        for (int r : res) {
            System.out.println(r);
        }
        return res;
    }

    public static class Pair {
        public char c;
        public int cnt;

        Pair(char curr, int cont) {
            this.c = curr;
            this.cnt = cont;
        }

    }

    public static String removeDuplicates(String s, int k) {
        int n = s.length();
        Stack<Pair> st = new Stack<>();
        for (int i = 0; i < n; i++) {
            char curr = s.charAt(i);
            if (st.isEmpty() || st.peek().c != curr) {
//                System.out.println("first exec");
                st.add(new Pair(curr, 1));
            } else if (st.peek().c == curr) {
//                System.out.println("second exe");
                Pair exist = st.pop();
                Pair new_pair = new Pair(exist.c, exist.cnt+1);
//                System.out.println("np " + new_pair.c + " " + new_pair.cnt);
                st.add(new_pair);
                if(new_pair.cnt == k) {
//                    System.out.println("pop executed");
                    st.pop();
                }
            }
        }
        String res = "";
        while (!st.isEmpty()) {
            Pair p = st.pop();
            for(int i=0; i<p.cnt; i++) {
                res = p.c + res;
            }
        }
        System.out.println(res);
        return "";
    }

    public static int minimumLength(String s) {
        if(s.length() == 1 || s.length() == 2) {
            return s.length();
        }
        int n = s.length();
        StringBuilder str = new StringBuilder(s);

        for(int i=1; i<str.length()-1; i++) {
            char curr = str.charAt(i);
            int left = i-1;
            int right = i+1;
            int leftIdx = -1;
            int rightIdx = -1;

            while(left >= 0) {
                if(str.charAt(left) == curr) {
                    leftIdx = left;
                    break;
                }
                left-= 1;
            }

            while(right < str.length()) {
                if (str.charAt(right) == curr) {
                    rightIdx = right;
                }
                right += 1;
            }

            if(leftIdx != -1 && rightIdx != -1) { // found closet leftIdx and rightIdx
                StringBuilder str2 = new StringBuilder(str);
                StringBuilder str3 = new StringBuilder(str);
                str2.deleteCharAt(leftIdx);
                str3.deleteCharAt(rightIdx);
                str = str3;
            }
        }
        System.out.println(str.toString());
        return 0;
    }
    public static boolean isSet(int num,  int bitPos) {
        if ( (num & (1 << bitPos)) != 0) {
            return true;
        }
        return false;
    }

    public static int Set(int num, int bitPos) {
       return num | (1 << bitPos);
    }

    public static int unSet(int num, int bitPos) {
        return num & (~(1 << bitPos));
    }

    public static int minimizeXor(int num1, int num2) {
        int setBits2 = 0;
        int setBits1 = 0;
        int x = num1;

        while (num1 > 0) {
            if ((num1 & 1) == 1) {
                setBits1 += 1;
            }
            num1 = num1 >> 1;
        }

        while (num2 > 0) {
            if ((num2 & 1) == 1) {
                setBits2 += 1;
            }
            num2 = num2 >> 1;
        }
        int bit = 0;
        if(setBits1 < setBits2) {
            while(setBits1 < setBits2) {
                if(!isSet(x, bit)) {
                    x = Set(x, bit);
                    setBits1 += 1;
                }
                bit++;
            }
        } else if (setBits1 > setBits2) {
            while(setBits1 > setBits2 && bit < 32) {
                if(isSet(x, bit)) {
                    x = unSet(x, bit);
                    setBits1 -= 1;
                }
                bit+= 1;
            }
        }

        System.out.println(setBits2);
        System.out.println(setBits1);
        return x;
    }

    public static int deleteAndEarn(int[] nums) {
        int n = nums.length;
        Set<Integer> st = new HashSet<>();
        Map<Integer, Integer> mp = new HashMap<>();
        for(int i : nums) {
            st.add(i);
        }
        for(int i=0; i<nums.length; i++){
            mp.put(nums[i], mp.getOrDefault(nums[i], 0) + 1);
        }
        List<Integer> ls = new ArrayList<>();
        for(int num : st) {
            ls.add(num);
        }
        Collections.sort(ls);
        System.out.println(ls);
        int[] dp = new int[ls.size()];
        dp[0] = ls.get(0) * mp.get(ls.get(0));

        for (int i = 1; i < ls.size(); i++) {
            if (ls.get(i) - 1 == ls.get(i - 1)) {  // last one is not sequence
                int val = ls.get(i) * mp.get(ls.get(i)) + (i - 2 >= 0 ? dp[i - 2] : 0);
                dp[i] = Math.max(val, dp[i - 1]);
            } else { // last one is sequence
                int val = ls.get(i) * mp.get(ls.get(i)) + dp[i-1];
                dp[i] = Math.max(val, dp[i-1]);
            }
        }
        for(int d : dp) {
            System.out.print(d + " ");
        }

        return dp[dp.length-1];
    }

}
