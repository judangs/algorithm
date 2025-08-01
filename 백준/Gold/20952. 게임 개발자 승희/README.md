# [Gold III] 게임 개발자 승희 - 20952 

[문제 링크](https://www.acmicpc.net/problem/20952) 

### 성능 요약

메모리: 9104 KB, 시간: 44 ms

### 분류

수학, 구현

### 제출 일자

2025년 7월 30일 16:09:19

### 문제 설명

<p>승희는 최근 369 게임에 푹 빠졌다. 369 게임을 하던 승희는 놀라 자빠질 수밖에 없었다. 369 게임을 잘하는 자기 자신이 너무 대견하였기 때문이다. 369 게임이 식상해진 승희는 369 게임을 변형한 71421 게임을 개발하였다. 369 게임에서는 3, 6, 9가 들어가는 수에 손뼉을 치지만, 71421 게임에서는 7의 배수에 손뼉을 친다. 승희는 71421 게임을 널리 퍼트리기로 결심하였다.</p>

<p>71421 게임은 최근 대학생들 사이에서 큰 인기를 끌고 있다. 369 게임에 이어 71421 게임도 식상해진 승희는 수열을 이용한 새로운 게임을 개발하였다.</p>

<p>승희의 수열 게임은 혼자서 즐길 수 있는 재미난 게임이다. 시작하기에 앞서 길이가 N인 수열 A와 길이가 M인 수열 B를 준비한다. 이후 수열 A에 대하여 M번의 연산을 수행한다. i(1 ≤ i ≤ M)번째 연산은 수열 A의 모든 원소에 B<sub>i</sub>를 더한 후 7의 배수인 원소들을 제거하는 연산이다. 단, 연산을 수행한 결과 수열 A의 모든 원소가 제거된다면 해당 연산은 수행하지 않는다.</p>

<p>수열 A와 B가 주어졌을 때, M번의 연산을 수행한 결과를 구하는 프로그램을 작성하시오.</p>

### 입력 

 <p>첫 번째 줄에 수열 A의 길이 N과 수열 B의 길이 M이 주어진다.</p>

<p>두 번째 줄에 N개의 정수 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>N</sub>이 주어진다.</p>

<p>세 번째 줄에 M개의 정수 B<sub>1</sub>, B<sub>2</sub>, ..., B<sub>M</sub>이 주어진다.</p>

<p>모든 입력은 공백으로 구분되어 주어진다.</p>

### 출력 

 <p>첫 번째 줄에 M번의 연산을 수행한 후 수열 A의 길이 K를 출력한다.</p>

<p>두 번째 줄에 K개의 정수 A<sub>1</sub>, A<sub>2</sub>, ..., A<sub>K</sub>를 공백으로 구분하여 출력한다. 답이 매우 커질 수 있으므로 10<sup>9</sup> + 7로 나눈 나머지를 출력한다.</p>

