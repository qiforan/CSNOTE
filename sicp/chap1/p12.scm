#lang sicp

;implement pascal's triangle with recursion

(define (pascal_triangle i j) 
  (if (or (= j 1) (= j i))
      1
      (+ (pascal_triangle (- i 1) (- j 1)) (pascal_triangle (- i 1) j))))

(pascal_triangle 3 2)