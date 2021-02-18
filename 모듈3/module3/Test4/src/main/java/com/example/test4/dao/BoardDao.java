package com.example.test4.dao;

import java.util.List;

import com.example.test4.vo.BoardVo;

public interface BoardDao {
	void insert(BoardVo board) throws Exception;
	void delete(int id) throws Exception;
	void edit(BoardVo board) throws Exception;

	BoardVo selectById(int id) throws Exception;
	List<BoardVo> getList() throws Exception;

	int getNextMainId() throws Exception;
	int getNextSubId(int mainId)throws Exception;
}
