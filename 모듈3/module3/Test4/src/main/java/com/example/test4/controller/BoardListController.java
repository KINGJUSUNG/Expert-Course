package com.example.test4.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

import com.example.test4.service.BoardList;
import com.example.test4.vo.BoardVo;

@Controller
public class BoardListController {

	@Autowired
	@Qualifier("boardList")
	BoardList service;
	
	@RequestMapping(value="/list", method=RequestMethod.GET)
	public String list(Model model) {
		try {
			List<BoardVo> boards = null;
			boards = service.execute();
			model.addAttribute("boards", boards);
			return "boardList";
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
			return "error";
		}
	}
}
