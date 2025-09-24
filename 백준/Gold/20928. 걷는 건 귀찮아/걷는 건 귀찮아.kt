import java.util.*

fun main() = with(System.`in`.bufferedReader()) {
    val (n, m) = readLine().split(' ').map { it.toInt() }
    val position: List<Int> = readLine().split(' ').map { it.toInt() }.toList()
    val distance: List<Int> = readLine().split(' ').map { it.toInt() }.toList()
    
    var dp = IntArray(m + 1) { -1 }
    
    var mx = Math.min(position[0] + distance[0], m)
    for(i in position[0]..mx) {
        dp[i] = 0
    }

    for(i in 1 until n) {
        var next = Math.min(position[i] + distance[i], m)
        if(position[i] <= mx && mx < next) {
            for(j in (mx + 1)..next) {
                dp[j] = dp[position[i]] + 1
            }
            mx = next
        }
    }

    println(dp[m])
}