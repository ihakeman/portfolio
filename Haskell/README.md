# Roman Numeral Arithmetic

- This project was an exercise in String rewriting in Haskell. I wrote all of the code myself. The supported arithmetic operations on Roman numerals are addition, subtraction and multiplication. In addition, numerals can be converted to integers, integers can be converted to numerals, and numerals can be checked to ensure they follow conventions. 

## Recommendations for Running
- Ensure that Haskell is installed on your computer.
- While you can look at the test cases in the main and simply run `runhaskell numerals.hs` or even edit the test cases and run it the same way, I suggest using GHCi.

- I have included a helpful function titled `help` that can be used within GHCi which explains the available functions and how to use them. Simply open a terminal and navigate to the folder containing `numerals.hs` and type the following:

        ghci
        :load numerals.hs
        help
- One important thing to note is that all Roman Numerals should be inputted as Strings which means that it is necessary to enclose each string with quotation marks.
- An example of how to use the `add` function to add 14 and 39 within GHCi after loading the file is

        add "XIV" "XXXIX"