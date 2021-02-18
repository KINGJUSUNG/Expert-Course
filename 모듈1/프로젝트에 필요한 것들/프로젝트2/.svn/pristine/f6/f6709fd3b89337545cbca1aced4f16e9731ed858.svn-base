package com.surveypro.member.controller;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.surveypro.member.service.IMemberService;
import com.surveypro.member.service.MemberMyPageUpdateService;

public class MemberMyPageUpdateController implements MemberBackController {
	private IMemberService service ;
	
	public MemberMyPageUpdateController () {
		service = new MemberMyPageUpdateService();
	}
	@Override
	public void execute(HttpServletRequest request, HttpServletResponse response) {
		// TODO Auto-generated method stub
		try {
			service.doService(request, response);
			
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	
}
