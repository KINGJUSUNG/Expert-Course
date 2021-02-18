package vo;

import java.util.ArrayList;

public class Category { 
	private String code;
	private String name;
	private ArrayList<Comic> comics;
	
	public Category() {
		this.comics = new ArrayList<>();
	}
	
	public Category(String code, String name) {
		this();
		this.code = code;
		this.name = name;
	}
	
	public void setCode(String code) { 
		this.code = code;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public void setComics(ArrayList<Comic> comics) {
		this.comics = comics;
	}
	
	public String getCode() {
		return this.code;
	}
	
	public String getName() {
		return this.name;
	}
	
	public ArrayList<Comic> getComics() {
		return this.comics;
	}
	
	public void addComic(Comic comic) {
		this.comics.add(comic);
	}
}
