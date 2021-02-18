<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<style>
.b1 {
	margin-top:10px;
	margin-left:67px;
}
</style>
<body>
<form:form modelAttribute="boardCmd" id="regForm">
	<table>
		<tr>
			<td>이메일</td>
			<td><input type="text" name="email" value="${boardCmd.email}"></td>
			<td><form:errors path="email" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>제목</td>
			<td><input type="text" name="title" value="${boardCmd.title}"></td>
			<td><form:errors path="title" style="color: red"></form:errors></td>
		</tr>
		<tr>
			<td>내용</td>
			<td><textarea name="content" rows="10" cols="23"></textarea></td>
			<td><form:errors path="content" style="color: red"></form:errors></td>
		</tr>
	</table>
</form:form>
<button class="b1" type="submit" form="regForm">등록하기</button>
<button onclick="location.href='./'">뒤로가기</button>
</body>
</html>