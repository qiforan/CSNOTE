#lang sicp

(define (prime? n)
  (define (smallest_divisor x)
    (find-divisor x 2))
  (define (square x)
    (* x x))
  (define (divides? a b)
    (= (remainder b a) 0))
  (define (find-divisor x test-divisor)
    (cond ((> (square test-divisor) x) x)
          ((divides? test-divisor x) test-divisor)
          (else (find-divisor x (+ 1 test-divisor)))))
   (= n (smallest_divisor n)))


(define (time-prime-test n)
  (define (start-prime-test n start-time)
    (if (prime? n)
        (report-prime (- (runtime) start-time))))
  (define (report-prime elapsed-time)
    (display " *** ")
    (display elapsed-time)
    (newline))
;   (newline)
  (display n)
  (start-prime-test n (runtime)))

(define (search-for-prime begin)
  (if (prime? begin)
      (time-prime-test begin)
      (search-for-prime (+ 1 begin))))

(search-for-prime 1000)
(search-for-prime 10000)
(search-for-prime 100000)
(search-for-prime 1000000)
(search-for-prime 10000000)
(search-for-prime 100000000)


