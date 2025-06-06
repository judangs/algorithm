# [Diamond IV] 백업 - 1150 

[문제 링크](https://www.acmicpc.net/problem/1150) 

### 성능 요약

메모리: 6288 KB, 시간: 32 ms

### 분류

자료 구조, 그리디 알고리즘, 우선순위 큐

### 제출 일자

2025년 6월 2일 22:47:43

### 문제 설명

<p>당신은 큰 회사들의 컴퓨터 자료를 백업하여주는 정보통신회사를 운영한다. 자료 백업이 즐거운 일이 아니므로, 당신은 서로 다른 두 회사의 자료를 서로 백업하여 주는 시스템을 개발하여 당신이 집에서 게임을 즐기는 동안 백업이 이루어지게 하려 한다.</p>

<p>모든 회사들은 직선인 길을 따라 위치하고 있다. 당신은 서로 백업을 하여 줄 두 회사를 짝 지어 주어야 하는데, 두 회사 사이에 네트워크 케이블을 연결 사용하여야 한다.</p>

<p>네트워크 케이블은 대단히 비쌀 뿐 아니라, 지역 통신 회사에서는 당신에게 오직 k개의 네트워크 케이블을 제공한다 –이 말은 당신이 오직 k 쌍의 회사에만 백업을 할 수 있다는 뜻이다 (전체 2k 개의 회사). 어떤 회사도 두 개 이상의 쌍에 속할 수는 없다 (즉, 여기 2k 개의 회사가 모두 다른 회사라는 것을 뜻한다).</p>

<p>통신 회사는 네트워크 케이블의 길이를 km 단위로 경비를 부과한다. 따라서 당신은 가장 짧은 길이의 케이블을 사용하도록 회사들을 k 쌍으로 짝지어야 한다. 다시 말하자면, 회사들을 짝짓기 하는데, 짝지어진 두 회사간의 거리들의 전체 합을 최소화 하도록 짝을 지어야 한다는 것이다.</p>

<p>예를 들어, 아래 그림과 같이 다섯 개의 고객회사들이 같은 길 위에 위치한다고 하자. 이 회사들은 각각 길의 출발점에서 기준하여 1 km, 3 km, 4 km, 6 km 그리고 12 km 에 위치하고 있다. 통신회사에서는 오직 k = 2 케이블만을 제공한다.</p>

<p><img alt="" src="https://www.acmicpc.net/upload/images/backup.png" style="height:191px; width:539px"></p>

<p>예에서 최선의 짝 짓기 방법은 첫 번째와 두 번째 회사, 그리고 세 번째와 네 번째 회사를 묶어 주는 것이다. k = 2 케이블 만을 사용하게 되며, 첫 번째 케이블의 길이는 3 km –1 km = 2 km 이고, 두 번째 케이블의 길이는 6 km –4 km = 2 km 이다. 이와 같은 짝짓기는 전체 4 km 의 네트워크 케이블을 사용하게 되며, 실제 가능한 가장 짧은 경우이다.</p>

### 입력 

 <p>입력의 첫 번째 줄에는 정수 n 과 k 가 주어지는데, 각각 길 위의 회사 수(2 ≤ n≤ 100 000), 그리고 제공되는 네트워크 케이블 수(1 ≤ k ≤ ½ n)를 의미한다. 그 다음 n 줄에는 각각 하나의 정수 s (0 ≤ s ≤ 1 000 000 000) 가 주어지며, 이 정수는 길의 출발점에서 각 회사까지의 거리를 의미한다. 이 정수들은 가장 작은 것에서 가장 큰 것 까지 순서대로 나타난다. 어떤 두 개의 회사도 같은 지점에 있지 않다.</p>

### 출력 

 <p>출력은 반드시 하나의 양의 정수로 표현되어야 하는데, 이것은 2k 의 서로 다른 회사를 k 쌍으로 묶었을 때 필요한 가장 짧은 전체 네트워크 케이블의 길이이다.</p>

