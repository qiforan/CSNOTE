#lang sicp

(define (accmulate combiner null-value term a next b)
  (if (> a b)
      null-value
      (accmulate combiner (+ null-value (term a)) term (next a) next b)))

(define (sum term a next b)
  (accmulate + 0 term a next b))

;; test

(define (sum-cubes a b)
  (sum (lambda (x) (* x x x)) a inc b))

(sum-cubes 1 2)