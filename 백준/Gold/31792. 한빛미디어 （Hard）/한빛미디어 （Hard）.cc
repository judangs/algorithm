#include <iostream>
#include <map>

using namespace std;

int Q, S;
map<int, int> book;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> Q;
    while(Q--) {

        int opt; cin >> opt;
        switch (opt)
        {
        case 1:
            cin >> S;
            book[S]++;
            break;
        case 2:
            cin >> S;
            if(book.find(S) != book.end()) {
                book[S]--;
                if(book[S] == 0)
                    book.erase(S);
            }
            break;
        case 3:
            int answer = 0; auto iter = book.begin();
            while(iter != book.end()) {
                answer++;
                iter = book.upper_bound(2 * iter->first - 1);
            }


            cout << answer << "\n";
            break;                        
        }

    }
}