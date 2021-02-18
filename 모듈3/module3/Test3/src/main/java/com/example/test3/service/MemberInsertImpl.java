package com.example.test3.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import com.example.test3.command.MemberCommand;
import com.example.test3.dao.MemberDao;
import com.example.test3.exception.MemberException;
import com.example.test3.vo.MemberVo;

@Service("memberInsert")
public class MemberInsertImpl implements MemberInsert {

	@Autowired
	@Qualifier("memberDao")
	private MemberDao dao;
	
	@Override
	public void execute(MemberCommand member) throws MemberException {
		MemberVo memberVo = new MemberVo();
		memberVo.setEmail(member.getEmail());
		memberVo.setPass(member.getPass());
		memberVo.setNick(member.getNick());
		dao.insert(memberVo);
	}
}