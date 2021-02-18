package com.example.test3.vo;

import java.sql.Timestamp;

public class MemberVo {
	private String email;
	private String pass;
	private String nick;
	private Timestamp registeredAt;
	private Timestamp removedAt;
	
	public MemberVo() {}
	public MemberVo(String email, String pass, String nick, Timestamp registeredAt, Timestamp removedAt) {
		this.email = email;
		this.pass = pass;
		this.nick = nick;
		this.registeredAt = registeredAt;
		this.removedAt = removedAt;
	}

	public String getEmail() { return email; }
	public void setEmail(String email) { this.email = email; }
	public String getPass() { return pass; }
	public void setPass(String pass) { this.pass = pass; }
	public String getNick() { return nick; }
	public void setNick(String nick) { this.nick = nick; }
	public Timestamp getRegisteredAt() { return registeredAt; }
	public void setRegisteredAt(Timestamp registeredAt) { this.registeredAt = registeredAt; }
	public Timestamp getRemovedAt() { return removedAt; }
	public void setRemovedAt(Timestamp removedAt) { this.removedAt = removedAt; }
}
