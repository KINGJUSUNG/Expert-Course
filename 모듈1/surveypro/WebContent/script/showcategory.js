var gPage = 1;
$.fn.bindGetByCategory = function(){
	this.click(function(){
		let clicked_c_code = $(this).val();
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetByCategory.do',
			type:'get',
			data:{
				page:gPage,
				c_code:clicked_c_code
			},
			success:function(data){
				$('#currentCate').empty();
				$('<span>'+clicked_c_code+'</span>').appendTo($('#currentCate'));	
				for(let i = 0 ;i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					obj.data("respondent", data.respondent);
					obj.bindListClick();
					$('.cateCont').append(obj);
				}
				$('.cateBottom #btnNext').val(clicked_c_code);
				$('.cateBottom #btnFirst').val(clicked_c_code);
				$('.cateBottom #btnPrev').val(clicked_c_code);
				$('.cateBottom #btnLast').val(clicked_c_code);
				
				gPage = data.page;
			}
		})
	})
}

$.fn.bindGetNext = function(){
	this.click(function(){
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetByCategory.do',
			type:'get',
			data:{
				mode:"next",
				c_code:$('.cateBottom #btnNext').val(),
				page:gPage
			},
			success:function(data){
				for(let i = 0 ;i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					obj.data("respondent", data.respondent);
					obj.bindListClick();
					$('.cateCont').append(obj);
				}
				gPage = data.page;
			}
		})
	})
}

$.fn.bindGetPrev = function(){
	this.click(function(){
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetByCategory.do',
			type:'get',
			data:{
				mode:"prev",
				c_code:$('.cateBottom #btnPrev').val(),
				page:gPage
			},
			success:function(data){
				for(let i = 0 ;i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					obj.data("respondent", data.respondent);
					obj.bindListClick();
					$('.cateCont').append(obj);
				}
				gPage = data.page;
			}
		})
	})
}

$.fn.bindGetFirst = function(){
	this.click(function(){
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetByCategory.do',
			type:'get',
			data:{
				mode:"first",
				c_code:$('.cateBottom #btnFirst').val()
			},
			success:function(data){
				for(let i = 0 ;i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					obj.data("respondent", data.respondent);
					obj.bindListClick();
					$('.cateCont').append(obj);
				}
				gPage = 1;
			}
		})
	})
}

$.fn.bindGetLast = function(){
	currentPage = 10000;
	this.click(function(){
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetByCategory.do',
			type:'get',
			data:{
				mode:"last",
				c_code:$('.cateBottom #btnLast').val()
			},
			success:function(data){
				for(let i = 0 ;i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					obj.data("respondent", data.respondent);
					obj.bindListClick();
					$('.cateCont').append(obj);
				}
				gPage = data.page;
			}
		})
	})
}

$.fn.bindListClick = function() {
	this.click(function() {
		let ul = $(this);
		let s_code = ul.data('survey').s_code;
		let resp = ul.data('respondent');
		if (resp == null) {
			alert("로그인 시 참여가능합니다.");
			return;
		}
			
		checkResponse(s_code, resp); 
	});
}

function checkResponse(s_code, respondent) {
	$.ajax({
		url: '../SurveyCheckResponse.do',
		type: 'post',
		data: {
			s_code: s_code,
			respondent: respondent
		},
		success: function(data) {
			if (data.errno != 0) {
				alert(data.message);
			}
			else {
				console.log('해당 설문에 참여 가능합니다.');
				location.href = 'responseSurvey.jsp?s_code=' + data.s_code + '&respondent=' + data.resp;
			}
		}
	});
}
