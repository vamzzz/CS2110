/**
 * CS 2110 Spring 2017 HW2
 * Part 2 - Coding with bases
 *
 * @author Vamshi Adimulam
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString and
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int bits = 0;
        for (int x = 0; x < binary.length(); x++) {
            int c = (int)binary.charAt(x);
            if (c == 49) {
                bits = bits | (1 << binary.length() - x - 1);
            }
        }
        return bits;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     */
    public static int decimalStringToInt(String decimal)
    {
        int number = 0;
        for (int x = 0; x < decimal.length(); x++) {
            int c = (int)decimal.charAt(x);
            number = number * 10 + (c % 48);

        }
        return number;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int number = 0;
        for (int x = 0; x < hex.length(); x++) {
            int c = (int)hex.charAt(x);
            if (47 < c && c < 58) {
                number = (number << 4) + (c - 48);
            }
            if (64 < c && c < 91) {
                number = (number << 4) + (c - 55);
            }
        }
        return number;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     */
    public static String intToBinaryString(int binary)
    {
        String aString = "";
        boolean facts = false;
        int count = 0;
        for (int x = 31; x >= 0; x--) {
            int temp = binary | (1 << x);
            if (temp == binary) {
                aString += "1";
                facts = true;
            } else if (facts || count == 31) {
                aString += "0";
            } else {
                count++;
            }
        }
        return aString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     */
    public static String intToHexString(int hex)
    {
        String aString = "";
        int count = 1;
        int temp = hex;

        while (temp >= 16) {
            count++;
            temp = temp >> 4;
        }
        int num = 0;
        for (int x = 0; x < count; x++) {
            int copy = hex;
            copy = (copy >> 4) << 4;
            num = hex - copy;
            if (num > 9) {
                aString = (char) (num + 55) + aString;
            } else {
                aString = num + aString;
            }
            hex = hex >> 4;
        }
        return aString;

    }
}
