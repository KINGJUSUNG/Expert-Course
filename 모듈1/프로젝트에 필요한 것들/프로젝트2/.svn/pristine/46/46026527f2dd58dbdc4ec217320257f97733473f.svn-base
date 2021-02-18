package com.surveypro.member.service;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.surveypro.controller.DAOManager;
import com.surveypro.dao.MemberDAO;
import com.surveypro.vo.MemberVO;

public class MemberMyPageUpdateService implements IMemberService{
	
	private MemberDAO mdao ;
	
	public MemberMyPageUpdateService() {
		mdao = (MemberDAO)DAOManager.getDAO(MemberDAO.KEY);
	}
	
	@Override
	public void doService(HttpServletRequest request, HttpServletResponse response) throws Exception {
		// TODO Auto-generated method stub
		HttpSession session = request.getSession(false);
		MemberVO m1 = (MemberVO)session.getAttribute("userInfo");
		
		int point = (Integer)session.getAttribute("point");
		
		synchronized(mdao){
			
			MemberVO m = mdao.getSignInMember(m1.getEmail());
			System.out.println(m1);
			point = mdao.getPoint(m.getEmail());
			session.setAttribute("userInfo", m);
			session.setAttribute("point",point);	
			session.setAttribute("result",true);
			request.setAttribute("point",point);
			request.setAttribute("userInfo",m);
		}
		
	}
	
}
