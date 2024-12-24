package Leetcode;

import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.List;
import java.util.ArrayList;

public class Main {

    public static int minimumOperationsToMakeArraySorted(List<Integer> arr) {
        if(arr.size() == 1) return 0;
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
        
        while(!q.isEmpty()) {
            int n = q.size();
            List<Integer> level = new ArrayList<>();
            for(int i=0; i<n; i++) {
                TreeNode node = q.poll();
                level.add(node.val);
                
                if(node.left != null) q.add(node.left);
                if(node.right != null) q.add(node.right);
            }
            System.out.println(level);
            cnt += minimumOperationsToMakeArraySorted(level);
        }

        return cnt;
    }

    public static void main(String[] args) {
        List<Integer> arr = new ArrayList<>(Arrays.asList(7,6,8,5));
        int res = minimumOperationsToMakeArraySorted(arr);
        System.out.println(res);
        System.out.println("Hello, World!");
    }
}
