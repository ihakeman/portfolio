help = do
    putStrLn $ "The following are functions with the number of arguments preceding the name. Note: Strings must be in quotation marks"
    putStrLn $ "----------------------------------------------------------------------------------------------------------------------"
    putStrLn $ "2  add            - Returns the Roman Numeral result of addition on two Roman Numeral strings."
    putStrLn $ "2  sub            - Returns the Roman Numeral result of subtraction on two Roman Numeral strings."
    putStrLn $ "2  multiply       - Returns the Roman Numeral result of multiplication on two Roman Numeral strings."
    putStrLn $ "1  intToNum       - Returns the Roman Numeral corresponding to the input integer or gives explains why it couldn't."
    putStrLn $ "1  numToInt       - Returns the integer corresponding to the valid Roman Numeral input string."
    putStrLn $ "1  checkValid     - Returns the Roman Numeral input string or gives an error telling that it breaks the rules."
    putStrLn $ "1  removeNegative - Returns the Roman Numeral input string with rules broken so that characters are in order of value."
    putStrLn $ "1  normalize      - Returns a rule-following Roman Numeral string given an input string of Roman Numeral characters. "
    putStrLn $ "1  elongate       - Returns a value representation solely in 'I's given a string of Roman Numeral characters."
    putStrLn $ "----------------------------------------------------------------------------------------------------------------------"

--functions for checking if strings abide by Roman Numeral conventions
isValidChars :: String -> Bool
isValidChars (x:rest) = if (x == 'M' || x == 'D' || x == 'C' || x == 'L' || x == 'X' || x == 'V' || x == 'I')
    then (isValidChars rest) 
    else False
isValidChars "" = True

checkValid :: String -> String
checkValid "" = error "Empty string is not a valid Roman numeral."
checkValid x = if (isValidChars x) 
    then (if (isValidRules x) then x else error ("Sequence of numerals \"" ++ x ++ "\" does not follow conventions.")) 
    else error ("Invalid characters found in \"" ++ x ++ "\". Only 'M', 'D', 'C', 'L', 'X', 'V', and 'I' are allowed.")

isValidRules :: String -> Bool
isValidRules (a:b:c:d:rest) = if ((isValidRules4 (a:b:c:d:rest)) && (isValidRules3 (a:b:c:rest)) && (isValidRules2 (a:b:rest))) then (isValidRules (b:c:d:rest)) else False
isValidRules (a:b:c:rest) = if ((isValidRules3 (a:b:c:rest)) && (isValidRules2 (a:b:rest))) then (isValidRules (b:c:rest)) else False
isValidRules (x:y:rest) = if (isValidRules2 (x:y:rest)) then (isValidRules (y:rest)) else False
isValidRules (x:"") = True

isValidRules2 :: String -> Bool
isValidRules2 (a:b:rest)
    | (b == 'M' && (a == 'I' || a == 'V' || a == 'X' || a == 'L' || a == 'D')) = False
    | (b == 'D' && (a == 'I' || a == 'V' || a == 'X' || a == 'L' || a == 'D')) = False
    | (b == 'C' && (a == 'I' || a == 'V' || a == 'L')) = False
    | (b == 'L' && (a == 'I' || a == 'V' || a == 'L')) = False
    | (b == 'X' && a == 'V') = False
    | (b == 'V' && a == 'V') = False
    | otherwise = True

isValidRules3 :: String -> Bool
isValidRules3 (a:b:c:rest)
    | (a == c && b /= a && (isGreaterThanOrEqualNum b a)) = False
    | (a == b && a /= c && (isGreaterThanOrEqualNum c a)) = False
    | (a == c && (a == 'D' || a == 'L' || a == 'V')) = False
    | (a /= b && a /= c && (isGreaterThanOrEqualNum b a) && (isGreaterThanOrEqualNum c a)) = False
    | otherwise = True

isValidRules4 :: String -> Bool
isValidRules4 (a:b:c:d:rest)
    | (a /= 'M' && a == b && a == c && a == d) = False
    | otherwise = True

--functions for normalizing strings in one way or another
removeNegative :: String -> String
removeNegative ('C':'D':rest) = 'C':'C':'C':'C': removeNegative rest
removeNegative ('C':'M':rest) = 'D':'C':'C':'C':'C': removeNegative rest
removeNegative ('X':'L':rest) = 'X':'X':'X':'X': removeNegative rest
removeNegative ('X':'C':rest) = 'L':'X':'X':'X':'X': removeNegative rest
removeNegative ('I':'X':rest) = 'V':'I':'I':'I':'I': removeNegative rest
removeNegative ('I':'V':rest) = 'I':'I':'I':'I': removeNegative rest
removeNegative (x:rest) = x:removeNegative rest
removeNegative "" = ""

normalize :: String -> String
normalize x = format $ sort x

format :: String -> String
format x = formatD $ formatC $ formatL $ formatX $ formatV $ formatI x

formatI :: String -> String
formatI ('I':'I':'I':'I':'I':rest) = 'V':(formatI rest)
formatI ('I':'I':'I':'I':rest) = 'I':'V':(formatI rest)
formatI (x:rest) = x:(formatI rest)
formatI "" = ""

formatV :: String -> String
formatV ('V':'V':rest) = 'X':(formatV rest)
formatV ('V':'I':'V':rest) = 'I':'X':(formatV rest)
formatV (x:rest) = x:(formatV rest)
formatV "" = ""

formatX :: String -> String
formatX ('X':'X':'X':'X':'X':rest) = 'L':(formatX rest)
formatX ('X':'X':'X':'X':rest) = 'X':'L':(formatX rest)
formatX (x:rest) = x:(formatX rest)
formatX "" = ""

formatL :: String -> String
formatL ('L':'L':rest) = 'C':(formatL rest)
formatL ('L':'X':'L':rest) = 'X':'C':(formatL rest)
formatL (x:rest) = x:(formatL rest)
formatL "" = ""

formatC :: String -> String
formatC ('C':'C':'C':'C':'C':rest) = 'D':(formatC rest)
formatC ('C':'C':'C':'C':rest) = 'C':'D':(formatC rest)
formatC (x:rest) = x:(formatC rest)
formatC "" = ""

formatD :: String -> String
formatD ('D':'D':rest) = 'M':(formatD rest)
formatD ('D':'C':'D':rest) = 'C':'M':(formatD rest)
formatD (x:rest) = x:(formatD rest)
formatD "" = ""

elongate :: String -> String
elongate x = elongateV $ elongateX $ elongateL $ elongateC $ elongateD $ elongateM $ removeNegative x

elongateM :: String -> String
elongateM ('M':rest) = 'D':'D':(elongateM rest)
elongateM (x:rest) = x:(elongateM rest)
elongateM "" = ""

elongateD :: String -> String
elongateD ('D':rest) = 'C':'C':'C':'C':'C':(elongateD rest) 
elongateD (x:rest) = x:(elongateD rest)
elongateD "" = ""

elongateC :: String -> String
elongateC ('C':rest) = 'L':'L':(elongateC rest)
elongateC (x:rest) = x:(elongateC rest)
elongateC "" = ""

elongateL :: String -> String
elongateL ('L':rest) = 'X':'X':'X':'X':'X':(elongateL rest)
elongateL (x:rest) = x:(elongateL rest)
elongateL "" = ""

elongateX :: String -> String
elongateX ('X':rest) = 'V':'V':(elongateX rest)
elongateX (x:rest) = x:(elongateX rest)
elongateX "" = ""

elongateV :: String -> String
elongateV ('V':rest) = 'I':'I':'I':'I':'I':(elongateV rest) 
elongateV (x:rest) = x:(elongateV rest)
elongateV "" = ""

--functions for sorting numerals
isGreaterThanOrEqualNum :: Char -> Char -> Bool--essentially a comparison override
isGreaterThanOrEqualNum 'M' _ = True

isGreaterThanOrEqualNum 'D' 'M' = False
isGreaterThanOrEqualNum 'D' _ = True

isGreaterThanOrEqualNum 'C' 'M' = False
isGreaterThanOrEqualNum 'C' 'D' = False
isGreaterThanOrEqualNum 'C' _ = True

isGreaterThanOrEqualNum 'L' 'M' = False
isGreaterThanOrEqualNum 'L' 'D' = False 
isGreaterThanOrEqualNum 'L' 'C' = False
isGreaterThanOrEqualNum 'L' _ = True

isGreaterThanOrEqualNum 'X' 'M' = False
isGreaterThanOrEqualNum 'X' 'D' = False
isGreaterThanOrEqualNum 'X' 'C' = False
isGreaterThanOrEqualNum 'X' 'L' = False
isGreaterThanOrEqualNum 'X' _ = True

isGreaterThanOrEqualNum 'V' 'M' = False
isGreaterThanOrEqualNum 'V' 'D' = False
isGreaterThanOrEqualNum 'V' 'C' = False
isGreaterThanOrEqualNum 'V' 'L' = False
isGreaterThanOrEqualNum 'V' 'X' = False
isGreaterThanOrEqualNum 'V' _ = True

isGreaterThanOrEqualNum 'I' _ = False

--insert and sort from assignments with different comparison
insert :: Char -> String -> String
insert x "" = x:""
insert x (y:ys) = if (isGreaterThanOrEqualNum x y) then x:y:ys else y:(insert x ys)

sort :: String -> String
sort (y:rest) = insert y (sort rest)
sort "" = ""

--functions for converting to integers and back (for input/output only)
intToNum :: Integer -> String
intToNum x = format (intToNumRec x) 

intToNumRec :: Integer -> String
intToNumRec 1 = "I"
intToNumRec x = if x < 1 then error "Roman Numerals cannot express values less than 1." else ("I" ++ intToNumRec (x-1))

numToInt :: String -> Integer
numToInt x = numToIntRec $ removeNegative $ checkValid x

numToIntRec :: String -> Integer
numToIntRec (x:rest)
    | (x == 'M') = 1000 + numToIntRec rest
    | (x == 'D') = 500 + numToIntRec rest
    | (x == 'C') = 100 + numToIntRec rest
    | (x == 'L') = 50 + numToIntRec rest
    | (x == 'X') = 10 + numToIntRec rest
    | (x == 'V') = 5 + numToIntRec rest
    | (x == 'I') = 1 + numToIntRec rest
    | otherwise = error "Invalid character found."
numToIntRec "" = 0

--core functionality
add :: String -> String -> String
add a b = normalize $ (removeNegative (checkValid a)) ++ (removeNegative (checkValid b))

multiply :: String -> String -> String--since extra fluff is needed outside of recursion, multiply and sub are split into recursive and non recursive functions
multiply a b = normalize $ multiplyRec (elongate (checkValid a)) (removeNegative (checkValid b))

sub :: String -> String -> String
sub a b = format $ subtractRec (elongate (checkValid a)) (elongate (checkValid b))

subtractRec :: String -> String -> String
subtractRec "" b = error "Result is less than 1 which cannot be expressed in Roman Numerals."
subtractRec a "" = a
subtractRec (a:resta) (b:restb) = subtractRec resta restb

multiplyRec :: String -> String -> String
multiplyRec ('I':rest) b = (b ++ (multiplyRec rest b))
multiplyRec "" b = ""

main = do
{-    print $ removeNegative "MCDIX"
    print $ removeNegative "CDCMXLXCIXIVC"
    print $ removeNegative "XXVII"
    print $ sort "CDCMXLXCIXIVC"
    --print $ normalize $ removeNegative "CDCMXLXCIXIVC"

    print $ format "IIIIII"
    print $ format "IIIIIIIIIII"
    print $ format "IIIIIIIII"
    print $ format "IIIII"
    print $ format "IIII"
    print $ format "I"
    print $ format "VVVVVVVVVIIIII"
    print $ format "XXXX"
    print $ format "XXXXX"
    print $ format "LXL"
    print $ format "LXLX"
    print $ format "LLX"

    print$ isGreaterThanOrEqualNum 'L' 'C'
    print $ format "CCCCCC"
    print $ format "CCCC"
    print $ format "CLX"
    print $ format "DDDDDDD"
    print $ format "DDDDCD"
    print $ format "CCCCCCCCCCC"
    print $ format "MDCCCCCCCLLLLXXXXXXVVVVVVVVVVIIIIIIIIIIIIIIIIIIIII"

    print $ normalize "MCDIVLXLM"
    --print $ checkValid "IIIIIB"
    --print $ checkValid "BIIIII"
    --print $ checkValid "MCDIVLXL"
    print $ checkValid "MCDLXXIV"
    --print $ isValidChars "MCDIVLXLc"
-}
    putStrLn $ "\nAddition:"
    print $ add "I" "IV"
    print $ add "XLIV" "MMCDLVIII"
    --print $ add "XLXX" "MCLXIV"
    print $ add "CCCLXV" "MMDCCXLVIII"
    print $ add "XXI" "I"
    print $ add "XIX" "I"
    print $ add "MCM" "I"
    print $ add "LXXXVII" "MMCDLVIII"
    print $ add (intToNum 87) (intToNum 2458)
{-
    print $ "Elongate:"
    print $ elongate "XLVI"
    print $ elongate "MDCLXVI"
    print $ numToInt $ format $ elongate "MDCLXVI"
    print $ format $ elongate "MDCLXVI"-}
    putStrLn $ "\nMultiplication:"
    print $ multiply "III" "M"
    print $ multiply "XL" "IV"
    putStrLn $ "\nSubtraction:"
    print $ sub "M" "CMXCIX"
    print $ sub "M" "CLXVIII"
    putStrLn $ "\nConversion to integers:"
    print $ numToInt "CLXVIII"
    print $ numToInt "DCCCXXXII"
    putStrLn $ "\nConversion from integers:"
    print $ intToNum 1982
    print $ intToNum 14