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
			errors.rejectValue("name", "name.required", "ȸ�� �̸��� �Էµ��� �ʾҽ��ϴ�.");
		}
		else if (cmd.getAge() == 0) {
			errors.rejectValue("age", "age.required", "ȸ�� ������ �Էµ��� �ʾҽ��ϴ�.");
		}
	}
}
