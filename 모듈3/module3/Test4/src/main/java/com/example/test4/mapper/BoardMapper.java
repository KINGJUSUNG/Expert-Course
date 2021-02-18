package com.example.test4.mapper;

import java.util.List;

import com.example.test4.vo.BoardVo;
import com.example.test4.vo.SearchVo;

public interface BoardMapper {
	void insert(BoardVo board) throws Exception;
	void update(BoardVo board) throws Exception;
	void delete(int id) throws Exception;
	
	BoardVo selectById(int id) throws Exception;
	List<BoardVo> select() throws Exception;
	
	int nextM_id() throws Exception;
	int nextS_id(int m_id) throws Exception;

	List<BoardVo> searchByTitle(SearchVo search) throws Exception;
}
