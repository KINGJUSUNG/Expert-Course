package com.example.test3.dao;

import com.example.test3.exception.MemberException;
import com.example.test3.vo.MemberVo;

public interface MemberDao {
	void insert(MemberVo member) throws MemberException;
	void delete(String email, String pass) throws MemberException;
	MemberVo login(String email, String pass) throws MemberException;
}
