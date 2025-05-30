# [Diamond V] 단어 퍼즐 - 6300 

[문제 링크](https://www.acmicpc.net/problem/6300) 

### 성능 요약

메모리: 26476 KB, 시간: 156 ms

### 분류

아호-코라식, 자료 구조, 구현, 문자열, 트리, 트라이

### 제출 일자

2025년 5월 31일 23:50:33

### 문제 설명

<p>긴말이 필요없다. 단어 퍼즐을 풀어보자.</p>

<p>직사각형 모양의 격자판에서  각 단어들이 상하, 좌우, 대각선 총 8개의 방향 중 하나로 연속해서 등장하는 위치를 찾아야 한다(문제의 예를 보고 싶다면 원문 또는 예제 입력을 참조하시오).</p>

<p>제일 왼쪽 위 칸의 위치는 (0, 0)이다. 이제 각 단어가 등장하는 시작 위치를 찾고, 어느 방향으로 읽어야 하는지도 구하시오. 각 방향은 북쪽 방향부터 시계방향으로 A~H라고 표기한다.</p>

### 입력 

 <p>첫째 줄에 격자판의 줄 수 L, 열 수 C, 찾아야 할 단어의 개수 W가 주어진다(0 < L, C, W ≤ 1000).</p>

<p>이어서 L개의 줄에 격자판이 주어지며 각 줄은 C글자의 대문자로 이루어져 있다.</p>

<p>이어서 W개의 줄에 찾아야 할 각 단어가 주어지며, 각 단어는 대문자로 이루어져 있다. 주어지는 단어는 반드시 격자판에 존재한다.</p>

### 출력 

 <p>W개의 줄에 거쳐서 각 단어가 등장하는 시작 위치의 줄 번호와 열 번호, 그리고 읽어야 하는 방향을 A~H 사이의 문자 하나로 공백으로 구분지어 출력한다.</p>

<p>단어가 여러 곳에서 등장할 경우,</p>

<ul>
	<li>행 위치가 더 작거나,</li>
	<li>행 위치가 같으면 열 위치가 더 작거나,</li>
	<li>행과 열 위치가 같으면 방향이 작은(A~H까지의 방향이 있다면 A가 가장 작습니다)</li>
</ul>

<p>위치를 출력해야 한다.</p>

