<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>IME面试 - 注册</title>
</head>
<body>
	<form action="register" method="post">
		<div>
			<input name="account" placeholder="用户名" />
		</div>
		<div>
			<input name="password" type="password" placeholder="密码" />
		</div>
		<div>
			<input name="passwordRepeat" type="password" placeholder="再次输入密码" />
		</div>
		<div>
			<input name="description" placeholder="描述" />
		</div>
		<div>
			<input type="submit" value="注册" /> <a href="login">已有帐号？点击登录</a>
		</div>
	</form>
</body>
</html>