SELECT
		nick writer, 
		s_title, 
		interest_count, 
		DATE(writtendate) written_date, 
		DATE(end_date) end_date,
		sub1.s_code s_code
FROM (SELECT 
				A.s_code, 
				C.nick, 
				A.s_title, 
				A.writtendate, 
				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,
				A.s_public,
				D.g_sample_num, 
				D.g_deadline
		FROM survey A, members C, grades D 
		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 
		LEFT JOIN 
	  (SELECT 
	  			s_code, 
				COUNT(s_code) interest_count 
		FROM interests 
		GROUP BY s_code) sub2 
	   ON (sub1.s_code = sub2.s_code)
	   	LEFT JOIN
		(SELECT 
			s_code, COUNT(s_code)/2 sample_num
		FROM
			pointhistory
		GROUP BY
			s_code) sub3 ON (sub1.s_code = sub3.s_code)
WHERE
	g_sample_num - IFNULL(sample_num, 0) != 0 
	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())
ORDER BY
	TIMESTAMPDIFF(DAY, NOW(), end_date) ASC
LIMIT 
	10;
	



	

	

	