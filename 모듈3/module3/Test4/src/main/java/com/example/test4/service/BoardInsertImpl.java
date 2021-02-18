package com.example.test4.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import com.example.test4.dao.BoardDao;
import com.example.test4.vo.BoardCommand;
import com.example.test4.vo.BoardVo;

@Service("boardInsert")
public class BoardInsertImpl implements BoardInsert {

	@Autowired
	@Qualifier("boardDao")
	private BoardDao dao;

	@Override
	public void execute(BoardCommand cmd) throws Exception {
		BoardVo board = new BoardVo();
		board.setEmail(cmd.getEmail());
		board.setTitle(cmd.getTitle());
		board.setContent(cmd.getContent());
		int m_id = dao.getNextMainId();
		board.setM_id(m_id);
		dao.insert(board);
	}
}
