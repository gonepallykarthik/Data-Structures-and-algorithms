package Leetcode;

// leetcode problem No 362 premium problem

import java.util.ArrayDeque;
import java.util.Deque;

public class HitCounter {

    private Deque<Integer> de;

    public HitCounter() {
        this.de = new ArrayDeque<>();
    }

    public void hit(int timestamp) {
        de.add(timestamp);
    }

    public int getHits(int timestamp) {
        int t = timestamp - 300;
        if (t < 0) {
            return this.de.size();
        }
        while (!de.isEmpty() && de.peek() <= t) {
            de.pollFirst();
        }
        return de.size();
    }

    public static void main(String[] args) {
        System.out.println("welcome to Hit Counter! ");
        HitCounter ht = new HitCounter();
        ht.hit(1);
        ht.hit(2);
        ht.hit(3);
        System.out.println(ht.getHits(4));
        ht.hit(4);
        System.out.println(ht.getHits(300));
        ht.hit(300);
        System.out.println(ht.getHits(301));
    }

}
