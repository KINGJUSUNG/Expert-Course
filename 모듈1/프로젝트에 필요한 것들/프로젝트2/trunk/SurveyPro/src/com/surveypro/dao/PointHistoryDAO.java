package com.surveypro.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import javax.naming.NamingException;

import com.surveypro.controller.DbManager;
import com.surveypro.vo.PointHistoryVO;

public class PointHistoryDAO {

	public static final String KEY = "PointHistoryDAO";

	public boolean insertFivePoints(PointHistoryVO phv) {

		String sql = "INSERT INTO pointhistory VALUES(DEFAULT,?,?,5,'P');";
		Connection con = null;
		PreparedStatement pstmt = null;
		boolean result = false;

		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, phv.getEmail());
			pstmt.setInt(2, phv.getS_code());
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

	public static int getPrice(int s_code) {
		String sql = "SELECT price FROM survey WHERE s_code=?";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		int price = 0;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setInt(1, s_code);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				price = rs.getInt(1);
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
		return price;
	}

	public static int getPoint(String email) {
		int point = 0;
		String sql = "SELECT SUM(B.pointchange) AS point" + " FROM members AS A NATURAL JOIN pointhistory AS B"
				+ " WHERE A.email = ?";
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		try {
			con = DbManager.getConnection();
			pstmt = con.prepareStatement(sql);
			pstmt.setString(1, email);
			rs = pstmt.executeQuery();
			if (rs.next()) {
				point = rs.getInt("point");
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
		return point;
	}

	public boolean isBuyable(String email, int s_code) {

		int currentPoint = getPoint(email);
		int surveyPoint = getPrice(s_code);

		boolean result = ((currentPoint - surveyPoint) >= 0);
		return result;
	}
	public ArrayList<PointHistoryVO> getHistoryByEmail(String email) {
		String sql = "SELECT * FROM pointhistory WHERE email='"+email+"'";
		Connection con = null;
		Statement stmt = null;
		ResultSet rs = null;
		ArrayList<PointHistoryVO> list = new ArrayList<>();
		try {
			con = DbManager.getConnection();
			stmt = con.createStatement();
			rs = stmt.executeQuery(sql);
			while(rs.next()) {
				PointHistoryVO ph = new PointHistoryVO();
				ph.setPh_code(rs.getInt("ph_code"));
				ph.setS_code(rs.getInt("s_code"));
				ph.setEmail(rs.getString("email"));
				ph.setPointchange(rs.getInt("pointchange"));
				ph.setPh_type(rs.getString("ph_type"));
				list.add(ph);
			}
		}catch(NamingException e) {
			e.printStackTrace();
		}catch(SQLException e) {
			e.printStackTrace();
		}
		finally {
			DbManager.close(rs);
			DbManager.close(stmt);
			DbManager.close(con);
		}
		return list;
	}
}
