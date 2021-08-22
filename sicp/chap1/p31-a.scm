#lang sicp

(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
         (product term (next a) next b))))

(define (factorial n)
  (define (term x)
    x)
  (product term 1 inc n))

;; test 

(factorial 3)