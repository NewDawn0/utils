-- Module
module Main where

-- Imports
import System.Environment (getArgs)
import Data.List (intercalate)
import qualified Data.ByteString.Lazy.Char8 as L8
import Network.HTTP.Client
import Network.HTTP.Client.TLS (tlsManagerSettings)

-- Fn main
main :: IO ()
main = do
  args <- getArgs
  let url = "https://vid.puffyan.us/serach?q=" ++ concatArgs args
  putStrLn url

-- Fn concatArgs: Concats an array of string with '+' as the seperator
-- @PARAM: [String]
-- @RVAL: String
concatArgs :: [String] -> String
concatArgs = intercalate "+"

-- Fn request: Makes a GET request to the url
-- @PARAM: String
-- @RVAL: IO String
-- requestUrlContent :: String -> IO String
