module H2 (
    parseMessage,
    parse,
) where

import Log

-- exercise 1

parseMessage :: String -> LogMessage
parseMessage msg =
    let wordlist = words msg
     in case wordlist of
            ("I" : ts : _str) -> LogMessage Info (read ts) (unwords _str)
            ("W" : ts : _str) -> LogMessage Warning (read ts) (unwords _str)
            ("E" : lv : ts : _str) -> LogMessage (Error (read lv)) (read ts) (unwords _str)
            _ -> Unknown $ unwords wordlist

parse :: String -> [LogMessage]
parse = map parseMessage . lines

-- exercise 2

insert :: LogMessage -> MessageTree -> MessageTree
insert (Unknown msg) messageTree = messageTree
insert logmessage@(LogMessage _ ts1 _) (Node left logmessage2@(LogMessage _ ts2 _)  right)  
    | ts1 < ts2 = Node (insert logmessage left) logmessage2 right
    | otherwise = Node left logmessage2 $ insert logmessage right
insert logmessage@LogMessage{} leaf = Node Leaf logmessage Leaf 
 