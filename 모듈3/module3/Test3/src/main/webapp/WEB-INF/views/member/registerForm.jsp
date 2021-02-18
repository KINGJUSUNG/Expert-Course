<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>registerForm</title>
</head>
<body>
<!-- <div style="color: red">${errorMessage}</div> -->
<form:form modelAttribute="info">
	<table>
		<tr>
			<td>메일주소</td>
			<td><input type="text" name="email" value="${info.email}"></td>
			<td><form:errors path="email" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>비밀번호</td>
			<td><input type="password" name="pass" value="${info.pass}"></td>
			<td><form:errors path="pass" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>비밀번호 확인</td>
			<td><input type="password" name="passConfirm" value="${info.passConfirm}"></td>
			<td><form:errors path="passConfirm" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>회원이름</td>
			<td><input type="text" name="nick" value="${info.nick}"></td>
			<td><form:errors path="nick" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>정수테스트값</td>
			<td><input type="text" name="number" value="${info.number}"></td>
			<td><form:errors path="number" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td><button>등록하기</button></td>
		</tr>
	</table>
</form:form>
</body>
</html>