package com.example.test3.dao;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import com.example.test3.exception.MemberException;
import com.example.test3.service.Login;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations= {
	"file:src/main/webapp/WEB-INF/spring/root-context.xml",
	"file:src/main/webapp/WEB-INF/spring/appServlet/servlet-context.xml"
})
public class LoginTester {

	@Autowired
	@Qualifier("login")
	Login service;

	@Test @Ignore
	public void testLogin() {
		try {
			// service.execute("dlrtls123455@naver.com", "1234", /* HttpSssion 객체 */);
			System.out.println("로그인에 성공하였습니다.");
		}
		catch (MemberException e) {
			System.out.println(e.getMessage());
		}
	}
}
