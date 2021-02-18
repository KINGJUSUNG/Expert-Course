package com.example.test3.exception;

public class MemberNotFoundException extends MemberException {

	private static final long serialVersionUID = 1L;

	public static final String MESSAGE = "�������� �ʴ� �����ּ��̰ų� ��й�ȣ�� ��ġ���� �ʽ��ϴ�.";
	
	public MemberNotFoundException() {
		this(MESSAGE);
	}

	public MemberNotFoundException(String message) {
		super(message);
	}

}
