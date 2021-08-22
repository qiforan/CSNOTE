#lang sicp

(define (cube x) (* x x x))

(define (p x) (display "called!") (newline) (- (* 3 x) (* 4 (cube x))))

(define (sine angle)
  (if (not (> (abs angle) 0.1))
      angle
      (p (sine (/ angle 3.0)))))

(sine 12.15)

;如结果所示，p被使用了5次
;增长阶为对数
