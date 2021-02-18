$(document).ready(function(){

	$('.login #signIn').bindLogin();
	$('.myPage #logOut').bindLogout();
	$('.myPage #btnWithdraw').bindWithdraw();
	$('.cpwrap #btnChange').bindChangePass();
	
	
	$('.wrap>.top>#menu>ul>li:nth-child(2)>ul>li:first-child').click(function(){
		location.href = "siteInfo.jsp"
	})
	
	$('.wrap>.top>#menu>ul>li:nth-child(2)>ul>li:last-child').click(function(){
		location.href = "siteRule.jsp"
	})
	
	$('.wrap>.top>#menu>ul>li:last-child>ul>li:first-child').click(function(){
		$.ajax({
			url:'../MemberLoginCheck.do',
			type:'get',
			success:function(data){
				if(data.result){
					location.href = "surveyForm.jsp";
				}
				else{
					alert(data.message);
				}
			}
		})
	})
	
	$('.wrap>.top>#menu>ul>li:last-child>ul>li:last-child').click(function(){
		$.ajax({
			url:'../MemberLoginCheck.do',
			type:'get',
			success:function(data){
				if(data.result){
					location.href = "enterSurvey.jsp";
				}
				else{
					alert(data.message);
				}
			}
		})
	})
	
	$(".wrap>.top>#logo").click(function(){
		location.href="index.jsp";
	})
	
})


