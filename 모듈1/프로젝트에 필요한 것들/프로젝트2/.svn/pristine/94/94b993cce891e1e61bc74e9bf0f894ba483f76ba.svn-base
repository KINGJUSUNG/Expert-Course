var gPage = 1;
$.fn.bindGetByMySurveyType = function(){
	this.click(function(){
		let clicked_myType = $(this).val();
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetMySurveyInfo.do',
			type:'post',
			data:{
				myType: clicked_myType,
				page:gPage,
			},
			success:function(data){
				for(let i = 0; i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
					$('.cateCont').append(obj);
				}
				$('.cateBottom #btnNext').val(clicked_myType);
				$('.cateBottom #btnFirst').val(clicked_myType);
				$('.cateBottom #btnPrev').val(clicked_myType);
				$('.cateBottom #btnLast').val(clicked_myType);
				gPage = data.page;
			}
		})
	})
}

$.fn.bindGetNext = function(){
	this.click(function(){
		$('.cateCont ul').remove();
		$.ajax({
			url:'../SurveyGetMySurveyInfo.do',
			type:'post',
			data:{
				mode:"next",
				myType:$('.cateBottom #btnNext').val(),
				page:gPage
			},
			success:function(data){
				for(let i = 0; i < data.surveys.length; i++){
					let survey = data.surveys[i];
					let obj = $('<ul>' + 
					'<li>' + survey.writer + '</li>' +
					'<li>' + survey.s_title + '</li>' +
					'<li>' + survey.interest_count + '</li>' +
					'<li>' + survey.written_date + '</li>' +
					'</ul>');
					obj.data('survey', survey);
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
			url:'../SurveyGetMySurveyInfo.do',
			type:'post',
			data:{
				mode:"prev",
				myType:$('.cateBottom #btnPrev').val(),
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
			url:'../SurveyGetMySurveyInfo.do',
			type:'get',
			data:{
				mode:"first",
				myType:$('.cateBottom #btnFirst').val()
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
			url:'../SurveyGetMySurveyInfo.do',
			type:'post',
			data:{
				mode:"last",
				myType:$('.cateBottom #btnLast').val()
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
					$('.cateCont').append(obj);
				}
				gPage = data.page;
			}
		})
	})
}