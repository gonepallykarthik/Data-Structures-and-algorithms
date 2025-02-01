package Leetcode;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Graph {
    
    public static boolean isConnected(int src, int des, Map<Integer,List<Integer>> graph, boolean[] visited) {
        if(src == des) {
            return true;
        }

        visited[src] = true;
        for(int neighbor : graph.get(src)) {
            if(visited[neighbor] == false) {
                if (isConnected(neighbor, des, graph, visited)) return true;
            }
        }
        
        return false;
    }

    public static int[] findRedundantConnection(int[][] edges) {
        int[] ans = new int[2];
        int m = edges.length;
        Map<Integer, List<Integer>> con = new HashMap<>();
        boolean[] isMarked = new boolean[m+1];

        for(int i=0; i<=m; i++) {
            con.put(i, new ArrayList<>());
        }
        
        for(int i=0; i<m; i++) {
            int src = edges[i][0];
            int des = edges[i][1];
            
            if(isMarked[src] && isMarked[des]) {
                boolean[] visited = new boolean[m+1];
                if(isConnected(src, des, con, visited)){
                    ans[0] = src;
                    ans[1] = des;
                }
                else {   // if they are not connected indirectly then we need to make connection                    
                    con.get(src).add(des);
                    con.get(des).add(src);
                }
            }

            else {
                con.get(src).add(des);
                con.get(des).add(src);
                isMarked[src] = true;
                isMarked[des] = true;
            }
            
        }
        
        return ans;
    }
    public static void BFS(int row, int col, int[][] grid, boolean[][] visited) {
        
    }

    public static int largestIsland(int[][] grid) {
        int max_island_size = Integer.MIN_VALUE;
        Map<Integer, Integer> mp = new HashMap<>();
        int m = grid.length;
        int n = grid[0].length;
        int u_id = 2;
        boolean[][] visited = new boolean[m][n];
        
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++){
                if(visited[i][j] == false && grid[i][j] == 1) {
                    BFS(i,j, grid, visited)
                }
            }
        }

        return max_island_size;
    }

    public static void main(String[] args) {
        System.out.println("welcome");
        int[][] edges = new int[][] {{1,2},{2,3},{3,4},{1,4},{1,5}};
        findRedundantConnection(edges);
    }
}
