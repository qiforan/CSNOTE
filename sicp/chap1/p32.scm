#lang sicp

(define (accmulate combiner null-value term a next b)
  (if (> a b)
      null-value
      (combiner (term a) 
                (accmulate combiner null-value term (next a) next b))))

;; sum

(define (sum term a next b)
  (accmulate + 0 term a next b))

;; product

(define (product term a next b)
  (accmulate * 1 term a next b))