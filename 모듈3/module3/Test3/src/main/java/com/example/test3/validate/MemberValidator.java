package com.example.test3.validate;

import org.springframework.validation.Errors;
import org.springframework.validation.Validator;

import com.example.test3.command.MemberCommand;

public class MemberValidator implements Validator {

	@Override
	public boolean supports(Class<?> clazz) {
		return MemberCommand.class.isAssignableFrom(clazz);
	}

	@Override
	public void validate(Object target, Errors errors) {
		MemberCommand cmd = (MemberCommand)target;
		if (cmd.getEmail() == null || cmd.getEmail().trim().equals("")) {
			errors.rejectValue("email", "email.required", "�����ּҰ� �Էµ��� �ʾҽ��ϴ�.");
		}
		else if (cmd.getPass() == null || cmd.getPass().trim().equals("")) {
			errors.rejectValue("pass", "pass.required", "��й�ȣ�� �Էµ��� �ʾҽ��ϴ�.");
		}
		else if (!cmd.getPassConfirm().equals(cmd.getPass())) {
			errors.rejectValue("passConfirm", "passConfirm.required", "��й�ȣ�� ��й�ȣ Ȯ���� ��ġ���� �ʽ��ϴ�.");
		}
		else if (cmd.getNick() == null || cmd.getNick().trim().equals("")) {
			errors.rejectValue("nick", "nick.required", "�̸��� �Էµ��� �ʾҽ��ϴ�.");
		}
	}
}
