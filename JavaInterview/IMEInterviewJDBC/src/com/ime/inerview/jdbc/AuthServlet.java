package com.ime.inerview.jdbc;

import java.io.IOException;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

/**
 * 注册和登录请求Servlet的基类。原本是想把共有逻辑全部抽象到这个基类，时间关系来不及了。
 * @author Jingyu Ma
 *
 */
public abstract class AuthServlet extends HttpServlet {
	/**
	 * Servlet需要的默认version uid.
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * 修复输出中文到页面时的乱码问题。
	 * 
	 * @param response
	 *            Servlet需要响应用户请求的response
	 */
	private void patchResponseForChinese(HttpServletResponse response) {
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
	}

	/**
	 * 从配置文件中获取一个DataSource 实例。
	 * 
	 * @return DataSource 实例。
	 */
	protected DataSource getDataSource() {
		DataSource dataSource = null;
		try {
			Context initContext = new InitialContext();
			Context envContext = (Context) initContext.lookup("java:/comp/env");
			dataSource = (DataSource) envContext.lookup("jdbc/imedb");
		} catch (NamingException e) {
			e.printStackTrace();
		}

		return dataSource;
	}

	/**
	 * Post 请求处理。包含Auth类型Servlet的基础处理。
	 */
	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		this.patchResponseForChinese(response);
	}
	
	/**
	 * Get 请求处理。包含Auth类型Servlet的基础处理。
	 */
	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		this.patchResponseForChinese(response);
	}
}
