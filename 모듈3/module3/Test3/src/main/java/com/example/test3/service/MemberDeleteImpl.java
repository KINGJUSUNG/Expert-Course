package com.example.test3.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import com.example.test3.dao.MemberDao;

@Service("memberDelete")
public class MemberDeleteImpl implements MemberDelete {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;

	@Override
	public void execute(String email, String pass) throws Exception {
		
	}
}
