package com.example.test4.vo;

public class BoardCommand {
	private String email;
	private String title;
	private String content;
	
	public BoardCommand() {}
	public BoardCommand(String email, String title, String content) {
		this.email = email;
		this.title = title;
		this.content = content;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getTitle() {
		return title;
	}
	public void setTitle(String title) {
		this.title = title;
	}
	public String getContent() {
		return content;
	}
	public void setContent(String content) {
		this.content = content;
	}
}
