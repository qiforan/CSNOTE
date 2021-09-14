#lang sicp

(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))

(define (simpson-integral f a b n)
  (define h (/ (- b a) n))
  (define (term k)
   (* (f (+ a (* k h))) (if (= (remainder k 2) 1) 4.0 2.0)))
  (* (/ h 3) (sum term 0 inc n)))

(define (cube x) (* x x x))

(simpson-integral cube 0 1 100)
(simpson-integral cube 0 1 1000)
(simpson-integral cube 0 1 10000)
