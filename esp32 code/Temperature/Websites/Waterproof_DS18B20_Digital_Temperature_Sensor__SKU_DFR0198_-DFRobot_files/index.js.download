

function reset(){
	// console.log($(window).width());
	if($(window).width()<1000){
		$("#markdown-content").height($(window).height()-112);
		// 菜单高度
		$(".bs-docs-sidebar").height($(window).height()-140);
		// $(".hidden-xs").hide();

	}else{
		$("#markdown-content").height($(window).height()-60);
		// 菜单高度
		$(".bs-docs-sidebar").height($(window).height()-60-40);
		// $(".hidden-lg").hide();
	}

}

reset();


$(function(){
	$(window).resize(function(){
		reset();
	})

	// 	移动端显示
	 $("#show-bs-docs-sidebar").click(function(){
	 	 $(".bs-docs-sidebar").animate({width:'toggle'},350);
	 	 $("#search-form").animate({width:'toggle'},350);
	 })

	 $(".content,.glyphicon-remove").click(function(){
	 	if($(window).width()<1000){
	 		$(".bs-docs-sidebar").hide();
	 		$("#search-form").hide();

	 	}
	 })

	 // 菜单选中
	 var subject_id= $("#subject_id").val();
	 var currLi;
	 $(".bs-docs-sidebar li").each(function(i,li){
	 	if($(li).attr("id")==subject_id){
	 		currLi = $(li);
	 		return ;
	 	}
	 })
	 console.log(currLi);

	 if(currLi){
		 	// 父级第一个菜单字体加亮
		  currLi.parents("li").each(function(i,li){
		  	 $(li).find("a").eq(0).addClass("bright");
		  })
		  //当前选中
		  currLi.addClass("active_bright");
		  //ul展开
		  currLi.parents("ul").show();
		  currLi.find("ul").eq(0).show();

		  // 菜单滚动到选中位置
		  $(".bs-docs-sidebar").scrollTop(currLi.offset().top - $(".bs-docs-sidebar").offset().top + currLi.scrollTop() );
	 }

	  // 搜索
	  $("#search-form").submit(function(){
	  	 var keyword = $("#search-form").find("input").val();
		   window.location.href="/search/"+keyword;
		   return false;
	  })
	  // 正文h标签导
	  if($(".content-nav").length>0){
	  	  var html ="";
		  $(".markdown-body").find("h1,h2").each(function(i,h){
		  	    var text = $(h).html();
		  	    var id  = "target_"+i;
		  		// $("<a style='display:block'   name='"+id+"'></a>").insertBefore();
		  		$(h).attr("id",id);
		  		html+='<li><a href="#'+id+'">'+text+'</a></li>';

		  })
		  // 标签 active
		   $(".content-nav ul").html(html);
		  // 标签 active 有描点
		  if($(".content-nav ul li").length>0){
		  	 $(".content-nav ul li").click(function(){
		  	 $(".content-nav ul li").removeClass('active');
		  		 $(this).addClass('active');
		 	 })
		  	$('#markdown-content').scrollspy({ target: '#navbar-content' })
		  }else{
		  	 $(".content-nav").hide();
		  	 if($(window).width()>1000) {
		  	 	$("#markdown-content").css({"padding-left":'330px'});
		  	 }
		  }

	  }


	  // $(".bs-docs-sidebar").scrollTop(currLi.offset().top - $(".bs-docs-sidebar").offset().top + currLi.scrollTop() );

})
