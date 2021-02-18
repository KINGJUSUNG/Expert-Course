package com.example.test3.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.example.test3.command.MemberCommand;
import com.example.test3.exception.MemberException;
import com.example.test3.service.MemberInsert;
import com.example.test3.validate.MemberValidator;

@Controller
public class MemberController {

	@Autowired
	@Qualifier("memberInsert")
	MemberInsert service;
	
	@RequestMapping(value="member/register", method=RequestMethod.GET)
	public String register() {
		return "member/registerForm";
	}
	
	@RequestMapping(value="member/register", method=RequestMethod.POST)
	public String register(@ModelAttribute("info") MemberCommand member, Errors errors) {
		// 검증
		new MemberValidator().validate(member, errors);
		if (errors.hasErrors()) {
			return "member/registerForm";
		}
		
		// DB에 저장
		service.execute(member);
		return "member/result";
	}
	
	@ExceptionHandler(MemberException.class)
	public String handlerException() {
		return "member/error";
	}
}
