    #include <iostream>
    #include <vector>
    #include <queue>
    #include <functional>

    #define fastio ios::sync_with_stdio(false); cin.tie(NULL);

    using namespace std;

    int N, P, A;
    vector<int> bot;
    priority_queue<int, vector<int>, greater<int>> pq;

    int main() {

        fastio;

        cin >> N >> P;
        bot = vector<int>(N + 1, 0);
        for(int i = 1; i <= N; i++) cin >> bot[i];

        vector<int> answer(N + 1, 0);
        long long sum = 0ll;
        for(int i = 1; i <= N; i++) {
            pq.push(bot[i]);
            sum += bot[i];
            
            if(sum < P) answer[i] = -1;
            else {
                while(!pq.empty() && P <= sum - pq.top()) {
                    sum -= pq.top();
                    pq.pop();
                }

                answer[i] = pq.size();
            }
        }

        for(int i = 1; i <= N; i++)
            cout << answer[i] << ' ';
        cout << endl;


}