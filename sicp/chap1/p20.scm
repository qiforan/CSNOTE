#lang sicp

(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (my-remainder a b))))

(define (my-remainder a b)
  (display "called ")
  (display (remainder a b))
  (newline)
  (remainder a b))

(gcd 206 40)

; 正则序代换
; (gcd 206 40) -> (if (= 40 0) 40 (gcd 40 (remainder 206 40)))
; = (gcd 40 6) -> (if (= 6 0) 6 (gcd 6 (remainder 40 6)))
; = (gcd 6 4) -> (if (= 4 0) 4 (gcd 4 (remainder 6 4)))
; = (gcd 4 2) -> (if (= 2 0) 2 (gcd 2 remainder 4 2))
; 