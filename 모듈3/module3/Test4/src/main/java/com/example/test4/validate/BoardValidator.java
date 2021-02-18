package com.example.test4.validate;

import org.springframework.validation.Errors;
import org.springframework.validation.Validator;

import com.example.test4.vo.BoardCommand;

public class BoardValidator implements Validator {

	@Override
	public boolean supports(Class<?> clazz) {
		return BoardCommand.class.isAssignableFrom(clazz);
	}

	@Override
	public void validate(Object target, Errors errors) {
		BoardCommand cmd = (BoardCommand)target;
		if (cmd.getEmail() == null || cmd.getEmail().trim().equals("")) {
			errors.rejectValue("email", "email.required", "이메일이 입력되지 않았습니다.");
		}
		else if (cmd.getTitle() == null || cmd.getTitle().trim().equals("")) {
			errors.rejectValue("title", "title.required", "제목이 입력되지 않았습니다.");
		}
		else if (cmd.getContent() == null || cmd.getContent().trim().equals("")) {
			errors.rejectValue("content", "content.required", "내용이 입력되지 않았습니다.");
		}
	}
}
