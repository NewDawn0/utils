-- Module
module Main where

-- Imports
import System.Environment (getArgs)
import Data.List (intercalate)

-- Fn main
main :: IO ()
main = putStrLn "Hello, Haskell!"

-- Fn concatArgs: Concats an array of string with '+' as the seperator
-- @PARAM: [String]
-- @RVAL: String
concatArgs :: [String] -> String
concatArgs = intercalate "+"

