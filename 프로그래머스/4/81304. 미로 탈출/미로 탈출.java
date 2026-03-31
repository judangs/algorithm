import java.util.*;

class Solution {

    static class Edge {
        int to;
        int cost;
        boolean forward;

        Edge(int to, int cost, boolean forward) {
            this.to = to;
            this.cost = cost;
            this.forward = forward;
        }
    }

    static class State implements Comparable<State> {
        int node;
        int dist;
        int visit;

        State(int node, int dist, int visit) {
            this.node = node;
            this.dist = dist;
            this.visit = visit;
        }

        @Override
        public int compareTo(State o) {
            return Integer.compare(this.dist, o.dist);
        }
    }

    List<Edge>[] graph;
    int[] trapIndex;
    boolean[] isTrap;

    public int solution(int n, int start, int end, int[][] roads, int[] traps) {
        graph = new ArrayList[n + 1];
        for (int i = 1; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] road : roads) {
            int u = road[0];
            int v = road[1];
            int w = road[2];

            graph[u].add(new Edge(v, w, true));
            graph[v].add(new Edge(u, w, false));
        }

        trapIndex = new int[n + 1];
        Arrays.fill(trapIndex, -1);

        isTrap = new boolean[n + 1];
        for (int i = 0; i < traps.length; i++) {
            trapIndex[traps[i]] = i;
            isTrap[traps[i]] = true;
        }

        int maxState = 1 << traps.length;
        int[][] dist = new int[n + 1][maxState];
        for (int i = 1; i <= n; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }

        PriorityQueue<State> pq = new PriorityQueue<>();
        dist[start][0] = 0;
        pq.offer(new State(start, 0, 0));

        while (!pq.isEmpty()) {
            State cur = pq.poll();

            if (cur.dist > dist[cur.node][cur.visit]) continue;
            if (cur.node == end) return cur.dist;

            boolean curActive = isActive(cur.node, cur.visit);

            for (Edge edge : graph[cur.node]) {
                int next = edge.to;
                boolean nextActive = isActive(next, cur.visit);

                boolean reversed = curActive ^ nextActive;

                if (edge.forward == reversed) continue;

                int nextVisit = cur.visit;
                if (isTrap[next]) {
                    nextVisit ^= (1 << trapIndex[next]);
                }

                int nextDist = cur.dist + edge.cost;
                if (nextDist < dist[next][nextVisit]) {
                    dist[next][nextVisit] = nextDist;
                    pq.offer(new State(next, nextDist, nextVisit));
                }
            }
        }

        return -1;
    }

    boolean isActive(int node, int visit) {
        if (!isTrap[node]) return false;
        return (visit & (1 << trapIndex[node])) != 0;
    }
}