package com.example.test3.command;

public class MemberCommand {
	private String email;
	private String pass;
	private String passConfirm;
	private String nick;
	private int number;

	private String test;
	
	public MemberCommand() {}
	public MemberCommand(String email, String pass, String passConfirm, String nick) {
		this.email = email;
		this.pass = pass;
		this.passConfirm = passConfirm;
		this.nick = nick;
	}
	
	public String getTest() { return test; }
	public void setTest(String test) { this.test = test; }

	public String getEmail() { return email; }
	public void setEmail(String email) { this.email = email; }
	public String getPass() { return pass; }
	public void setPass(String pass) { this.pass = pass; }
	public String getPassConfirm() { return passConfirm; }
	public void setPassConfirm(String passConfirm) { this.passConfirm = passConfirm; }
	public String getNick() { return nick; }
	public void setNick(String nick) { this.nick = nick; }
	public int getNumber() {
		return number;
	}
	public void setNumber(int number) {
		this.number = number;
	}
}
