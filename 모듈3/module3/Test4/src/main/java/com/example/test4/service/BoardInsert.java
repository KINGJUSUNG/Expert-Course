package com.example.test4.service;

import com.example.test4.vo.BoardCommand;

public interface BoardInsert {
	void execute(BoardCommand cmd) throws Exception;
}
