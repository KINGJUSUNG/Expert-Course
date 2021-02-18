package com.example.test3.service;

import javax.servlet.http.HttpSession;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import com.example.test3.dao.MemberDao;
import com.example.test3.exception.MemberException;
import com.example.test3.exception.MemberNotFoundException;
import com.example.test3.vo.MemberVo;

@Service("login")
public class LoginImpl implements Login {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;

	@Override
	public void execute(String email, String pass, HttpSession session) throws MemberException {
		MemberVo member = dao.login(email, pass);
		if (member == null) {
			throw new MemberNotFoundException();
		}
		session.setAttribute("loginInfo", member);
	}
}
