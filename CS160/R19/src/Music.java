// Music.java
// Author: Luke Burford
// Date:   Apr 19, 2016
// Class:  CS160
// Email:  lburford@rams.colostate.edu

public class Music {

	//Instance Variables
	private String songTitle;
	private String albumName;
	private String artistName;
	private int releaseYear;

	// Constructor
	public Music(String title, String album, String artist, int year) {
		songTitle = title;
		albumName = album;
		artistName = artist;
		releaseYear = year;
	}

	// Accessor methods
	public String getTitle() { 
		return songTitle; 
	}
	
	public String getAlbum() { 
		return albumName;
	}
	
	public String getArtist() {
		return artistName;
	}
	
	public int getYear() {
		return releaseYear;
	}
	
	// toString method
	public String toString() {
		String out = "";
		out = out.concat(songTitle);
		out = out.concat(", ");
		out = out.concat(albumName);
		out = out.concat(", ");
		out = out.concat(artistName);
		out = out.concat(", ");
		out += releaseYear;
		return out;
	}
    public double getPrice() {
    	double price = 0.0;
    	if(releaseYear < 1970)
    		price = 1.29;
    	else if(releaseYear >= 1970 && releaseYear < 1980)
    		price = 1.89;
    	else if(releaseYear >= 1980 && releaseYear < 1990)
    		price = 0.69;
    	else if(releaseYear >= 1990 && releaseYear < 2000)
    		price = 0.99;
    	else if(releaseYear >= 2000 && releaseYear < 2009)
    		price = 1.39;
    	else if(releaseYear <= 2010)
    		price = 0.59;
    	return price;
    	
    }

}
