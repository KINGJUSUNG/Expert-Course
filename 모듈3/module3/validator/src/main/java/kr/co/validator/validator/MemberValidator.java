package kr.co.validator.validator;

import org.springframework.validation.Errors;
import org.springframework.validation.Validator;

import kr.co.validator.command.MemberCommand;

public class MemberValidator implements Validator {

	@Override
	public boolean supports(Class<?> clazz) {
		// return clazz.isAssignableFrom(MemberCommand.class);
		return MemberCommand.class.isAssignableFrom(clazz);
	}

	@Override
	public void validate(Object target, Errors errors) {
		MemberCommand cmd = (MemberCommand)target;
		if (cmd.getName() == null || cmd.getName().trim().equals("")) {
			errors.rejectValue("name", "name.required", "회원 이름이 입력되지 않았습니다.");
		}
		else if (cmd.getAge() == 0) {
			errors.rejectValue("age", "age.required", "회원 연령이 입력되지 않았습니다.");
		}
	}
}
