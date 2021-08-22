#lang sicp

(define (* a b)
  (define (double x)
    (+ x x))
  (define (halve x)
    (/ x 2))
  (cond ((= b 0) 0)
        ((even? b) (double (* a (halve b))))
        (else (+ a (* a (- b 1))))))

(* 2 2)