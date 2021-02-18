package com.example.test4.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

import com.example.test4.dao.BoardDao;
import com.example.test4.vo.BoardVo;

@Service("boardList")
public class BoardListImpl implements BoardList {

	@Autowired
	@Qualifier("boardDao")
	private BoardDao dao;

	@Override
	public List<BoardVo> execute() throws Exception {
		return dao.getList();
	}
}
