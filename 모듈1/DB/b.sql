SELECT
	   sub1.s_code s_code,
		nick writer,
		s_title, 
		sub4.c_desc,
		CAST(g_sample_num - IFNULL(sample_num, 0) AS SIGNED INTEGER) spare_sample_num,
		((IFNULL(sample_num, 0) * 2) + interest_count) price
FROM (SELECT 
				A.s_code, 
				C.nick, 
				A.s_title, 
				A.writtendate,
				A.c_code,
				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,
				D.g_sample_num,
				A.s_public,
				D.g_deadline
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
			s_code, 
			COUNT(s_code) sample_num
		FROM pointhistory
		WHERE ph_type='P'
		GROUP BY s_code) sub3 ON (sub1.s_code = sub3.s_code)
		LEFT JOIN
		(SELECT
			c_code,
			c_desc
		FROM categories) sub4 ON (sub1.c_code = sub4.c_code)
WHERE
		sub1.s_public = 'Y' 
		AND (g_sample_num - IFNULL(sample_num, 0) = 0
		OR DATE(NOW()) >= DATE(end_date));




		