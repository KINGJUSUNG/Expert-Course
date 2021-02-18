package com.example.test3.dao;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import com.example.test3.exception.MemberException;
import com.example.test3.vo.MemberVo;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations= {
	"file:src/main/webapp/WEB-INF/spring/root-context.xml",
	"file:src/main/webapp/WEB-INF/spring/appServlet/servlet-context.xml"
})
public class MemberDaoTester {
	
	@Autowired
	@Qualifier("memberDao")
	MemberDao dao;
	
	@Test @Ignore
	public void testLogin() {
		try {
			MemberVo member = dao.login("abc@naver.com", "1234");
			System.out.println("로그인 성공!");
			System.out.println(member);
		}
		catch (MemberException e) {
			System.out.println(e.getMessage());
		}
	}
	
	@Test @Ignore
	public void testInsert() {
		MemberVo member = new MemberVo("aaa@naver.com", "1234", "kkk", null, null);
		try {
			dao.insert(member);
			System.out.println("회원등록 성공!");
		}
		catch (MemberException e) {
			System.out.println(e.getMessage());
		}
	}
}