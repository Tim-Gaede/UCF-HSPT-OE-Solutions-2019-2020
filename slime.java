import java.util.*;
import java.io.*;

public class slime {
    static class Num {
        long v, lastSplit, cnt;
        public Num(long vv, long ll, long cc) {
            v = vv;  lastSplit = ll;  cnt = cc;
        }
    }
    static class Result {
        long res, split;
        public Result(long rr, long ss) {
            res = rr;  split = ss;
        }
    }
    static Result solveRec(Map<Long, Integer> prios, PriorityQueue<Num> pq, long splits, long maxPrio) {
        long res = 0;
        while(!pq.isEmpty() && prios.get(pq.peek().v) <= maxPrio) {
            Num base = pq.poll();
            long v = base.v;
            List<Num> bestNums = new ArrayList<>();
            bestNums.add(base);
            while(!pq.isEmpty() && pq.peek().v == v) bestNums.add(pq.poll());
            long cnt = 0;
            for(Num a : bestNums) {
                res += (splits - a.lastSplit) * a.v * a.cnt;
                cnt += a.cnt;
            }
            splits++;
            PriorityQueue<Num> nq = new PriorityQueue<>();
            long childRes = 0, childDsplit = 0;
            if(v > 1) {
                long old = splits;
                nq.add(new Num(v / 2, splits - 1, 2));
                Result child = solveRec(prios, nq, splits, prios.get(v));
                for(Num c : nq) child.res += (child.split - c.lastSplit) * c.v * c.cnt;
                childRes = child.res;
                childDsplit = child.split - old;
            }
            res += cnt * childRes;
            res += cnt * (cnt - 1) / 2 * v * (childDsplit + 1);
            splits += (childDsplit + 1) * cnt - 1;
            for(Num c : nq) {
                Num cl = new Num(c.v, splits, c.cnt * cnt);
                res += cnt * (cnt - 1) / 2 * (childDsplit + 1) * c.cnt * c.v;
                pq.add(cl);
            }
        }
        return new Result(res, splits);
    }
    static long solve(List<Long> nums, Map<Long, Integer> prios) {
        Comparator<Num> cmp = new Comparator<Num>() {
            public int compare(Num a, Num b) {
                return Long.compare(prios.get(a.v), prios.get(b.v));
            }
        };
        PriorityQueue<Num> pq = new PriorityQueue<>(cmp);
        for(long x : nums) pq.add(new Num(x, 0, 1));
        return solveRec(prios, pq, 0, Long.MAX_VALUE).res;
    }
    static long solve(long x) {
        List<Long> vals = new ArrayList<>();
        long tmp = x;
        while(tmp > 0) {
            vals.add(tmp);
            tmp /= 2;
        }
        Collections.reverse(vals);
        int ptr = 0;
        List<Long> ord = new ArrayList<>();
        for(long v : vals) {
            long best = Long.MAX_VALUE;
            List<Long> bestList = new ArrayList<>();
            if(v % 2 == 1) ord.add(ptr++, v);
            else {
                for(int i = 0 ; i <= ord.size() ; i++) {
                    List<Long> clone = new ArrayList<>(ord);
                    clone.add(i, v);
                    Map<Long, Integer> map = new HashMap<>();
                    for(int j = 0 ; j < clone.size() ; j++)
                        map.put(clone.get(j), j);
                    long score = solve(clone, map);
                    if(score < best) {
                        best = score;
                        bestList = clone;
                    }
                }
                ord = bestList;
            }
        }
        Map<Long, Integer> map = new HashMap<>();
        for(int i = 0 ; i < ord.size() ; i++)
            map.put(ord.get(i), i);
        List<Long> list = new ArrayList<>();
        list.add(x);
        return solve(list, map);
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int t = scan.nextInt();
        for(int tt = 1 ; tt <= t ; tt++) {
            int h = scan.nextInt();
            long res = solve(h);
            System.out.printf("Fight #%d: %d%n", tt, res);
        }
    }
}