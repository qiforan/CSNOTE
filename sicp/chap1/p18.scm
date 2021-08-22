#lang sicp

(define (* a b)
  (define (double x)
    (+ x x))
  (define (halve x)
    (/ x 2))
  (define (multiply-iter x _b count)
    (if (= count 0)
        x
        (if (even? count)
            (multiply-iter x (double _b) (halve count))
            (multiply-iter (+ x _b) (double _b) (halve (- count 1))))))
  (multiply-iter 0 a b))

  (* 8 2)
