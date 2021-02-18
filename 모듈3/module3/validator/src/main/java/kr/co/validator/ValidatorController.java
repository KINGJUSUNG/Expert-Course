package kr.co.validator;

import org.springframework.stereotype.Controller;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import kr.co.validator.command.MemberCommand;
import kr.co.validator.validator.MemberValidator;

@Controller
public class ValidatorController {
	
	@RequestMapping(value="/validator", method=RequestMethod.GET)
	public String getValidator(@ModelAttribute("info") MemberCommand cmd) {
		return "form";
	}

	@RequestMapping(value="/validator", method=RequestMethod.POST)
	public String postValidator(@ModelAttribute("info") MemberCommand cmd, Errors errors) {
		new MemberValidator().validate(cmd, errors);
		if (errors.hasErrors()) {
			return "form";
		}
		return "ok";
	}
}
