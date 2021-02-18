package com.example.test3.service;

import com.example.test3.command.MemberCommand;
import com.example.test3.exception.MemberException;

public interface MemberInsert {
	void execute(MemberCommand member) throws MemberException;
}
