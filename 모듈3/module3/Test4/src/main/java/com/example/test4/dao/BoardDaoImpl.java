package com.example.test4.dao;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import com.example.test4.mapper.BoardMapper;
import com.example.test4.vo.BoardVo;

@Repository("boardDao")
public class BoardDaoImpl implements BoardDao {
	
	@Autowired
	private BoardMapper mapper;

	@Override
	public void insert(BoardVo board) throws Exception {
		mapper.insert(board);
	}

	@Override
	public void delete(int id) throws Exception {
		mapper.delete(id);
	}

	@Override
	public void edit(BoardVo board) throws Exception {
		mapper.update(board);
	}

	@Override
	public List<BoardVo> getList() throws Exception {
		return mapper.select();
	}

	@Override
	public BoardVo selectById(int id) throws Exception {
		return mapper.selectById(id);
	}

	@Override
	public int getNextMainId() throws Exception {
		return mapper.nextM_id();
	}

	@Override
	public int getNextSubId(int m_id) throws Exception {
		return mapper.nextS_id(m_id);
	}
}
