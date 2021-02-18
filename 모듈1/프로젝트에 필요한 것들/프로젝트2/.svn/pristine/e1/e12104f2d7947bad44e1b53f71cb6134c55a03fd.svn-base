package com.surveypro.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.naming.NamingException;

import com.surveypro.controller.DbManager;
import com.surveypro.vo.SurveyVO;

public class SurveyDAO {

	public static final String KEY = "SurveyDAO";

	public SurveyDAO() {
	}
	
	public SurveyVO getSurvey(int s_code) {
		String sql = "SELECT s_code, s_title, email, c_code FROM survey WHERE s_code=?;";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		SurveyVO survey = new SurveyVO();

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setInt(1, s_code);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				survey.setS_code(rs.getInt("s_code"));
				survey.setS_title(rs.getString("s_title"));
				survey.setEmail(rs.getString("email"));
				survey.setC_code(rs.getString("c_code"));
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
		return survey;
	}
	
	public int getLastS_code() {
		String sql = "SELECT s_code FROM survey ORDER BY s_code DESC LIMIT 1;";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int result = 0;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				result = rs.getInt("s_code");
			} else {
				result = 0;
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
		return result;
	}

	public int getLastS_id(String email) {
		String sql = "SELECT s_id FROM survey WHERE email=? ORDER BY s_code DESC LIMIT 1;";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int result = 0;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				result = rs.getInt("s_id");
			} else {
				result = 0;
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
		return result;
	}

	public boolean insert(SurveyVO survey, int insertID) {
		boolean result = false;

		String email = survey.getEmail();
		String s_title = survey.getS_title();
		String c_code = survey.getC_code();
		String s_public = survey.getS_public();

		String sql = "INSERT INTO survey VALUES(DEFAULT,?,?,?,?,DEFAULT, DEFAULT, ?);";
		Connection con = null;
		PreparedStatement pstmt = null;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			pstmt.setInt(2, insertID);
			pstmt.setString(3, c_code);
			pstmt.setString(4, s_public);
			pstmt.setString(5, s_title);
			result = (pstmt.executeUpdate() > 0);
		} catch (SQLException e) {
			e.printStackTrace();
		} catch (NamingException e) {
			e.printStackTrace();
		} finally {
			DbManager.close(pstmt);
			DbManager.close(con);
		}

		return result;
	}
}
