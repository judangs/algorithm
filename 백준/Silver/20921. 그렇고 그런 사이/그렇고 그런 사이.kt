import java.io.BufferedReader
import java.util.Collections

fun main() = with(System.`in`.bufferedReader()) {

    val (N, K) = readLine().split(" ").map { it.toInt() }
    var person = Array(N) { it + 1 }.toMutableList()

    var idx = 0
    for(i in 0 until K) {
        while(person[idx] > person[idx + 1]) {
            idx++
            idx = if(idx == N - 1) 0 else idx
        }

        Collections.swap(person, idx, idx + 1)
    }

    println(person.joinToString(separator = " "))


}