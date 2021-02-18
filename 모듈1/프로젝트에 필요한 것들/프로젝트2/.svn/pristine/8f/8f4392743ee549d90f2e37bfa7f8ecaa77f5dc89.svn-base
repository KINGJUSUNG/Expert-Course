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
				jObj.put("message", "������ ���� �α����� �Ϸ�Ǿ����ϴ�.\n ������ ��� �������� �̵��մϴ�.");
			} else {
				jObj.put("errno", 0);
				jObj.put("message", "로그인 성공 하셨습니다.");
			}
		} catch (Exception e) {
			// �̸��϶�, ��й�ȣ���� ����ְų�
			// �̸����� �������� �ʰų�
			// ��й�ȣ�� ��ġ���� �ʴ� ���
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