module Main where

import Data.List

a :: Maybe Int
a = Just 3

b :: Char
b = 'x'

replicateB :: Int -> String
replicateB = (`replicate` b)

main :: IO ()
main = print $ replicateB 3