package com.example.test3.controller;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import com.example.test3.exception.MemberException;
import com.example.test3.service.Login;

@Controller
public class LoginController {

	@Autowired
	@Qualifier("login")
	private Login service;

	@RequestMapping(value="/mypage")
	public String mypage() {
		return "mypage";
	}
	
	@RequestMapping(value="/login", method=RequestMethod.GET)
	public String login() {
		return "logForm";
	}
	
	@RequestMapping(value="/login", method=RequestMethod.POST)
	public String login(
			@RequestParam("email") String email, 
			@RequestParam("pass") String pass, 
			HttpSession session) {

		try {
			service.execute(email, pass, session);
			return "mypage";
		}
		catch (MemberException e) {
			System.out.println(e.getMessage());
			return "loginError";
		}
	}
}
