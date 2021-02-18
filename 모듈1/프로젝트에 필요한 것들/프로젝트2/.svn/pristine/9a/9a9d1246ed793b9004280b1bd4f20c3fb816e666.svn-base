package com.surveypro.survey.service;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.surveypro.controller.DAOManager;
import com.surveypro.dao.SurveyDAO;
import com.surveypro.vo.SurveyVO;

public class SurveyGetBySurveyCodeService implements ISurveyService {
	
	private SurveyDAO dao;
	
	public SurveyGetBySurveyCodeService() {
		dao = (SurveyDAO)DAOManager.getDAO("SurveyDAO");
	}
	
	@Override
	public void doService(HttpServletRequest request, HttpServletResponse response) 
			throws Exception {
		
		int s_code = Integer.parseInt(request.getParameter("s_code"));
		SurveyVO s = null;
		
		synchronized (dao) {
			s = dao.getSurvey(s_code);
		}
		
		request.setAttribute("SurveyVO", s);
	}
}
