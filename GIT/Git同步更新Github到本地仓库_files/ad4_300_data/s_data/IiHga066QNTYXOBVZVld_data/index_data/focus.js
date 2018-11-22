$(function(){
	$(".flash li").each(function(){
		$(".menubox").append("<b></b>")
	});
	$(".menubox").css("z-index","200");
	$(".menubox b").eq(0).addClass("current");
	var p = 0;
	$(".flash li").css({"z-index":1,"opacity":0});

	$(".flash li").eq(0).css({"z-index":100,"opacity":1});
	$(".menubox b").click(
		function(){
			play($(".menubox b").index(this));
	});
	function play(p){
		$(".menubox b").eq(p).addClass("current").siblings().removeClass("current");
		$(".flash li").eq(p).animate({'opacity':1},800).css({'z-index':100}).siblings().animate({'opacity':0},800).css({'z-index':1});
	}

	function autoplay(){
		p = (p>$(".menubox b").length-2)?0:(p+1);
		play(p);
	}
	$(".arrlft").click(function(){
		p = (p>0) ?(p-1):$(".menubox b").length-1;
		play(p);
	});
	$(".arrrgt").click(function(){
		p = (p>$(".menubox b").length-2)?0:(p+1);
		play(p);
	});
	var auto = setInterval(function(){ autoplay(p)},2500);
	
	$(".focuswid").hover(function(){
		$(".arrlft,.arrrgt").fadeIn(300);
	},function(){$(".arrlft,.arrrgt").fadeOut(300);});
	
	$(".menubox").hover(function(){
		$(".flash li").find("p").show();
	});
	$(".flash").hover(function(){
		$(this).find("p").fadeIn();
	},function(){
		$(this).find("p").fadeOut();
	});
	var stop=setInterval(function(){ clearInterval(auto)},25000);
});