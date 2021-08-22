{-# LANGUAGE ViewPatterns #-}
module H1
  ( toDigits,
    doubleEveryOther,
    sumDigits,
    validate,
    hanoi,
    hanoi4
  )
where

-- exercise 1

toDigits :: Integer -> [Integer]
toDigits n
  | n > 0 = (++) (toDigits $ div n 10) [mod n 10]
  | otherwise = []

toDigitsRev :: Integer -> [Integer]
toDigitsRev digit = reverse $ toDigits digit

-- exercise 2

doubleEveryOtherAux :: [Integer] -> [Integer]
doubleEveryOtherAux [] = []
doubleEveryOtherAux [x] = [x]
doubleEveryOtherAux (x : y : zs) = x : 2 * y : doubleEveryOtherAux zs

doubleEveryOther :: [Integer] -> [Integer]
doubleEveryOther l = reverse $ doubleEveryOtherAux $ reverse l

doubleEveryOther1 :: [Integer] -> [Integer]
doubleEveryOther1 (reverse -> (x : y : zs)) = doubleEveryOther1 (reverse zs) ++ [2 * y, x]
doubleEveryOther1 _ = []

-- exercise 3

sumDigits :: [Integer] -> Integer
sumDigits [] = 0
sumDigits (x : ys) = sum (toDigits x) + sumDigits ys

-- exercise 4

validate :: Integer -> Bool
validate digit =
  let _sum = sumDigits $ doubleEveryOther $ toDigits digit
   in 0 == (_sum `mod` 10)

-- exercise 5

type Peg = String
type Move = (Peg, Peg)

hanoi :: Integer -> Peg -> Peg -> Peg -> [Move]
hanoi n a b c 
  | n == 0 = []
  | otherwise  = hanoi (n-1) a c b ++ [(a,b)] ++ hanoi (n-1) c b a

-- exercise 6

-- not solved

hanoi4 :: Integer -> Peg -> Peg -> Peg -> Peg -> [Move]
hanoi4 n a b c d
  | n == 0 = []
  | n == 1 = [(a,b)]
  | n == 2 = [(a,c),(a,b),(c,b)]
  | n == 3 = [(a,b),(a,c),(a,d),(b,a),(d,b),(c,b),(a,b)]
  | otherwise  = hanoi4 (n-2) a c b d ++ [(a,d),(a,b),(d,b)] ++ hanoi4 (n-2) c b a d

