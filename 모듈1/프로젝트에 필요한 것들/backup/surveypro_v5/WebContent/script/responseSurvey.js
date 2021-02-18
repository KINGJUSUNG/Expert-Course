$.fn.bindReportClick = function(){
	this.click(function(){
		if($('.sTop > ul > li:nth-child(4)').css("display")=="none"){
			$('.sTop > ul > li:nth-child(4)').css("display","block");
		}
		else{
			$('.sTop > ul > li:nth-child(4)').css("display","none");
		}
	})
};
$.fn.bindSubmitReport = function(){
	this.click(function(){
		alert("신고 접수가 완료 되었습니다.");
	})
}

function showResponseSurvey(s_code) {
	$.ajax({
		url: '../GetSurvey.do',
		type: 'post',
		data: {
			s_code: s_code
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			
			console.log($('.questionList').data("respondent"));
			console.log($('.questionList').data("s_code"));
			
			let survey = data.survey;
			let s_code = survey.s_code;
		
			let li1 = $('<li>').text('작성자: '+survey.email);
			let li2 = $('<li>').text('카테고리: '+survey.c_code);
			let li3 = $('<li>').text('제목: '+survey.s_title);
		
			$('#btnReport').closest('li').before(li1);
			$('#btnReport').closest('li').after(li2);
			$('#btnSubmitReport').closest('li').after(li3);
			
			showResponseQuestion(s_code);
		}
	});
}

function showResponseQuestion(s_code) {
	$.ajax({
		url: '../GetQuestion.do',
		type: 'post',
		data: {
			s_code: s_code
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			for (let i = 0; i < data.list.length; i++) {
				
				let q = data.list[i];
				let s_code = q.s_code;
				let q_number = q.q_number;
				let q_title = q.q_title;
				let q_type = q.q_type;
				
				let li = $('<li>').text('질문' + q_number + '] ' + q_title);
				
				if (q_type == 'C') {
					let ul = $('<ul data-qType="C"></ul>');
					ul.data("q_number", q_number);
					ul.attr('id', 'choiceQ');
					ul.append(li);
					ul.appendTo($('.questionList'));
					showResponseChoice(s_code, q_number);
				}
				else {
					let ul = $('<ul data-qType="S"></ul>');
					ul.data("q_number", q_number);
					ul.attr('id', 'subjectiveQ');
					let li2 = $('<li>');
					let textarea = $('<textarea>');
					textarea.attr('id', 'sTypeRe');
					li2.append(textarea);
					ul.append(li);
					ul.append(li2);
					ul.appendTo($('.questionList'));
				}
			}
		}
	});
}

function showResponseChoice(s_code, q_number) {
	$.ajax({
		url: '../GetChoice.do',
		type: 'post',
		data: {
			s_code: s_code,
			q_number: q_number
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			let ul = $('.questionList > ul:nth-child(' + q_number + ')');
			for (let i = 0; i < data.list.length; i++) {
				let q = data.list[i];
				let li = $('<li>');
				let label = $('<label><input type="radio" data-num="'+q.choice_num+'" name="choice'+q_number+'"> ' + q.choice_content + '</label>');
				li.append(label);
				ul.append(li);
			}
		}
	});
}


$(document).ready(function(){
	$('.surwrap > .sTop > ul > li > button#btnReport').bindReportClick();
	$('.sTop > ul > li:nth-child(4) > #btnSubmitReport').bindSubmitReport();
	
	var address = unescape(location.href);
	console.log(address);
	var loc_s_code = address.indexOf('s_code', 0);
	var loc_respondent = address.indexOf('respondent', 0);
	var s_code = '';
	var respondent = '';

	if (loc_s_code != -1) {
		tmp1 = address.substring(loc_s_code);
	}
	
	if (loc_respondent != -1) {
		tmp2 = address.substring(loc_respondent);
	}

	var arr1 = tmp1.split('&');
	var arr2 = arr1[0].split('=');
	s_code = arr2[1];
	
	var arr3 = tmp2.split('=');
	respondent = arr3[1];
	$('.questionList').data("respondent", respondent);
	$('.questionList').data("s_code", s_code);
	showResponseSurvey(s_code);
});