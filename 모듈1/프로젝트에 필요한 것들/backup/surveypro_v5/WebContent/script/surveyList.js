function showList() {
	
	$.ajax({
		url: '../SurveyGetSurveyInfo.do',
		type: 'post', 
		data: {
			msg: 'deadLine'
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			for (let i = 0; i < data.list.length; i++) {
				let sInfo = data.list[i];
				let obj = 
					$('<ul>' +
					'<li>' + sInfo.writer + '</li>' +
					'<li>' + sInfo.s_title + '</li>' +
					'<li>' + sInfo.interest_count + '</li>' +
					'<li>' + sInfo.written_date + '</li>' +
					'<li>' + sInfo.end_date + '</li>' +							
					'</ul>');
				
				$(obj).data('s_code', sInfo.s_code);
				$(obj).data('respondent', sInfo.respondent);
				$(obj).bindListClick();
				$(obj).appendTo('.deadLineCon');
			}
		}
	});

	$.ajax({
		url: '../SurveyGetSurveyInfo.do',
		type: 'post', 
		data: {
			msg: 'spareSampleNum'
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			for (let i = 0; i < data.list.length; i++) {
				let sInfo = data.list[i];
				let obj = 
					$('<ul>' +
					'<li>' + sInfo.writer + '</li>' +
					'<li>' + sInfo.s_title + '</li>' +
					'<li>' + sInfo.interest_count + '</li>' +
					'<li>' + sInfo.written_date + '</li>' +
					'<li>' + sInfo.spare_sample_num + '</li>' +							
					'</ul>');
				
				$(obj).data('s_code', sInfo.s_code);
				$(obj).data('respondent', sInfo.respondent);
				$(obj).bindListClick();	
				$(obj).appendTo('.lowSampleCon');
			}
		}
	});

	$.ajax({
		url: '../SurveyGetSurveyInfo.do',
		type: 'post', 
		data: {
			msg: 'endSurvey'
		},
		success: function(data) {
			if (data.errno != 0) {
				console.log(data.message);
				return;
			}
			for (let i = 0; i < data.list.length; i++) {
				let sInfo = data.list[i];
				let obj = 
					$('<ul>' +
					'<li>' + sInfo.writer + '</li>' +
					'<li>' + sInfo.s_title + '</li>' +
					'<li>' + sInfo.interest_count + '</li>' +
					'<li>' + sInfo.written_date + '</li>' +
					'<li>' + sInfo.price + '</li>' +							
					'</ul>');
				
				$(obj).data('s_code', sInfo.s_code);
				$(obj).data('respondent', sInfo.respondent);
				$(obj).bindListClick();	
				$(obj).appendTo('.closeSurveyCon');
			}
		}
	});
	
}

$.fn.bindListClick = function() {
	this.click(function() {
		let ul = $(this);
		let s_code = ul.data('s_code');
		let respondent = ul.data('respondent');
		location.href = 'responseSurvey.jsp?s_code=' + s_code + '&respondent=' + respondent;
	});
}

$(document).ready(function() {
	showList();
});


	