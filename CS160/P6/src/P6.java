// P6.java
// Author: Luke Burford
// Date:   Mar 3, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class P6 {

	// Class variables
	public static Maze maze;
	public static int mazeWidth;
	public static int mazeHeight;

	public static void main(String[] args) {

		// Create maze
		String fileName = args[0];
		System.err.println("Maze name: " + fileName);

		// Get dimensions
		maze = new Maze(fileName);
		mazeWidth = maze.getWidth();
		mazeHeight = maze.getHeight();
		System.err.println("Maze width: " + mazeWidth);
		System.err.println("Maze height: " + mazeHeight);

		// Add code to move around maze
		maze.moveUp();
		if(maze.foundHaku()){
			System.out.println("Yes!");
		}
		maze.moveUp();
		if(maze.foundHaku()){
			System.out.println("Yes!");
		}
		maze.moveUp();
		if(maze.foundHaku()){
			System.out.println("Yes!");
		}
	}
}	
