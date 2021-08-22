#lang sicp
; 计算三个数中较大两个之和
(define (sum_of_bigger_two_in_three x y z)
  (cond ((and (< x y) (< x z)) (+ y z))
        ((and (< y z) (< y x)) (+ x z)) 
        (else (+ x y))))

(sum_of_bigger_two_in_three 1 2 3)