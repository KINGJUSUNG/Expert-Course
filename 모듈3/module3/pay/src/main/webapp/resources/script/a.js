$(document).ready(function() {
	a(10);
});

function a(num) {
	alert(num);
	IMP.init('imp26187900');  // 매장식별번호
	IMP.request_pay({
		pg : 'inicis', 
		pay_method : 'card',
		merchant_uid : 'merchant_' + new Date().getTime(),
		name : '결제테스트',											// 주문번호  
		amount : 100,												// 결제 금액
		buyer_email : 'dlrtls12345@naver.com',						// 주문자 이메일
		buyer_name : '김주성',										// 주문자 명
		buyer_tel : '010-5292-7836',								// 주문자 번호
		buyer_addr : '서울특별시 강남구 삼성동',							// 주문자 주소
		buyer_postcode : '123-456',
		m_redirect_url : 'http://192.168.30.29:8080/dinner41/b'
	}, function(rsp) {
		if (rsp.success) {
			var msg = '결제가 완료되었습니다.' + "\n";
			msg += '고유ID : ' + rsp.imp_uid + "\n";
			msg += '결제 금액 : ' + rsp.paid_amount + "\n";
		    msg += '상점 거래ID : ' + rsp.merchant_uid + "\n";
			msg += '카드 승인번호 : ' + rsp.apply_num + "\n";
		} 
		else {
			var msg = '결제에 실패하였습니다.' + '\n';
			msg += '에러내용 : ' + rsp.error_msg + "\n";
		}
		alert(msg);
	});
}