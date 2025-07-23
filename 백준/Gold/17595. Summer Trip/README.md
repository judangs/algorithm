# [Gold V] Summer Trip - 17595 

[문제 링크](https://www.acmicpc.net/problem/17595) 

### 성능 요약

메모리: 2268 KB, 시간: 16 ms

### 분류

애드 혹, 문자열

### 제출 일자

2025년 7월 23일 14:42:09

### 문제 설명

<p>Leo has started a job in a travel agency. His first task is to organize a summer trip to an exotic overseas city. During the summer season, events of various types take place in the city: sports matches, concerts, beach parties, and many others. At any given time, there is exactly one event taking place. Events of any particular type may take place more than once during the season. The itinerary of events that Leo offers to his clients cannot be chosen arbitrarily; the company requires them to form a so-called “good itinerary.” A good itinerary is a consecutive sequence of at least two events in the summer season, where the first and last events are of different types, and they are both unique among all event types during the sequence. For example, if the first event in a good itinerary is a beach party, none of the other events during the itinerary can also be a beach party. There are no other restrictions on the event types in the sequence of a good itinerary.</p>

<p>Before he starts organizing the trip, Leo wants to know the total number of good itineraries that are possible given a calendar of events that will take place over the summer season.</p>

### 입력 

 <p>The input consists of one line with a string describing the sequence of event types in the summer season. All characters are lowercase English letters (’<code>a</code>’ – ’<code>z</code>’), with different letters represent different types of events. Character <em>i</em> of the string encodes the <em>i</em>th event of the summer. There are no blanks or spaces in the string.</p>

<p>The length of the input string is at least 2 and at most 100 000 characters.</p>

### 출력 

 <p>Print the number of good itineraries that exist for the given summer season.</p>

