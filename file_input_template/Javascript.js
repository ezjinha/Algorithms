const fs = require('fs');

// read contents of the file
const data = fs.readFileSync('input.txt', 'UTF-8');

// split the contents by new line
const lines = data.split(/\r?\n/);

// print all lines
lines.forEach((line) => {
    // If line is able to be casted, cast it to int
    line = isNaN(line) ? line : parseInt(line);
    console.log(typeof line);
});

/* If using try-catch,
try {
    // Put above codes
} catch (err) {
    console.log(err);
}
*/