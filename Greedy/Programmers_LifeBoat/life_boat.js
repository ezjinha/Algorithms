function solution(people, limit) {
    var answer = 0;
    people.sort((a, b) => { return b - a; });
    let l = 0;
    let r = people.length - 1;
    
    while (l < r) {
        let total_weight = people[l] + people[r];
        if (total_weight > limit) {
            l++;
        }
        else {
            l++;
            r--;
        }
        answer++;
    }
    if (l == r) answer++;

    return answer;
}

answer =
    // solution([70, 50, 80, 50], 100) // 3
    solution([70, 80, 50], 100)     // 3
    // solution([10, 10, 10, 10, 10], 50)     // 3
    // solution([40, 50, 60, 90], 100)     // 3
;
console.log(answer);