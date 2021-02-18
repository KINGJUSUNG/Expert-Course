package com.spring.entity;

public class LectopiaTest implements Test {
	
	private int kor;
	private int eng;
	private int math;

	public LectopiaTest() {}
	public LectopiaTest(int kor, int eng, int math) {
		this.kor = kor;
		this.eng = eng;
		this.math = math;
	}
	public int getKor() {
		return kor;
	}
	public void setKor(int kor) {
		this.kor = kor;
	}
	public int getEng() {
		return eng;
	}
	public void setEng(int eng) {
		this.eng = eng;
	}
	public int getMath() {
		return math;
	}
	public void setMath(int math) {
		this.math = math;
	}
	@Override
	public int tot() {
		return (kor + eng + math);
	}
	@Override
	public double avg() {
		return ((double)tot()/3);
	}
}
