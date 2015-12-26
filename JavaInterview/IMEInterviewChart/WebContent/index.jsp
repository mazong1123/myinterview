<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>IME面试 - 3D Chart</title>
</head>
<body>
	<div id="ime-chart"></div>
	<!-- 可配置的选项可以做很多，根据highchart的文档设置属性就可以了，时间关系我没有弄太多自定义属性，就放了2个 ，当作示例了-->
	<div id="chart-configs">
		<div>
			背景颜色: <input id="chart-bg-color" value="#fff" />
		</div>
		<div>
			是否显示横轴标题: <input id="chart-xaxis-title" type="checkbox" checked="checked" />
		</div>
		<div>
			报表标题: <input id="chart-title" value="IME面试 - 报表" />
		</div>
	</div>
	<script src="jquery.js"></script>
	<script src="highcharts.js"></script>
	<script src="index.js"></script>
</body>
</html>