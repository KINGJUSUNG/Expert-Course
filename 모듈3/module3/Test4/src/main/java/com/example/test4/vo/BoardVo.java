package com.example.test4.vo;

import java.sql.Timestamp;

public class BoardVo {
	private int id;
	private int m_id;
	private int s_id;
	private String email;
	private String title;
	private String content;
	private Timestamp regDate;
	private int hits;
	
	public BoardVo() {}
	public BoardVo(int id, int m_id, int s_id, String email, String title, String content, Timestamp regDate, int hits) {
		this.id = id;
		this.m_id = m_id;
		this.s_id = s_id;
		this.email = email;
		this.title = title;
		this.content = content;
		this.regDate = regDate;
		this.hits = hits;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public int getM_id() {
		return m_id;
	}
	public void setM_id(int m_id) {
		this.m_id = m_id;
	}
	public int getS_id() {
		return s_id;
	}
	public void setS_id(int s_id) {
		this.s_id = s_id;
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
	public Timestamp getRegDate() {
		return regDate;
	}
	public void setRegDate(Timestamp regDate) {
		this.regDate = regDate;
	}
	public int getHits() {
		return hits;
	}
	public void setHits(int hits) {
		this.hits = hits;
	}
	
	public String toString() {
		return String.format("%d %d %d %s %s %s %s %d\n",  id, m_id, s_id, email, title, content, regDate.toString(), hits);
	}
}
