#lang sicp
; two way to implement function (n) = f(n-1) + 2*f(n-2) + 3*f(n-3) if n >= 3, else f(n) = n

;tree
(define (f_tree n)
  (if (< n 3)
      n
      (+ (f_tree (- n 1)) (* 2 (f_tree (- n 2))) (* 3 (f_tree (- n 3))))))

;iter
(define (f n)
  (define (f_iter a b c count)
    (if (< count 3)
        c
        (f_iter b c (+ (* 3 a) (* 2 b) (* 1 c)) (- count 1))))
   (f_iter 0 1 2 n))

(define x 8)
(= (f_tree x) (f x))