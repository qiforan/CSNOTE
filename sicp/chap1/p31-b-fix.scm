#lang sicp

(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
         (product term (next a) next b))))

(define (pi-approx n)
  (define (pi-term x)
    (if (even? x)
        (/ (+ 2 x) (+ 1 x))
        (/ (+ 1 x) (+ 2 x))))
  (* 4.0 (product pi-term 1 inc n)))

(pi-approx 10000)