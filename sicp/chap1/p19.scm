#lang sicp

; solve matrix T = [p+q  q]
;                  [q    p]

; T' = T ^ 2 = [(p+q)^2+q^2  (p+q)q + pq]
;              [(p+q)q+pq        p^2+q^2]

;so   p^2 + q^2 -> p
;   q(p+q) + pq -> q


(define (fib n)
  (fib-iter 1 0 0 1 n))

(define (fib-iter a b p q count)
;   (display  p) (display q) (newline) 
  (cond ((= count 0) b)
        ((even? count) 
         (fib-iter a
                   b
                   (+ (* p p) (* q q))
                   (+ (* q (+ p q)) (* p q))
                   (/ count 2)))
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)))))

(fib 10)