<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="javax.servlet.http.HttpSession" %>


<div class='myPage'>
	<ul>
		<li>${userInfo.nick }님 반갑습니다!</li>
		<li>등급 : ${userInfo.g_name}</li>
		<li>보유 포인트 : ${point } <a id="btnMyPoint" href='myPointHistory.jsp?email=${userInfo.email}&point=${point}'>내역보기</a></li>
		<li><button type="button" id="changePass">비밀번호 변경</button>
			<button type="button" id="showList">내 설문 보기</button>
			<button type="button" id="btnWithdraw">회원 탈퇴</button></li>
	</ul>
	<button type="button" id="logOut">로그아웃</button>
</div>
