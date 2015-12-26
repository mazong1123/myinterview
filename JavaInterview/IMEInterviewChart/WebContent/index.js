(function() {
	$(document).ready(function() {
		// 从服务器端获取报表数据。
		$.getJSON("chart").done(function(seriesArray){
			var displayOptions = {
					backgroundColor : 'white', // 背景颜色
					isEnableXAxisLabels: true, //横坐标的字是否显示
					reportType: 'column', // 报表显示样式
					title: 'IME面试 - 报表' // 报表标题
				};

			// 根据默认参数生成报表。
			generateHighChart(seriesArray, displayOptions);
			
			// 监控配置区域所有input类型，一旦有变化，重新生成报表。
			$('#chart-configs input').on('change', function(){
				var backgroundColor = $('#chart-bg-color').val();
				displayOptions.backgroundColor = backgroundColor;
				
				displayOptions.isEnableXAxisLabels = $('#chart-xaxis-title').is(':checked');
				
				displayOptions.title = $('#chart-title').val();
				
				generateHighChart(seriesArray, displayOptions);
			});
		}).fail(function(e){
			alert('获取图报表数据失败');
			console.log(e);
		});
	});

	/**
	 * 生成报表。seriesArray 是节点数据，displayOptions是显示选项
	 */
	var generateHighChart = function(seriesArray, displayOptions) {
		// 横坐标的点。
		var categoriesArray = new Array();

		// 至少需要有一个节点数据，如果没有这里就提示。
		if (seriesArray.length <= 0){
			alert('没有任何报表数据orz');
			
			return;
		}
		
		// 取第一个节点数据来确定横坐标的点。
		var firstSery = seriesArray[0];
		var firstSeryDataLength = firstSery.data.length;
		for (var i = 0; i < firstSeryDataLength; i++) {
			var dateTime = firstSery.data[i][0];
			categoriesArray.push(dateTime);
		}

		var chartOption = {
			chart : {
				type : displayOptions.reportType,
				backgroundColor : displayOptions.backgroundColor
			},
	        title: {
	            text: displayOptions.title
	        },
			yAxis : seriesArray,
			xAxis : {
				categories : categoriesArray,
				title : {
					align : 'high',
					text : '时间'
				},

				labels : {
					enabled : displayOptions.isEnableXAxisLabels
				}
			},
			series : seriesArray
		};

		$('#ime-chart').highcharts(chartOption);
	};
})();