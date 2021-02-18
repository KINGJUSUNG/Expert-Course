package com.example.test4.dao;

import java.util.List;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.ApplicationContext;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import com.example.test4.vo.BoardVo;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations= {
		"file:src/main/webapp/WEB-INF/spring/root-context.xml",
		"file:src/main/webapp/WEB-INF/spring/appServlet/servlet-context.xml"
})
public class BoardDaoTester {

	@Autowired
	private ApplicationContext ctx;

	@Test @Ignore
	public void testGetNextMainId() {
		BoardDao dao = ctx.getBean(BoardDao.class);
		try {
			int nextMainId = dao.getNextMainId();
			System.out.println("다음 주 글번호는 " + nextMainId + " 입니다");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Test @Ignore
	public void testInsert() {
		BoardDao dao = ctx.getBean(BoardDao.class);
		BoardVo board = new BoardVo();
		board.setEmail("dlrtls12345@naver.com");
		board.setTitle("입력테스트");
		board.setContent("입력테스트 입니다");
		try {
			int m_id = dao.getNextMainId();
			board.setM_id(m_id);
			dao.insert(board);
			System.out.println("정상적으로 글이 입력되었습니다.");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Test @Ignore
	public void testReplyInsert() {
		BoardDao dao = ctx.getBean(BoardDao.class);
		BoardVo board = new BoardVo();
		board.setEmail("dhqpf12345@nate.com");
		board.setTitle("답글테스트2");
		board.setContent("답글테스트2 입니다");
		
		// 메인아이디는 폼에서 가져옴
		board.setM_id(1);
		try {
			int s_id = dao.getNextSubId(board.getM_id());
			board.setS_id(s_id);
			dao.insert(board);
			System.out.println("정상적으로 답글이 입력되었습니다.");
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@Test
	public void select() {
		BoardDao dao = ctx.getBean(BoardDao.class);
		try {
			List<BoardVo> boards = dao.getList();
			for (int i = 0; i < boards.size(); i++) {
				BoardVo board = boards.get(i);
				System.out.println(board.getM_id() + " : " + board.getS_id() + " : " + board.getTitle());
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}
