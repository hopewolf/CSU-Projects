import java.io.File;
import java.util.Arrays;
import java.util.Scanner;

public class Maze implements IMaze {

	/* Precondition - filename set to file containing map of the maze.
	 * Postcondition - two dimensional char array holding a map of the maze
	 * Postcondition - returns null if file not found
	 */
	@Override
	public char[][] readFile(String filename) {
		char[][] maze = null;
		try {
			Scanner fileIn = new Scanner(new File(filename));
			maze = new char[fileIn.nextInt()][fileIn.nextInt()];
			fileIn.nextLine();
			for(int i=0; i<maze.length; i++) {
				String currentLine = fileIn.nextLine();
				//			System.out.println(currentLine);
				for(int j=0; j<maze[i].length; j++) {
					maze[i][j] = currentLine.charAt(j);
				}
			}
			fileIn.close();
		} catch(Exception e) {
			System.err.println("Oops... File Read Error...");
			return null;
		}
		return maze;
	}

	/* Precondition - maze array initialized to a valid maze
	 * Postcondition - array containing row, column of location of S 
	 * 		returned.  Ex. if S is in maze[1][2]. the return 
	 * 		array is {1, 2}
	 * Postcondition - returns null if no S found
	 */
	@Override
	public int[] findStart(char[][] maze) {
		int[] start = new int[2];
		boolean foundS = false;
		for(int i=0; i<maze.length; i++) {
			for(int j=0; j<maze[i].length; j++) {
				if(maze[i][j] == 'S') {
					start[0] = i;
					start[1] = j;
					foundS = true;
					break;
				}
			}
		}
		if(foundS == true)
			return start;
		else {
			System.err.println("Oops... Current maze does not appear to have a start...");
			return null;
		}

	}

	/* Precondition - maze array initialize to a valid maze
	 * Precondition - StartPosition contains row, column of location of S 
	 * 		Ex. if S is in maze[1][2], the startPosition 
	 * 		 array is {1, 2}
	 * Postcondition - returns a String composed of the appropriate
	 *     characters from  'U', 'R', 'D', 'L', and the final 'G', 
	 *     indicating the solution path.
	 * Postcondition - successful path marked with '.' characters in maze
	 * 		 array from 'S' to the final 'G', indicating the 
	 * 		 solution path.
	 */
	@Override
	public String findPath(char[][] maze, int[] startPosition) {
		String temp = this.recPath(maze, startPosition[0], startPosition[1]);
		maze[startPosition[0]][startPosition[1]] = 'S';
		return temp;
	}

	/*
	 * Precondition - maze array initialized to a valid maze
	 * Postcondition - returns the path from the location r,c to the goal
	 * Postcondition - '.' set from location r,c in the maze to the goal
	 * Requirement - Implemented as a recursive method that finds a path
	 *               from position (row,col) to the goal position,
	 *               marked by 'G'
	 */
	private String recPath(char[][] maze, int r, int c) {
		if(r > maze.length-1 && c > maze[r].length-1) {
			return "";
		}
		else if(maze[r][c] == '#' || maze[r][c] == '.') {
			return "";
		}
		else if(maze[r][c] == 'G') {
			return "G";
		}
		else {
				maze[r][c] = '.';
			String test = "";
			test = recPath(maze,r-1,c);
			if(!(test.equals(""))) {
				return "U" + test;
			}
			test = recPath(maze,r,c+1);
			if(!(test.equals(""))) {
				return "R" + test;
			}
			test = recPath(maze,r+1,c);
			if(!(test.equals(""))) {
				return "D" + test;
			}
			test = recPath(maze,r,c-1);
			if(!(test.equals(""))) {
				return "L" + test;
			}
			if(!(maze[r][c] == 'S'))
				maze[r][c] = ' ';
			return "";
		}
	}

	/*
	 * Postcondition - returns a String representation of the map character array
	 * 	(complete with end of line characters).
	 */
	@Override
	public String printMaze(char[][] maze) {
		String output = "";
		for(int i=0; i<maze.length; i++) {
			for(int j=0; j<maze[i].length; j++) {
				output += maze[i][j];
			}
			output += "\n";
		}
		return output;
	}

	public static void main(String[] args) {
		Maze m = new Maze();
		char[][] testMaze = m.readFile(args[0]);
		int[] testStart = m.findStart(testMaze);
		System.out.println(Arrays.deepToString(testMaze));
		System.out.print(m.printMaze(testMaze));
		String path = m.findPath(testMaze, testStart);
//		System.out.println(Arrays.toString(testStart));
		System.out.println(m.findPath(testMaze, testStart));
		if(path.contains("G"))
			System.out.println("Found G! Path: " + path);
		else
			System.out.println("Couldn't find G... Path: " + path);
		System.out.print(m.printMaze(testMaze));
	}
}