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
			errors.rejectValue("email", "email.required", "메일주소가 입력되지 않았습니다.");
		}
		else if (cmd.getPass() == null || cmd.getPass().trim().equals("")) {
			errors.rejectValue("pass", "pass.required", "비밀번호가 입력되지 않았습니다.");
		}
		else if (!cmd.getPassConfirm().equals(cmd.getPass())) {
			errors.rejectValue("passConfirm", "passConfirm.required", "비밀번호와 비밀번호 확인이 일치하지 않습니다.");
		}
		else if (cmd.getNick() == null || cmd.getNick().trim().equals("")) {
			errors.rejectValue("nick", "nick.required", "이름이 입력되지 않았습니다.");
		}
	}
}
