package com.surveypro.survey.service;

import java.util.ArrayList;
import java.util.Iterator;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.surveypro.controller.DAOManager;
import com.surveypro.dao.SurveyInfoDAO;
import com.surveypro.vo.MemberVO;
import com.surveypro.vo.SurveyInfoVO;

public class SurveyGetSurveyInfoService implements ISurveyService {
	
	private SurveyInfoDAO dao;
	
	public SurveyGetSurveyInfoService() {
		dao = (SurveyInfoDAO)DAOManager.getDAO("SurveyInfoDAO");
	}
	
	@Override
	public void doService(HttpServletRequest request, HttpServletResponse response) 
			throws Exception {
		
		ArrayList<SurveyInfoVO> list = null;
		
		String type = (String)request.getParameter("msg");
		HttpSession session = request.getSession(false);
		MemberVO m = (MemberVO)session.getAttribute("userInfo");
		String respondent = m.getEmail();
		
		synchronized (dao) {
			switch (type) {
			case "deadLine":
				list = dao.getSurveyInfoByDeadLine();
				break;
			case "spareSampleNum":
				list = dao.getSurveyInfoBySpareSampleNum();
				break;
			case "endSurvey":
				list = dao.getSurveyInfoByEndSurvey();
				break;
			default:
				break;
			}
		}

		Iterator<SurveyInfoVO> it = list.iterator();
		while (it.hasNext()) {
			it.next().setRespondent(respondent);
		}
		
		request.setAttribute("list", list);
	}
}
