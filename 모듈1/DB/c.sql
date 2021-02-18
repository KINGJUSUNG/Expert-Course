SELECT
		sub1.s_code s_code,
		nick writer, 
		s_title, 
		interest_count, 
		DATE(writtendate) written_date,
		((IFNULL(sample_num, 0) * 2) + interest_count) price
FROM (SELECT 
				A.s_code, 
				C.nick, 
				A.s_title, 
				A.writtendate,
				D.g_sample_num,
				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,
				A.s_public
		FROM survey A, members C, grades D 
		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 
		LEFT JOIN 
	  (SELECT 
	  			s_code, 
				COUNT(s_code) interest_count
		FROM interests 
		GROUP BY s_code) sub2 ON (sub1.s_code = sub2.s_code)
		LEFT JOIN
		(SELECT 
			s_code, COUNT(s_code)/2 sample_num
		FROM
			pointhistory
		GROUP BY
			s_code) sub3 ON (sub1.s_code = sub3.s_code)
WHERE 
		sub1.s_public = 'Y' 
		AND (g_sample_num - IFNULL(sample_num, 0) = 0
		OR DATE(NOW()) >= DATE(end_date));

		
		