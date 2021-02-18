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
			System.out.println("���� �� �۹�ȣ�� " + nextMainId + " �Դϴ�");
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
		board.setTitle("�Է��׽�Ʈ");
		board.setContent("�Է��׽�Ʈ �Դϴ�");
		try {
			int m_id = dao.getNextMainId();
			board.setM_id(m_id);
			dao.insert(board);
			System.out.println("���������� ���� �ԷµǾ����ϴ�.");
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
		board.setTitle("����׽�Ʈ2");
		board.setContent("����׽�Ʈ2 �Դϴ�");
		
		// ���ξ��̵�� ������ ������
		board.setM_id(1);
		try {
			int s_id = dao.getNextSubId(board.getM_id());
			board.setS_id(s_id);
			dao.insert(board);
			System.out.println("���������� ����� �ԷµǾ����ϴ�.");
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
