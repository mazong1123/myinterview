package com.ime.inerview.jdbc;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

/**
 * 处理注册页面请求的Servlet类
 * @author Jingyu Ma
 *
 */
public class RegisterServlet extends AuthServlet {

	/**
	 * Servlet需要的默认version uid.
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * Get 请求处理。注册时的逻辑。
	 */
	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		super.doGet(request, response);
		request.getRequestDispatcher("register.jsp").forward(request, response);
	}
	
	/**
	 * Post 请求处理。注册时的逻辑。
	 */
	@Override
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		super.doPost(request, response);

		PrintWriter writer = response.getWriter();

		// 检查传入的账户
		String account = request.getParameter("account");
		if (account == null || account.isEmpty()) {
			writer.write("账户不能为空");
			writer.flush();

			return;
		}

		// 检查传入的密码
		String password = request.getParameter("password");
		if (password == null || password.isEmpty()) {
			writer.write("密码不能为空");
			writer.flush();

			return;
		}
		
		// 检查传入的重复密码
		String passwordRepeat = request.getParameter("passwordRepeat");
		if (password == null || password.isEmpty()) {
			writer.write("再次输入的密码不能为空");
			writer.flush();

			return;
		}
		
		// 检查密码一致性
		if (!password.equals(passwordRepeat)){
			writer.write("两次密码输入不一致");
			writer.flush();

			return;
		}
		
		String description = request.getParameter("description");

		DataSource dataSource = this.getDataSource();
		if (dataSource == null) {
			System.err.println("dataSource为空，请检查配置文件。");
			throw new ServletException("网站出问题啦，请稍后再试。");
		}

		/***********************以下是数据库请求操作********************/
		ResultSet resultSet = null;
		Connection connection = null;
		PreparedStatement queryUserByAccountStatement = null;
		PreparedStatement createUserStatement = null;
		PreparedStatement insertLogStatement = null;
		try {
			// 从tomcat连接池中获取一个连接
			connection = dataSource.getConnection();

			// 根据账户查询用户的语句。
			String query = "SELECT 1 FROM t_user WHERE account = ?";

			// 从连接中创建statement
			// 用Preparedstatement防止SQL Injection.
			queryUserByAccountStatement = connection.prepareStatement(query);
			queryUserByAccountStatement.setString(1, account);

			resultSet = queryUserByAccountStatement.executeQuery();

			// 检查是否找到用户记录
			if (resultSet.next()) {
				writer.write("账号已存在，请换个账号");
				writer.flush();

				return;
			}
			
			// 没有相同的账户，开始做插入数据的准备。
			// MD5 加密密码
			String encryptedPassword = this.md5Encrypt(password);
			
			// 准备新建用户SQL语句。
			String createUserQuery = "INSERT INTO t_user(account, password, desp) VALUES(?, ?, ?)";
			createUserStatement = connection.prepareStatement(createUserQuery);
			createUserStatement.setString(1, account);
			createUserStatement.setString(2, encryptedPassword);
			createUserStatement.setString(3, description);
			
			// 准备新插入日志的SQL语句。
			String insertLogQuery = "INSERT INTO t_log(modify_date, description) VALUES(?, ?)";
			insertLogStatement = connection.prepareStatement(insertLogQuery);
			
			java.util.Date date = new java.util.Date();
			insertLogStatement.setTimestamp(1, new java.sql.Timestamp(date.getTime()));
			insertLogStatement.setString(2, account + "注册成功");
			
			// 防止自动提交，以便多条插入语句在一个事务中提交。
			connection.setAutoCommit(false);
			
			try{
				// 创建用户
				createUserStatement.executeUpdate();
				
				// 插入日志
				insertLogStatement.executeUpdate();
				
				connection.commit();
			}
			catch(SQLException ex)
			{
				// 由于是插入操作，如果出现Exception，需要回滚数据库。
				connection.rollback();
				
				// 不吃掉Exception，继续向上抛出。
				throw ex;
			}

			// 告诉用户注册成功。
			writer.write("注册成功");
			writer.flush();
		} catch (SQLException e) {
			// SQL Exception
			// 不抛向最终页面，而是作为系统错误输出到控制台。不过实际应用中是可以抛出去的，因为可以设置不向用户展示错误详情
			System.err.println(e.getMessage());
			e.printStackTrace();
		} finally {
			// 释放所有数据库资源。
			try {
				if (resultSet != null) {
					resultSet.close();
				}

				if (queryUserByAccountStatement != null) {
					queryUserByAccountStatement.close();
				}

				if (connection != null) {
					connection.close();
				}
			} catch (SQLException e) {
				// SQL Exception
				// 不抛向最终页面，而是作为系统错误输出到控制台。不过实际应用中是可以抛出去的，因为可以设置不向用户展示错误详情
				System.err.println(e.getMessage());
				e.printStackTrace();
			}
		} // finally block结束
	}
	
	/**
	 * md5加密
	 * @param source 需要加密的字符串
	 * @return　md5加密后的字符串
	 */
	private String md5Encrypt(String source){
		String encrypted = source;
		
		// TODO: 时间所限，没有实现。所以数据库里面存的是明文密码，实际应用中需要实现md5编码防止数据库灾难后密码泄露(参见csdn事件)。
		
		return encrypted;
	}
}
