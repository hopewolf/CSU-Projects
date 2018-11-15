
import java.util.Iterator;
import java.util.Scanner;


public class TokenIter implements Iterator<String>{

	//input line to be tokenized
	private String line;

	// the next Token, null if no next Token
	private String nextToken;

	public TokenIter(String line){
		this.line = line;
	}

	@Override
	public boolean hasNext() {
		if(this.line.isEmpty()) {
			Debug.printf("nextToken = null");
			return false;
		}
		Scanner sc = new Scanner(this.line);
		while(true) {
			this.line = line.trim();
			if(this.line.isEmpty()) {
				sc.close();
				return false;
			}
			String current = sc.next();
			if(current.charAt(0)==')' || current.charAt(0)=='(') {
				this.nextToken = current.substring(0, 1);
				this.line = line.substring(1, this.line.length());
				Debug.printf("nextToken =%s",nextToken);
				Debug.printf("line is now =%s",line);
				sc.close();
				return true;
			}
			else if(current.equals("or") 
					|| current.equals("and")
					|| current.contains("not")) {
				if(current.contains("not")) {
					if(current.substring(0,3).contains("not")) {
						if(current.charAt(3) == '(') {
							this.nextToken = current.substring(0,3);
							this.line = line.substring(nextToken.length(),this.line.length());
							Debug.printf("nextToken =%s",nextToken);
							Debug.printf("line is now =%s",line);
							sc.close();
							return true;
						}
					}
				}
				this.nextToken = current;
				this.line = line.substring(current.length(),this.line.length());
				Debug.printf("nextToken =%s",nextToken);
				Debug.printf("line is now =%s",line);
				sc.close();
				return true;
			}
			else if(current.contains("true")) {
				if(current.length() > 4) {
					if(current.charAt(4) == ')') {
						this.nextToken = current.substring(0,4);
						this.line = line.substring(4, this.line.length());
						Debug.printf("nextToken =%s",nextToken);
						Debug.printf("line is now =%s",line);
						sc.close();
						return true;
					}
				}
				else {
					this.nextToken = current.substring(0,4);
					this.line = line.substring(4);
					Debug.printf("nextToken =%s",nextToken);
					Debug.printf("line is now =%s",line);
					sc.close();
					return true;
				}
			}
			else if(current.contains("false")) {
				if(current.length() > 5) {
					if(current.charAt(5) == ')') {
						this.nextToken = current.substring(0,5);
						this.line = line.substring(5, this.line.length());
						Debug.printf("nextToken =%s",nextToken);
						Debug.printf("line is now =%s",line);
						sc.close();
						return true;
					}
				}
				else {
					this.nextToken = current.substring(0,5);
					this.line = line.substring(5);
					Debug.printf("nextToken =%s",nextToken);
					Debug.printf("line is now =%s",line);
					sc.close();
					return true;
				}
			}
			this.line = line.substring(current.length(),this.line.length());
		}
	}

	@Override
	public String next() {
		String token = "";
		if(nextToken.equals("(") || nextToken.equals(")")) {
			token = nextToken.substring(0, 1);
		}
		else if(nextToken.equals("or") 
				|| nextToken.equals("and")
				|| nextToken.equals("not")) {
			token = nextToken;
		}
		else if(nextToken.contains("true")) {
			token = nextToken.substring(0,4);
		}
		else if(nextToken.contains("false")) {
			token = nextToken.substring(0,5);

		}
		return token;
	}

	@Override
	public void remove() {
		throw new UnsupportedOperationException();
	}
	public static void main(String[] args){
		String line;
		if(args.length>0)
			line = args[0];
		else
			line = "not(true or false)";	//line = " not (true or garbage false  && ) more";
		System.out.println("line: [" + line + "]");
		TokenIter tokIt = new TokenIter(line);
		while(tokIt.hasNext()){
			System.out.println("next token: [" + tokIt.next() + "]");
		}


	}
}
