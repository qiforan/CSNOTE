const add = (x, y) => { return x + y; };

const add2 = add.bind(null, 2);

console.log(add2(2));