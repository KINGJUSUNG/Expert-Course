<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags" prefix="spring" %>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="form" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script src="resources/jquery-3.5.1.min.js"></script>
</head>
<body>
<form:form modelAttribute="info">
	<label for="name">
		이름 : 
		<form:input type="text" path="name"></form:input>
		<form:errors path="name"></form:errors>
	</label><br>
	<label for="age">
		연령 : <form:input type="text" path="age"></form:input>
		<form:errors path="age"></form:errors>
	</label><br>
	<button>등록하기</button>
</form:form>
</body>
</html>