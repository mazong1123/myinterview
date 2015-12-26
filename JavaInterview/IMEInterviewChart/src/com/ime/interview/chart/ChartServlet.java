package com.ime.interview.chart;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * 本类提供报表图形所需数据。
 * @author Jingyu Ma
 *
 */
public class ChartServlet extends HttpServlet {
	/**
	 * Servlet需要的默认version uid.
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * Get 请求获取图形数据。
	 */
	@Override
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// 解决中文乱码
		response.setCharacterEncoding("UTF-8");
		response.setHeader("content-type", "text/html;charset=UTF-8");
		
		// 以json格式输出
		response.setContentType("application/json");
		
		String resultJson = "[ {" 
			+"\"name\" : \"金额\","
			+"\"tooltip\" : {"
				+"\"valueDecimals\" : 1,"
				+ "\"valuePrefix\" : \"￥\""
			+ "},"
			+ "\"data\" : [ [ \"2015/10/1\", 12.18 ], [ \"2015/10/2\", 13.18 ] ],"
			+ "\"title\" : {"
			+	"\"align\" : \"high\","
			+	"\"text\" : \"人民币\","
			+	"\"rotation\" : 0"
			+"},"
			+ "\"min\" : 0"
		+"}, {"
		+"\"name\" : \"提现人数\","
		+"\"tooltip\" : {"
			+"\"valueDecimals\" : 1,"
			+ "\"valuePrefix\" : \"￥\""
		+ "},"
		+ "\"data\" : [ [ \"2015/10/1\", 12.18 ], [ \"2015/10/2\", 13.18 ] ],"
		+ "\"title\" : {"
		+	"\"align\" : \"high\","
		+	"\"text\" : \"人数\","
		+	"\"rotation\" : 0"
		+"},"
		+ "\"min\" : 0"
		+"} ]";
		
		PrintWriter out = response.getWriter();
		
		out.print(resultJson);
		out.flush();
	}
}
