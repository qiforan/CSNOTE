#lang sicp

;implement to calculate b ^ n in fast-expt with iteration

;solution
; b ^ n = 1 * b ^ n = 1 * (b^2)^(n/2) if n is even else b * (b^2)^(n/2)
; a * b ^ n = (a if n is even else a * b) * (b^2)^(n/2)

(define (expt b n)
  (define (expt_iter a _b count)
    (if (= count 0)
        a
        (if (even? count)
            (expt_iter a (* _b _b) (/ count 2))
            (expt_iter (* a _b) (* _b _b) (/ (- count 1) 2)))))
   (expt_iter 1 b n))

(expt 2 3)