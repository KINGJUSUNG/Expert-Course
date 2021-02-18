package com.surveypro.member.controller;

import java.io.PrintWriter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.json.simple.JSONObject;

import com.surveypro.member.service.IMemberService;
import com.surveypro.member.service.MemberLoginService;
import com.surveypro.vo.MemberVO;

public class MemberLoginController implements MemberBackController {

	private IMemberService service;

	public MemberLoginController() {
		service = new MemberLoginService();
	}

	@SuppressWarnings("unchecked")
	public void execute(HttpServletRequest request, HttpServletResponse response) {

		JSONObject jObj = new JSONObject();

		try {
			service.doService(request, response);
			HttpSession session = request.getSession(false);
			MemberVO m = (MemberVO) session.getAttribute("userInfo");
			if (m.getEmail().equals("admin@surveypro.com")) {
				jObj.put("errno", 2);
				jObj.put("message", "관리자 모드로 로그인이 완료되었습니다.\n 관리자 모드 페이지로 이동합니다.");
			} else {
				jObj.put("errno", 0);
				jObj.put("message", "로그인이 완료되었습니다");
			}
		} catch (Exception e) {
			// 이메일란, 비밀번호란이 비어있거나
			// 이메일이 존재하지 않거나
			// 비밀번호가 일치하지 않는 경우
			jObj.put("errno", 1);
			jObj.put("message", e.getMessage());
		}

		PrintWriter out = null;
		try {
			response.setCharacterEncoding("UTF-8");
			response.setContentType("application/json");
			out = response.getWriter();
			out.println(jObj.toJSONString());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}