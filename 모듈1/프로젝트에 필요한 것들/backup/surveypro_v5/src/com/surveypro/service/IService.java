package com.surveypro.service;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public interface IService {
	public void doService(HttpServletRequest request, HttpServletResponse response) throws Exception;
}
