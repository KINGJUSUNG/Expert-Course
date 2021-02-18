package com.example.test3.interceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.springframework.web.servlet.HandlerInterceptor;

public class SessionCheckInterceptor implements HandlerInterceptor {

	@Override
	public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) {
		HttpSession session = request.getSession(false);
		if (session == null) {
			System.out.println("������ �������� �ʽ��ϴ�");
			return false;
		}
		if (session.getAttribute("loginInfo") == null) {
			System.out.println("������ ���������� ���� ������ �������� �ʽ��ϴ�.");
			return false;
		}
		System.out.println("������ �����մϴ�.");
		return true;
	}
}