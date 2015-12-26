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
 * 处理登录页面请求的Servlet类
 * @author Jingyu Ma
 *
 */
public class LoginServlet extends AuthServlet {
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
		request.getRequestDispatcher("index.jsp").forward(request, response);
	}
	
	/**
	 * Post请求处理。所有登录处理逻辑在里面。
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

		DataSource dataSource = this.getDataSource();
		if (dataSource == null) {
			System.err.println("dataSource为空，请检查配置文件。");
			throw new ServletException("网站出问题啦，请稍后再试。");
		}

		/***********************以下是数据库请求操作********************/
		ResultSet resultSet = null;
		Connection connection = null;
		PreparedStatement queryUserByAccountStatement = null;
		try {
			// 从tomcat连接池中获取一个连接
			connection = dataSource.getConnection();

			// 根据账户查询用户的语句。
			String query = "SELECT account, password, desp FROM t_user WHERE account = ?";

			// 从连接中创建statement
			// 用Preparedstatement防止SQL Injection.
			queryUserByAccountStatement = connection.prepareStatement(query);
			queryUserByAccountStatement.setString(1, account);

			resultSet = queryUserByAccountStatement.executeQuery();

			// 检查是否找到用户记录
			if (!resultSet.next()) {
				writer.write("账号不存在");
				writer.flush();

				return;
			}
			
			// 比对密码
			String userPasswordFromDatabase = resultSet.getString(2);
			if (!password.equals(userPasswordFromDatabase))
			{
				writer.write("密码不正确");
				writer.flush();

				return;	
			}

			// 用户名和密码验证通过，获取用户信息
			String userDescription = resultSet.getString(3);

			if (resultSet.next()) {
				// 同一用户名不能在数据库中出现多条，如果出现了说明数据异常。
				System.err.printf("账户%s在数据库中有多条记录，数据异常", account);

				throw new ServletException("您的账户异常，不能返回数据");
			}

			// 将用户描述输出到最终页面
			writer.write(userDescription);
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
}
