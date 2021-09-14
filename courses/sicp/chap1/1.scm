#lang sicp

; 牛顿迭代法求平方根

(define (good-enough? guess x)
  (< (abs (- (* guess guess) x)) 0.0001))

(define (average x y)
  (/ (+ x y) 2.0))

(define (improve guess x)
  (average guess
           (/ x guess)))
           
(define (sqrt x)
  (sqrt-iter 1.0 x))

(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))


(sqrt 1e10)