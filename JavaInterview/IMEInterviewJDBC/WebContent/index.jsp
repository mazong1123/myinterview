<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>IME面试 - 登录</title>
</head>
<body>
	<form action="login" method="post">
		<div>
			<input name="account" placeholder="用户名" />
		</div>
		<div>
			<input name="password" type="password" placeholder="密码" />
		</div>
		<div>
			<input type="submit" value="登录" /> <a href="register">没有帐号？点击注册</a>
		</div>
	</form>
</body>
</html>