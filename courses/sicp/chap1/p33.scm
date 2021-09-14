#lang sicp

(define (filter-accumulate combiner null-value predicate term a next b)
  (if (> a b)
      null-value
      (* (if (predicate a) 
             (term a) 
             null-value) 
         (filter-accumulate combiner null-value predicate term (next a) next b))))
