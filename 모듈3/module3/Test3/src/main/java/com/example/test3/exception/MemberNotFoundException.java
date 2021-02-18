package com.example.test3.exception;

public class MemberNotFoundException extends MemberException {

	private static final long serialVersionUID = 1L;

	public static final String MESSAGE = "존재하지 않는 메일주소이거나 비밀번호가 일치하지 않습니다.";
	
	public MemberNotFoundException() {
		this(MESSAGE);
	}

	public MemberNotFoundException(String message) {
		super(message);
	}

}
