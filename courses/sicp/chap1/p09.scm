#lang sicp

; 两种方法定义两个正整数相加的过程

;第一种
;代换过程
;(+ 4 5)
;(if (= 4 0) 5 (inc (+ (dec 4) 5)))
;(inc (+ 3 5))
;...
;(inc (inc (inc inc(+ 0 5))))
; 这是递归过程
(define (+ a b)
  (if (= a 0)
      b
      (inc (+ (dec a) b))))
;第二种
;(+ 4 5)
;(if (= 4 0) (+ (dec 4) (inc 5)))
;(+ 3 6)
;这是迭代过程
(define (+ a b)
  (if (= a 0)
      b
      (+ (dec a) (inc b))))
