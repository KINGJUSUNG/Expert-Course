package com.example.test3.exception;

public abstract class MemberException extends RuntimeException {
	private static final long serialVersionUID = 1L;

	public MemberException(String message) {
		super(message);
	}
}
