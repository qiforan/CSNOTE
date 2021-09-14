#lang sicp
;费马法检查素数

(define (square x)
  (* x x))

;fast calculate (base^exp) mod(m)
(define (expmod base exp m)
  (cond ((= exp 0) 0)
        ((even? exp) (remainder (square (expmod base (/ exp 2) m))
                               m))
        (else (remainder (* base (expmod base (- exp 1) m ))
                         m))))

(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))

(fast-prime? 100 3)