package com.example.test3.service;

import javax.servlet.http.HttpSession;

import com.example.test3.exception.MemberException;

public interface Login {
	void execute(String email, String pass, HttpSession session) throws MemberException;
}
