#lang sicp

(define (product term a next-a b next-b end)
  (if (end a b)
      1
      (* (term a b)
         (product term (next-a a b) next-a (next-b a b) next-b end))))

(define (pi-approx h)

  (define (term a b)
    (/ a b))

  (define (next-a a b)
    (if (< a b) (+ a 2) a))

  (define (next-b a b)
    (if (> a b) (+ b 2) b))

  (define (end a b)
    (< (abs (- (/ a b) 1)) h))

  (* (product term 2 next-a 3 next-b end) 4.0))

;; test

(pi-approx 0.0001)