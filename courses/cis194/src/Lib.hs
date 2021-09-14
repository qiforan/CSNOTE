module Lib
    ( someFunc
    , sayYo) where

sayYo :: String -> String
sayYo input = "Yo " ++ input ++ "!"

someFunc :: IO ()
someFunc = putStrLn "someFunc"

