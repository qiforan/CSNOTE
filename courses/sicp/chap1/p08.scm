#lang sicp

;牛顿迭代法求立方根

(define (cuber x)
 (cuber-iter 1.0 x))


(define (cuber-iter guess x)
  (if (good-enough? guess x)
      guess
      (cuber-iter (improve guess x)
                 x)))

(define (good-enough? guess x)
  (< (abs (- (* guess guess guess) x)) 0.0001))

(define (improve guess x)
  (average guess
           (/ (+ (/ x (* guess guess)) (* 2 guess)) 3)))

(define (average x y)
  (/ (+ x y) 2.0))

(cuber 27)