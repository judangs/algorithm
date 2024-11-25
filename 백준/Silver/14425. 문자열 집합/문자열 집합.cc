#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int N, M;
int result = 0;

inline int toIndex(char c) { return c - 'a'; }

struct  TrieNode {

  TrieNode * children[26];
  bool isEnd;

  // default 생성자
  TrieNode() : children(), isEnd(false) {}

  // Insert 할 경우 idx로 문자를 구분, children[next] 객체가 생성되지 않았다면 생성하는 것으로 대체하기!
  void Insert(std::string & word, int idx) {
    if(idx == word.length()) {
      isEnd = true;
    }
    else {
      int next = toIndex(word[idx]);
      if(children[next] == NULL)
        // 여기서 시간 초과?
        children[next] = new TrieNode();
      children[next]->Insert(word, idx + 1);
    }
  }

  // 찾는 경우도 동일. 문자열에 해당하는 idx에 대한 객체가 NULL인지 확인하기.
  // Trie의 find()에는 접두사만 같을 경우 true를 반환하는 것과 단어 전체가 똑같아야 True를 반환하는 케이스
  // 2가지가 존재함. 아래는 전체가 똑같아야 True 반환
  // ex)
  // 1 : appleqks app (True) 접두사가 같을 경우
  // 2 : appleqks app (False) 전체가 똑같은 로직이라면.
  bool find(std::string & word, int depth) {
    
    if(depth == (word.length()) && !isEnd) {
      return false;
    }
    if(depth == (word.length()) && isEnd) {
      return true;
    }
    
    int next = toIndex(word[depth]);
    if(children[next] == NULL) {
      return false;
    }
    return children[next]->find(word, depth + 1);
  }
};


int main() {

  std::ios::sync_with_stdio(false);
  std::cout.tie(NULL);
  std::cin.tie(NULL);

  std::cin >> N >> M;

  TrieNode root = TrieNode();

  std::string s;
  for(int i=0; i<N; i++) {
    std::cin >> s;
    root.Insert(s, 0);
  }
  std::vector<std::string> ans;
  for(int i=0; i<M; i++) {
    std::cin >> s;
    
    if(root.find(s, 0)) {
      ans.push_back(s);
      result++;
    }
  }

  std::cout << result;
  /*
  for(std::string s : ans) {
    std::cout << "correct : " << s << std::endl;
  }
  */
  
}