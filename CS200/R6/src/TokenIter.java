
import java.util.Iterator;

 /*
 * This Token Iterator ONLY READS SINGLE CHARACTER TOKENS
 * It is used for demonstration purposes
 * It does not read tokens defined in the Programming Assignments
 */

public class TokenIter implements Iterator<String>{
	//input line to be tokenized
	private String line;

	// the next Token, null if no next Token
	private String nextToken;

	public TokenIter(String line){
		this.line = line;
		nextToken = getToken();
	}

	private String getToken(){
		line = line.trim();
		if(line.length()==0)
			return null;
		else{
			// NOTICE: single character token!!
			String val;
			val = line.substring(0,1);
			line = line.substring(1);
			return val;
		}
	}
	
	@Override
	public boolean hasNext() {
		// TODO Auto-generated method stub
		return nextToken!=null;
	}

	@Override
	public String next() {
		// TODO Auto-generated method stub
        String t = nextToken;
        nextToken = getToken();
		return t;
	}

	@Override
	public void remove() {
		// TODO Auto-generated method stub
		throw new UnsupportedOperationException();
	}

	public static void main(String[] args){
		String line = " 1+ 2*(3 - --4) ";
		System.out.println("line: [" + line + "]");
		TokenIter tokIt = new TokenIter(line);
		while(tokIt.hasNext()){
			System.out.println("next token: [" + tokIt.next() + "]");
		}


	}
}
