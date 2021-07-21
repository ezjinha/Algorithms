function solution(array, commands) {
    var answer = [];

    commands.forEach(command => {
        let i = command[0] - 1;
        let j = command[1];
        let k = command[2] - 1;

        let new_array = array.slice(i, j);
        new_array.sort((a, b) => {return a - b;});
        answer.push(new_array[k]);
    });

    return answer;
}

answer =
    solution([1, 5, 2, 6, 3, 7, 4], [[2, 5, 3], [4, 4, 1], [1, 7, 3]])  // [5, 6, 3]
;
console.log(answer);