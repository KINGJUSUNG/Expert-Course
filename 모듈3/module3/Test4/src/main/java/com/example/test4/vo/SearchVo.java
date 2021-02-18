package com.example.test4.vo;

public class SearchVo {
	private String word;
	private int page;
	private int pageSize;
	
	public SearchVo() {}
	public SearchVo(String word, int page, int pageSize) {
		this.word = word;
		this.page = page;
		this.pageSize = pageSize;
	}
	public String getWord() {
		return word;
	}
	public void setWord(String word) {
		this.word = word;
	}
	public int getPage() {
		return page;
	}
	public void setPage(int page) {
		this.page = page;
	}
	public int getPageSize() {
		return pageSize;
	}
	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}
}
