#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;

void _move_block(int dir, vector<vector<int>> & board) {
    stack<pair<int, bool>> st;

    switch (dir) {
        case 0:
            for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                    if(board[i][j] == 0) continue;            
                    if(st.empty()) 
                        st.push({board[i][j], false});
                    else {
                        auto & block = st.top();
                        if(block.first == board[i][j] && !block.second) {
                            st.pop();
                            st.push({2 * board[i][j], true});
                        }
                        else 
                            st.push({board[i][j], false});
                    }
                }

                for(int j=0; j<N; j++) board[i][j] = 0;
                for(int j=st.size() - 1; !st.empty(); j--) {
                    board[i][j] = st.top().first;
                    st.pop();
                }
            }  
            break;

        case 1:
            for(int i=0; i<N; i++) {
                for(int j=N-1; j>=0; j--) {
                    if(board[i][j] == 0) continue;            
                    if(st.empty()) 
                        st.push({board[i][j], false});
                    else {
                        auto & block = st.top();
                        if(block.first == board[i][j] && !block.second) {
                            st.pop();
                            st.push({2 * board[i][j], true});
                        }
                        else 
                            st.push({board[i][j], false});
                    }
                }

                for(int j=0; j<N; j++) board[i][j] = 0;
                for(int j=N - st.size(); !st.empty(); j++) {
                    board[i][j] = st.top().first;
                    st.pop();
                }
            }  
            break;   

        case 2:
            for(int i=0; i<N; i++) {
                for(int j=N-1; j>=0; j--) {
                    if(board[j][i] == 0) continue;            
                    if(st.empty()) 
                        st.push({board[j][i], false});
                    else {
                        auto & block = st.top();
                        if(block.first == board[j][i] && !block.second) {
                            st.pop();
                            st.push({2 * board[j][i], true});
                        }
                        else 
                            st.push({board[j][i], false});
                    }
                }

                for(int j=0; j<N; j++) board[j][i] = 0;
                for(int j=N - st.size(); !st.empty(); j++) {
                    board[j][i] = st.top().first;
                    st.pop();
                }
            }
            break;

        default:
            for(int i=0; i<N; i++) {
                for(int j=0; j<N; j++) {
                    if(board[j][i] == 0) continue;            
                    if(st.empty()) 
                        st.push({board[j][i], false});
                    else {
                        auto & block = st.top();
                        if(block.first == board[j][i] && !block.second) {
                            st.pop();
                            st.push({2 * board[j][i], true});
                        }
                        else 
                            st.push({board[j][i], false});
                    }
                }

                for(int j=0; j<N; j++) board[j][i] = 0;
                for(int j=st.size() - 1; !st.empty(); j--) {
                    board[j][i] = st.top().first;
                    st.pop();
                }
            }  
            break;
    }
}

int move(int count, vector<vector<int>> & board) {
    if(count == 5) {
        int cost = 0;
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++) cost = max(cost, board[i][j]);

        return cost;
    }

    int ret = 0;
    vector<vector<int>> backup = board;

    for(int dir=0; dir<4; dir++) {
        _move_block(dir, board);
        ret = max(ret, move(count + 1, board));
        board = backup;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> board[i][j];
        }
    }

    int answer = move(0, board);
    cout << answer << endl;
}