<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>

<div style="margin-bottom:10px">
<table border="1" style="text-align:center">
   <tr height="30">
     <th width="50">번호</th>
     <th width="250">제목</th>
     <th width="100">작성자</th>
     <th width="170">작성일</th>
     <th width="100">조회수</th>
   </tr>
   <c:forEach var="board" items="${boards}" begin="0" end="10" step="1">
     <tr>
       <td>${board.id}</td>
       <td>${board.title}</td>
       <td>${board.email}</td>
       <td>${board.regDate}</td>
       <td>${board.hits}</td>
     <tr>
   </c:forEach>
</table>
<button style="margin: 20px 3px 0px 315px ">이전</button>
<button>다음</button>
</div>
</body>
</html>