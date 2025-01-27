package Leetcode;

import java.util.*;

public class Dota {

    public static int[][] highestPeak(int[][] isWater) {
        int m = isWater.length;
        int n = isWater[0].length;
        int[][] res = new int[m][n];
        for (int i = 0; i < res.length; i++) {
            Arrays.fill(res[i], -1);
        }
        Queue<int[]> pq = new LinkedList<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isWater[i][j] == 1) {
                    pq.add(new int[] { i, j });
                    res[i][j] = 0;
                }
            }
        }

        while (!pq.isEmpty()) {
            int[] topEle = pq.poll();
            int row = topEle[0];
            int col = topEle[1];
            int[][] directions = new int[][] { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
            for (int[] dir : directions) {
                int new_row = row + dir[0];
                int new_col = col + dir[1];
                if (new_row >= 0 && new_row < m && new_col >= 0 && new_col < n && res[new_row][new_col] == -1) {
                    res[new_row][new_col] = 1 + res[row][col];
                    pq.add(new int[] { new_row, new_col });
                }
            }
        }

        return res;
    }

    public static int trapRainWater(int[][] heightMap) {
        int waterTrap = 0;
        int m = heightMap.length;
        int n = heightMap[0].length;
        boolean[][] visited = new boolean[m][n];

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        for (int row = 0; row < m; row++) {
            visited[row][0] = true;
            pq.add(new int[] { heightMap[row][0], row, 0 });
        }

        for (int col = 1; col < n; col++) {
            visited[0][col] = true;
            pq.add(new int[] { heightMap[0][col], 0, col });
        }

        for (int row = 1; row < m; row++) {
            visited[row][n - 1] = true;
            pq.add(new int[] { heightMap[row][n - 1], row, n - 1 });
        }

        for (int col = n - 2; col >= 1; col--) {
            visited[m - 1][col] = true;
            pq.add(new int[] { heightMap[m - 1][col], m - 1, col });
        }

        while (!pq.isEmpty()) {
            int[] topEle = pq.poll();
            int height = topEle[0];
            int row = topEle[1];
            int col = topEle[2];

            int[][] directions = new int[][] { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };

            for (int[] dir : directions) {
                int new_row = row + dir[0];
                int new_col = col + dir[1];
                if (new_row >= 0 && new_row < m && new_col >= 0 && new_col < n && !visited[new_row][new_col]) {
                    visited[new_row][new_col] = true;
                    int trap = heightMap[row][col] - heightMap[new_row][new_col];
                    waterTrap += Math.max(trap, 0);
                    pq.add(new int[] { Math.max(heightMap[row][col], heightMap[new_row][new_col]), new_row, new_col });
                }
            }
        }

        return waterTrap;
    }

    public int firstCompleteIndex(int[] arr, int[][] mat) {
        int m = mat.length;
        int n = mat[0].length;
        Map<Integer, Integer> rowMap = new HashMap<>();
        Map<Integer, Integer> colMap = new HashMap<>();
        Map<Integer, int[]> coordinates = new HashMap<>();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                coordinates.put(mat[i][j], new int[] { i, j });
            }
        }

        for (int i = 0; i < arr.length; i++) {
            int[] r = coordinates.get(arr[i]);
            int row = r[0];
            int col = r[1];
            rowMap.put(row, rowMap.getOrDefault(row, 0) + 1);
            colMap.put(col, colMap.getOrDefault(col, 0) + 1);

            if (rowMap.get(row) == n) {
                return i;
            }

            if (colMap.get(col) == m) {
                return i;
            }
        }

        return -1;
    }

    public static long f(int row, int col, int[][] grid, int m, int n) {
        if (row == 0 && col == 0) {
            return (long) grid[row][col];
        }

        if (row < 0 || row >= m || col < 0 || col >= n) {
            return Long.MIN_VALUE;
        }

        long left = grid[row][col] + f(row, col - 1, grid, m, n);
        long up = grid[row][col] + f(row - 1, col, grid, m, n);

        return Math.max(left, up);
    }

    public static long gridGame(int[][] grid) {
        long res = 0;
        int m = grid.length;
        int n = grid[0].length;
        long ans = f(m - 1, n - 1, grid, m, n);
        return ans;
    }

    public static int countServers(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        Map<Integer, Integer> rowMap = new HashMap<>();
        Map<Integer, Integer> colMap = new HashMap<>();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    rowMap.put(i, rowMap.getOrDefault(i, 0) + 1);
                    colMap.put(j, colMap.getOrDefault(j, 0) + 1);
                }

            }
        }
        int servercnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (rowMap.get(i) > 1) {
                        servercnt += 1;
                    } else if (colMap.get(j) > 1) {
                        servercnt += 1;
                    }
                }
            }
        }

        return servercnt;
    }

    public static int[] lexicographicallySmallestArray(int[] nums, int limit) {
        Set<String> st = new LinkedHashSet<>();
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            StringBuilder strBuilder = new StringBuilder();
            strBuilder.append(String.valueOf(i));
            strBuilder.append(String.valueOf(nums[i]));
            st.add(strBuilder.toString());
        }

        for (int i = 0; i < n; i++) {
            int currVal = nums[i];
            int sub = 1;

        }
        return nums;
    }

    public static int[] createTargetArray(int[] nums, int[] index) {
        List<Integer> ls = new ArrayList<>();
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            ls.add(index[i], num);
            System.out.println(ls);
        }
        System.out.println(ls);
        int[] res = new int[ls.size()];
        for (int i = 0; i < ls.size(); i++) {
            res[i] = ls.get(i);
        }
        return res;
    }



    public static void main(String[] args) {
        // System.out.println("welcome");
        // int[][] grid = { {1, 0},{1,1} };
        // System.out.println(gridGame(grid));
        // int[] bills = new int[]{5,5,10,10,20};
        // List<Integer> ls = new ArrayList<>();
        // System.out.println(countServers(grid));
        int[] nums = new int[] { 0, 1, 2, 3, 4 };
        int[] indexes = new int[] { 0, 1, 2, 2, 1 };
        createTargetArray(nums, indexes);
    }
}
