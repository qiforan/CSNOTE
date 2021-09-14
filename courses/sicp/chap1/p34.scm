#lang sicp

(define (f g)
  (g 2))

(define (square x) (* x x))

;; 4
(f square)

;;6
(f (lambda (z) (* z (+ 1 z))))

;; (f f) -> (f 2) -> (f2 2) 
;; 2 is not applicable
(f f)