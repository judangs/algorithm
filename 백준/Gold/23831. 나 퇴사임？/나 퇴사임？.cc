    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <memory.h>

    #define fastio ios::syn_with_stdio(false); cin.tie(NULL);

    using namespace std;

    int N, A, B;
    struct Type {
        int read;
        int study;
        int rest;
        int relax;
    };
    vector<Type> rooms;
    int dp[101][101][2][101];

    int main() {

        cin >> N;
        cin >> A >> B;
        
        rooms = vector<Type>(N + 1);
        for(int day = 1; day <= N; day++) {
            auto & room = rooms[day];
            cin >> room.read >> room.study >> room.rest >> room.relax;
        }

        memset(dp, -1, sizeof(dp));
        dp[0][0][0][0] = 0;

        for(int day = 0; day < N; day++) {
            for(int relax = 0; relax <= A; relax++) {
                for(int rest = 0; rest < 2; rest++) {
                    for(int etc = 0; etc < N; etc++) {

                        auto & now = dp[day][relax][rest][etc];
                        if(now == -1) continue;
 
                        for(int next = 0; next < 4; next++) {
                            switch (next)
                            {
                            case 0:
                                dp[day + 1][relax][0][etc + 1] = max(dp[day + 1][relax][0][etc + 1], dp[day][relax][rest][etc] + rooms[day + 1].read);
                                break;
                            
                            case 1:
                                dp[day + 1][relax][0][etc + 1] = max(dp[day + 1][relax][0][etc + 1], dp[day][relax][rest][etc] + rooms[day + 1].study);
                                break;

                            case 2:
                                if(rest == 0) {
                                    dp[day + 1][relax][rest + 1][etc] = max(dp[day + 1][relax][rest + 1][etc], dp[day][relax][rest][etc] + rooms[day + 1].rest);    
                                }
                                break;
                            
                            case 3:
                                if(relax < A) {
                                    dp[day + 1][relax + 1][0][etc] = max(dp[day + 1][relax + 1][0][etc], dp[day][relax][rest][etc] + rooms[day + 1].relax);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        int answer = 0;
        for(int relax = 0; relax <= A; relax++) {
            for(int rest = 0; rest < 2; rest++) {
                for(int etc = B; etc <=N; etc++) {
                    answer = max(answer, dp[N][relax][rest][etc]);
                }
            }
        }

        cout << answer << endl;
        

    }