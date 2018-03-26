package com.example.uriahnewkirk.funky_beats;



public class Song {
    private String title, artist;
    private String path;
    private int duration;
    private boolean favorite;


    public Song(String s, String p) {
        title = s;
        path = p;
    }

    public String getName() {
        return title;
    }

    public String getArtist() {
        return artist;
    }

    public void setName(String t) {
        this.title = t;
    }

    public void setArtist(String a) {
        this.artist = a;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String p) {
        path = p;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int d) {
        this.duration = d;
    }

    @Override
    public String toString() {
        return title;
    }

    public void addFavorite() {
        this.favorite = true;
    }

    public void removeFavorite() {
        favorite = false;
    }

    public boolean getFavorite() {
        return favorite;
    }
}
