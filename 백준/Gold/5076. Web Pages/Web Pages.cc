#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

string html;
stack<string> st;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(true) {
        
        getline(cin, html);
        if(html == "#") break;

        int n = html.size();
        if(html.empty()) {
            cout << "legal" << endl;
            continue;
        }

        for(int i=0; i<n; ) {
            if(html[i] == '<') {
                bool space = false;
                string tag = "";
                while(i < n && html[i] != '>') {
                    if(html[i] == ' ') space = true;
                    if(!space) tag += html[i];
                    i++;
                }

                if(tag.back() != '>') tag += '>';
                if(tag.find('/') != string::npos)
                    tag.erase(tag.find('/'), 1);

                if(!st.empty() && st.top() == tag) 
                    st.pop();
                else {
                    if(tag.find("br") != string::npos) continue;
                    st.push(tag);
                }
                
            }

            i++;
        }

        string answer = (st.empty() ? "legal" : "illegal");
        cout << answer << endl;

        while(!st.empty()) st.pop();

    }    

}