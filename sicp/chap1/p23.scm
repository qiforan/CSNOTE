#lang sicp

; 存在问题

(define (prime? n)
  (define (smallest_divisor x)
    (find-divisor x 2))
  (define (square x)
    (* x x))
  (define (divides? a b)
    (= (remainder b a) 0))
  (define (next test-divisor)
    (if (= test-divisor 2)
        3
        (+ 2 test-divisor)))
  (define (find-divisor x test-divisor)
    (cond ((> (square test-divisor) x) x)
          ((divides? test-divisor x) test-divisor)
          (else (find-divisor x (next test-divisor)))))
  (= n (smallest_divisor n)))

(define (time-prime-test n)
  (start-prime-test n (runtime)))

(define (start-prime-test n start-time)
  (if (prime? n)
      (report-prime n start-time (runtime))))

(define (report-prime n begin-time end-time)
  (display n)
  (display " *** ")
  (display (runtime))
  (display " *** ")
  (display (- end-time begin-time))
  (newline))
    
(define (find_prime begin count)
  (time-prime-test begin)
  (if (> count 0)
      (if (prime? begin)
          (find_prime (+ begin 1) (- count 1))
          (find_prime (+ begin 1) count))))

(find_prime 10007 12)
