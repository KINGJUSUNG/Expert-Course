package com.example.test3.exception;

public class MemberInsertFailedException extends MemberException {

	private static final long serialVersionUID = 1L;

	public static final String MESSAGE = "회원 등록에 실패하였습니다.";

	public MemberInsertFailedException() {
		this(MESSAGE);
	}

	public MemberInsertFailedException(String message) {
		super(message);
	}
}
