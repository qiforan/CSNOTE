#lang sicp

; 牛顿迭代法求平方根
; new-if
; new-if is a function. 
; When a function is called, what's the first thing that Scheme does with the argument list? 
; It evaluates all the arguments.

(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
        (else else-clause)))

(define (good-enough? guess x)
  (< (abs (- (* guess guess) x)) 0.0001))

(define (average x y)
  (/ (+ x y) 2.0))

(define (improve guess x)
  (average guess
           (/ x guess)))

(define (sqrt-iter guess x)
  (new-if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))

(define (sqrt x)
  (sqrt-iter 1.0 x))

(sqrt 3)