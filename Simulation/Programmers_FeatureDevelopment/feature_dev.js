function solution(progresses, speeds) {
    var answer = [];

    while (progresses.length) {
        let count = 0;
        
        for (let i = 0; i < progresses.length; i++) {
            progresses[i] = progresses[i] + speeds[i];
        }

        while (progresses[0] >= 100) {
            count += 1;
            progresses.shift();
            speeds.shift();
        }

        count != 0 ? answer.push(count) : answer;
    }

    return answer;
}

answer = 
    // solution([93, 30, 55], [1, 30, 5]);  // [2, 1]
    solution([95, 90, 99, 99, 80, 99], [1, 1, 1, 1, 1, 1]);  // [1, 3, 2]
;
console.log(answer);