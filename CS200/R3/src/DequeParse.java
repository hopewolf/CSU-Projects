import java.util.Scanner;
import java.util.LinkedList;
import java.util.Deque;

/*
 * Class for parsing (recognizing) simple prefix expressions
 * Recursive descent parser for grammar:
 * <expression> = <ID> | <operator> <expression> <expression>
 * <operator> = * | + | - | \
 * <ID> = a | b | c
 *
 */

public class DequeParse {
    public static boolean isValidPrefixExpression(String s) {
        Deque<String> tokens = new LinkedList<>();

        Scanner sc = new Scanner(s);
        while(sc.hasNext()) tokens.addLast(sc.next());

        System.out.println("tokens is: " + tokens);
        return extractExpression(tokens) && tokens.isEmpty();
    }

    /* rule is
     * <expression> = <ID> | <operator> <expression> <expression>
     */
    private static boolean extractExpression(Deque<String> tokens) {
        boolean matched = extractId(tokens) ||
            (extractOperator(tokens) && extractExpression(tokens) && extractExpression(tokens));

        if(matched) System.out.println("Matched expression");
        return matched;
    }

    /* rule is
     * <ID> = Integer
     */
    private static boolean extractId(Deque<String> tokens) {
    	try {
        String first = tokens.getFirst();
    	if (first.length() == 1 && (Integer.parseInt(first) >= 0 || Integer.parseInt(first) < 0)) {
            System.out.println("Matched id: " + first);
            tokens.removeFirst();
            return true;
        }
    	}catch(NumberFormatException e) {
        
    	}
    	return false;
    }

    /* rule is
     * <operator> = + | - | * | /
     */
    private static boolean extractOperator(Deque<String> tokens) {
        String first = tokens.getFirst();
    	if (first.length() == 1 && "+-*/".contains(first)) {
            System.out.println("Matched operator: " + first);
            tokens.removeFirst();
            return true;
        }
        return false;
    }

    /*
     * Main allows us to test the class
     */
    public static void main(String[] args) {
        String[] examples = {"* 4 3", "* a b c", "a * b", "* + a b - c / a b", "a "};

        for (String s : examples)
            System.out.printf("\"%s\" is %sa valid prefix expression\n", s,
                              isValidPrefixExpression(s) ? "" : "not ");
    }
}