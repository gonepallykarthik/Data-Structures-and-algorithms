package Leetcode;

import java.util.HashMap;
import java.util.Map;

class Pair {
    String val;
    int timestamp;

    public Pair(String val, int time) {
        this.val = val;
        this.timestamp = time;
    }
}


public class TimeMap {
    private Map<String, Pair> mp;

    public TimeMap() {
        this.mp = new HashMap<>();
    }

    public void set(String key, String value, int timestamp) {
        mp.put(key, new Pair(value, timestamp));
    }

    public String get(String key, int timestamp) {
        if (!mp.containsKey(key)) return null;
        return mp.get(key).val;
    }

    public static void main(String[] args) {
        TimeMap tm = new TimeMap();
        tm.set("foo", "bar", 1);
        System.out.println(tm.get("foo", 1));
        System.out.println(tm.get("foo", 3));
        tm.set("foo", "bar2", 4);
        System.out.println(tm.get("foo", 4));
        System.out.println(tm.get("foo", 5));
    }
}
