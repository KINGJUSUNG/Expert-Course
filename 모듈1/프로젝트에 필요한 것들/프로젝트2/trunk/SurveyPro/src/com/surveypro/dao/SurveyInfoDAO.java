package com.surveypro.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.naming.NamingException;

import com.surveypro.controller.DbManager;
import com.surveypro.vo.SurveyInfoVO;

public class SurveyInfoDAO {

	public static final String KEY = "SurveyInfoDAO";

	public SurveyInfoDAO() {
	}

	public ArrayList<SurveyInfoVO> getSurveyInfoByDeadLine() {

		ArrayList<SurveyInfoVO> list = new ArrayList<>();

		String sql = "SELECT \r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date, \r\n" + 
				"		DATE(end_date) end_date,\r\n" + 
				"		sub1.s_code s_code\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate, \r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				A.s_public,\r\n" + 
				"				D.g_sample_num, \r\n" + 
				"				D.g_deadline\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count \r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 \r\n" + 
				"	   ON (sub1.s_code = sub2.s_code)\r\n" + 
				"	   	LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"WHERE\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0) != 0 \r\n" + 
				"	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())\r\n" + 
				"ORDER BY\r\n" + 
				"	TIMESTAMPDIFF(DAY, NOW(), end_date) ASC\r\n" + 
				"LIMIT \r\n" + 
				"	10;";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setS_code(rs.getInt("s_code"));
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				s.setEnd_date(rs.getString("end_date"));
				list.add(s);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}

		return list;
	}

	public ArrayList<SurveyInfoVO> getSurveyInfoBySpareSampleNum() {
		ArrayList<SurveyInfoVO> list = new ArrayList<>();

		String sql = "SELECT\r\n" + 
				"		sub1.s_code s_code,\r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date,\r\n" + 
				"		CAST(g_sample_num - IFNULL(sample_num, 0) AS SIGNED INTEGER) spare_sample_num\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate,\r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				D.g_sample_num,\r\n" + 
				"				A.s_public,\r\n" + 
				"				D.g_deadline\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count\r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 ON (sub1.s_code = sub2.s_code)\r\n" + 
				"		LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"WHERE\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0) != 0\r\n" + 
				"	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())\r\n" + 
				"ORDER BY\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0)\r\n" + 
				"LIMIT\r\n" + 
				"	10;";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setS_code(rs.getInt("s_code"));
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				s.setSpare_sample_num(rs.getString("spare_sample_num"));
				list.add(s);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}

		return list;
	}

	public ArrayList<SurveyInfoVO> getSurveyInfoByEndSurvey() {
		ArrayList<SurveyInfoVO> list = new ArrayList<>();

		String sql = "SELECT\r\n" + 
				"		sub1.s_code s_code,\r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date,\r\n" + 
				"		((IFNULL(sample_num, 0) * 2) + interest_count) price\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate,\r\n" + 
				"				D.g_sample_num,\r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				A.s_public\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count\r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 ON (sub1.s_code = sub2.s_code)\r\n" + 
				"		LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"WHERE \r\n" + 
				"		sub1.s_public = 'Y' \r\n" + 
				"		AND (g_sample_num - IFNULL(sample_num, 0) = 0\r\n" + 
				"		OR DATE(NOW()) >= DATE(end_date));";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setS_code(rs.getInt("s_code"));
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				s.setPrice(rs.getInt("price"));
				list.add(s);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}

		return list;
	}

	public int getTotalCountByCategory(String c_code) {
		String sql = "SELECT COUNT(*) AS CNT FROM survey WHERE c_code =?";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int rowCount = 0;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, c_code);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				rowCount = rs.getInt(1);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return rowCount;
	}

	public ArrayList<SurveyInfoVO> getSurveyByCategory(int page, int pageSize, String c_code) {
		String sql = "SELECT nick writer, s_title, CAST(writtendate AS DATE) written_date, "
				+ "interest_count FROM(SELECT A.s_code, B.nick, A.s_title, A.writtendate, "
				+ "A.s_id FROM survey A, members B WHERE A.email = B.email AND A.c_code=?) "
				+ "sub1 LEFT JOIN (SELECT s_code, COUNT(s_code) interest_count FROM interests "
				+ "GROUP BY s_code) sub2 ON(sub1.s_code = sub2.s_code) ORDER BY s_id ASC ";
		int startPos = ((page - 1) * pageSize < 0) ? 0 : (page - 1) * pageSize;
		sql += "LIMIT " + startPos + ", " + pageSize + " ";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		ArrayList<SurveyInfoVO> surveys = new ArrayList<>();

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, c_code);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setS_title(rs.getString("s_title"));
				s.setWriter(rs.getString("writer"));
				s.setWritten_date(rs.getString("written_date"));
				s.setInterest_count((rs.getString("interest_count") == null) ? 0 : rs.getInt("interest_count"));
				surveys.add(s);
			}
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return surveys;
	}
	
	public int getTotalCountByMySurvey(String email) {
		String sql = "SELECT COUNT(*) AS CNT FROM survey WHERE email=?";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int rowCount = 0;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				rowCount = rs.getInt(1);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return rowCount;
	}
	
	public ArrayList<SurveyInfoVO> getSurveyByMySurvey(int page, int pageSize, String email) {
		String sql = "SELECT \r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date, \r\n" + 
				"		DATE(end_date) end_date\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				A.email,\r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate, \r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				A.s_public,\r\n" + 
				"				D.g_sample_num, \r\n" + 
				"				D.g_deadline\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count \r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 \r\n" + 
				"	   ON (sub1.s_code = sub2.s_code)\r\n" + 
				"	   	LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"WHERE\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0) != 0 \r\n" + 
				"	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())\r\n" + 
				"	AND sub1.email = ?\r\n" + 
				"ORDER BY\r\n" + 
				"	TIMESTAMPDIFF(DAY, NOW(), end_date) ASC\r\n" + 
				"";
		int startPos = ((page - 1) * pageSize < 0) ? 0 : (page - 1) * pageSize;
		sql += "LIMIT " + startPos + ", " + pageSize + " ";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		ArrayList<SurveyInfoVO> surveys = new ArrayList<>();

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				surveys.add(s);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return surveys;
	}
	
	public int getTotalCountByMyInterest(String email) {
		String sql = 
				"SELECT COUNT(*)\r\n" + 
				"FROM interests A, survey B\r\n" + 
				"WHERE A.s_code = B.s_code AND A.email = ?";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int rowCount = 0;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				rowCount = rs.getInt(1);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return rowCount;
	}

	public ArrayList<SurveyInfoVO> getSurveyByMyInterest(int page, int pageSize, String email) {
		String sql = "SELECT \r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date, \r\n" + 
				"		DATE(end_date) end_date\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				A.email,\r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate, \r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				A.s_public,\r\n" + 
				"				D.g_sample_num, \r\n" + 
				"				D.g_deadline\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count\r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 \r\n" + 
				"	   ON (sub1.s_code = sub2.s_code)\r\n" + 
				"	   	LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"		INNER JOIN \r\n" + 
				"		(SELECT\r\n" + 
				"			A.email,\r\n" + 
				"			A.s_code\r\n" + 
				"		FROM \r\n" + 
				"			interests A, survey B\r\n" + 
				"		WHERE\r\n" + 
				"			A.s_code = B.s_code \r\n" + 
				"			AND A.email = ?) sub4 ON (sub4.s_code = sub1.s_code)\r\n" + 
				"WHERE\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0) != 0 \r\n" + 
				"	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())\r\n" + 
				"ORDER BY\r\n" + 
				"	TIMESTAMPDIFF(DAY, NOW(), end_date) ASC ";
		int startPos = ((page - 1) * pageSize < 0) ? 0 : (page - 1) * pageSize;
		sql += "LIMIT " + startPos + ", " + pageSize + " ";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		ArrayList<SurveyInfoVO> surveys = new ArrayList<>();

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				surveys.add(s);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return surveys;
	}

	public int getTotalCountByMyPurchase(String email) {
		String sql = 
				"SELECT COUNT(*)\r\n" + 
				"FROM pointhistory\r\n" + 
				"WHERE email=?\r\n" + 
				"AND ph_type='B'";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int rowCount = 0;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				rowCount = rs.getInt(1);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return rowCount;
	}
	
	public ArrayList<SurveyInfoVO> getSurveyByMyPurchase(int page, int pageSize, String email) {
		String sql = "SELECT \r\n" + 
				"		nick writer, \r\n" + 
				"		s_title, \r\n" + 
				"		interest_count, \r\n" + 
				"		DATE(writtendate) written_date, \r\n" + 
				"		DATE(end_date) end_date\r\n" + 
				"FROM (SELECT \r\n" + 
				"				A.s_code, \r\n" + 
				"				A.email,\r\n" + 
				"				C.nick, \r\n" + 
				"				A.s_title, \r\n" + 
				"				A.writtendate, \r\n" + 
				"				DATE_ADD(A.writtendate, INTERVAL D.g_deadLine DAY) end_date,\r\n" + 
				"				A.s_public,\r\n" + 
				"				D.g_sample_num, \r\n" + 
				"				D.g_deadline\r\n" + 
				"		FROM survey A, members C, grades D \r\n" + 
				"		WHERE A.email = C.email AND C.g_name = D.g_name) sub1 \r\n" + 
				"		LEFT JOIN \r\n" + 
				"	  (SELECT \r\n" + 
				"	  			s_code, \r\n" + 
				"				COUNT(s_code) interest_count\r\n" + 
				"		FROM interests \r\n" + 
				"		GROUP BY s_code) sub2 \r\n" + 
				"	   ON (sub1.s_code = sub2.s_code)\r\n" + 
				"	   	LEFT JOIN\r\n" + 
				"		(SELECT \r\n" + 
				"			s_code, COUNT(s_code)/2 sample_num\r\n" + 
				"		FROM\r\n" + 
				"			pointhistory\r\n" + 
				"		GROUP BY\r\n" + 
				"			s_code) sub3 ON (sub1.s_code = sub3.s_code)\r\n" + 
				"		INNER JOIN \r\n" + 
				"		(SELECT s_code\r\n" + 
				"		FROM pointhistory\r\n" + 
				"		WHERE email=?\r\n" + 
				"				AND ph_type='B') sub4 ON (sub4.s_code = sub1.s_code)\r\n" + 
				"WHERE\r\n" + 
				"	g_sample_num - IFNULL(sample_num, 0) != 0 \r\n" + 
				"	AND DATE(DATE_ADD(sub1.writtendate, INTERVAL sub1.g_deadLine DAY)) > DATE(NOW())\r\n" + 
				"ORDER BY\r\n" + 
				"	TIMESTAMPDIFF(DAY, NOW(), end_date) ASC ";
		int startPos = ((page - 1) * pageSize < 0) ? 0 : (page - 1) * pageSize;
		sql += "LIMIT " + startPos + ", " + pageSize + " ";

		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		ArrayList<SurveyInfoVO> surveys = new ArrayList<>();

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			while (rs.next()) {
				SurveyInfoVO s = new SurveyInfoVO();
				s.setWriter(rs.getString("writer"));
				s.setS_title(rs.getString("s_title"));
				s.setInterest_count(rs.getInt("interest_count"));
				s.setWritten_date(rs.getString("written_date"));
				surveys.add(s);
			}
		} 
		catch (SQLException e) {
			e.printStackTrace();
		} 
		catch (NamingException e) {
			e.printStackTrace();
		} 
		finally {
			DbManager.close(rs);
			DbManager.close(pstmt);
			DbManager.close(con);
		}
		return surveys;
	}
	
}
