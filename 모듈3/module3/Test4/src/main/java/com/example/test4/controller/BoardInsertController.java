package com.example.test4.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.validation.Errors;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.example.test4.service.BoardInsert;
import com.example.test4.validate.BoardValidator;
import com.example.test4.vo.BoardCommand;

@Controller
public class BoardInsertController {

	@Autowired
	@Qualifier("boardInsert")
	BoardInsert service;
	
	@RequestMapping(value="/register", method=RequestMethod.GET)
	public String register() {
		return "registerForm";
	}
	
	@RequestMapping(value="/register", method=RequestMethod.POST)
	public String register(@ModelAttribute("boardCmd") BoardCommand cmd, Errors errors) {

		new BoardValidator().validate(cmd, errors);
		if (errors.hasErrors()) {
			return "registerForm";
		}
		try {
			service.execute(cmd);
			return "redirect:list";
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
			return "error";
		}
	}
}