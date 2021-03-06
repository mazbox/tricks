
var graphics = graphics || {
	context: null,
	width:0,
	height:0,
	x: 0,
	y: 0
};

function setColor(r, g, b) {
	graphics.context.fillStyle = "rgb("+r+", "+g+", "+b+")";
}

function background(r, g, b) {
	setColor(r, g, b);
	rect(0,0,graphics.width, graphics.height);
}
function rect(x, y, width, height) {
	graphics.context.fillRect(x, y, width, height);
}
function line(ax, ay, bx, by) {
	//graphics.context.strokeStyle = "1px red solid";
	//graphics.context.stroke();
	//graphics.context.moveTo(ax, ay);
	//graphics.context.lineTo(bx	, by);
}

function drawString(str, x, y) {
	graphics.context.fillText(str, x, y);
}

function rotate(deg) {
	graphics.context.rotate(deg*Math.PI/180.0);
}
function translate(x, y) {
	graphics.context.translate(x, y);
}
function pushMatrix() {
	graphics.context.save();
}
function popMatrix() {
	graphics.context.restore();
}
function map(val, inMin, inMax, outMin, outMax) {
	return outMin + (outMax-outMin)*(val - inMin)/(inMax-inMin);
}


graphics.init = function(place, drawFunc) {
	
	$(place).append('<canvas id="mygraphicscanvas" width="600" height="360"></canvas>');
	var canvas = document.getElementById("mygraphicscanvas");
	graphics.width = $(place).width();
	graphics.height = $(place).height();
	var pos = $("#mygraphicscanvas").offset();
	graphics.x = pos.left;
	graphics.y = pos.top;
	this.context = canvas.getContext("2d");
	this.context.font = '12px monospace';
	setInterval(drawFunc, 1000/30);
};


graphics.Image = Class.extend({
	init: function(path) {
		this.img = new Image();
		this.img.src = path;
	},
	
	draw: function(x, y, width, height) {
		x = x||0;
		y = y||0;
		if(width && height) {
			graphics.context.drawImage(this.img, x, y, width, height);
		} else {
			graphics.context.drawImage(this.img, x, y);
		}
	}
});