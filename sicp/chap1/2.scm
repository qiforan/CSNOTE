#lang sicp
; O(sqr(N))法判断一个数为素数
; 即遍历2-sqrt(N)

(define (smallest_divisor n)
  (find-divisor n 2))

(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n) ;没有素因子
        ((divides? test-divisor n) test-divisor)
        (else (find-divisor n (+ 1 test-divisor)))))

(define (divides? a b)
  (= (remainder b a) 0))

(define (prime? n)
  (= n (smallest_divisor n))) ;最小素因子为本身

(define (square n)
  (* n n))

(prime? 19)