<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script src="../script/jquery-3.5.0.min.js"></script>
<script src="../script/responseSurvey.js"></script>
<link rel="stylesheet" href="../css/responseSurvey.css">
</head>
<body>	

<div class="surwrap">
	<div class="sTop">
		<ul>
			<li><button type="button" id="btnReport">설문 신고하기</button></li>
			<li><button type="button" id="btnSubmitReport">신고 제출</button><input type="text" id="reportText" placeholder="     신고 사유 입력란"></li>
		</ul>
		
	</div>
	<div class="sMid">
		<div class="questionList">
		<!--  
				<ul id="choiceQ" data-qType="S">
					<li>질문] 머머머머ㅓ머머머머</li>
					<li><textarea id="sTypeRe"></textarea></li>
				</ul>
				<ul id="choiceQ" data-qType="S">
					<li>질문]  머머머머머머머멈머머</li>
					<li><textarea id="sTypeRe"></textarea></li>
				</ul>
				<ul id="subjectiveQ" data-qType="C">
					<li>질문]  머머머머머머머멈머머</li>
					<li><label><input type="radio" name="choice2"> 좋아요</label></li>
					<li><label><input type="radio" name="choice2" > 보통이에요</label></li>
					<li><label><input type="radio" name="choice2" > 별로에요</label></li>
					<li><label><input type="radio" name="choice2" > 더별로에요</label></li>
				</ul>
				<ul id="choiceQ" data-qType="S">
					<li>질문]  머머머머머머머멈머머</li>
					<li><textarea id="sTypeRe"></textarea></li>
				</ul>
				<ul id="subjectiveQ" data-qType="C">
					<li>질문]  머머머머머머머멈머머</li>
					<li><label><input type="radio" name="choice2"> 좋아요</label></li>
					<li><label><input type="radio" name="choice2" > 보통이에요</label></li>
					<li><label><input type="radio" name="choice2" > 별로에요</label></li>
					<li><label><input type="radio" name="choice2" > 더별로에요</label></li>
				</ul>
				<ul id="subjectiveQ" data-qType="C">
					<li>질문]  머머머머머머머멈머머</li>
					<li><label><input type="radio" name="choice1"> 좋아요</label></li>
					<li><label><input type="radio" name="choice1" > 보통이에요</label></li>
					<li><label><input type="radio" name="choice1" > 별로에요</label></li>
					<li><label><input type="radio" name="choice1" > 더별로에요</label></li>
					<li><label><input type="radio" name="choice1" > 더더별로에요</label></li>
				</ul>
				-->
		</div>
	</div>
	<div class="sBottom">
		<button type="submit" id="surBtnReply">응답 제출</button>
		<button type="button" id="surBtnCancel" onclick="history.back(-1)">응답 취소</button>
	</div>
</div>

</body>
</html>