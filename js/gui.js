

var gui = gui || {};

gui.Rectangle = Class.extend({
	init: function(x, y, width, height) {
		this.x = x || 0;
		this.y = y || 0;
		this.width = width || 0;
		this.height = height || 0;
	},

	inside: function(x, y) {
		return x>=this.x && y>=this.y && x <= this.x + this.width
		&& y <= this.y + this.height;
	}
});


gui.Control = gui.Rectangle.extend({
	init: function(params) {
		this._super(params.x||0, params.y||0, params.width || 20, params.height || 20);
		this.over = false;
		this.down = false;
		this.name = params.name || "";
		
	},
	
	draw: function() {
		if(this.over) {
			setColor(100,0,0);
		} else {
			setColor(100,100,100);
		}
		rect(this.x, this.y, this.width, this.height);
	},
	
	mousePressed: function(x, y) {
	},
	
	mouseReleased: function(x, y) {
	},
	
	mouseDragged: function(x, y) {
	},
	
	mouseMoved: function(x, y) {
	}
});

gui.values = {};


gui.Toggle = gui.Control.extend({
	init: function(params) {
		this._super(params);
		this.defaultValue = params.defaultValue || false;
		gui.values[this.name] = this.defaultValue;
	},
	draw: function() {
		if(gui.values[this.name]) {
			setColor(200,0,0);
		} else {
			setColor(150, 150,150);
		}
		rect(this.x, this.y, this.width, this.height);
		setColor(0, 0, 0);
		drawString(this.name, this.x, this.y+this.height - 3);
	},
	mouseReleased: function(x,y) {
		gui.values[this.name] = !gui.values[this.name];
	}
});

gui.Segmented = gui.Control.extend({
	init: function(params) {
		this._super(params);
		this.defaultValue = params.defaultValue || false;
		gui.values[this.name] = this.defaultValue || 0;
		this.options = params.options;// || [];
		
	},
	draw: function() {
		/*if(gui.values[this.name]) {
			setColor(200,0,0);
		} else {
			setColor(150, 150,150);
		}
		*/
		var h = this.height/this.options.length;
		for(i = 0; i < this.options.length; i++) {
			if(i==gui.values[this.name]) {
				setColor(200, 0, 0);
			} else {
				setColor(150, 150, 150);
			}
			rect(this.x, this.y + h*i, this.width, h-3);
			setColor(0, 0, 0);
			drawString(this.options[i], this.x, this.y + h*i + h - 5);
		}
//		rect(this.x, this.y, this.width, this.height);
	},
	
	mousePressed: function(x, y) {
		gui.values[this.name] = Math.floor((y - this.y)/(this.height/this.options.length));
	}
	
});

gui.Keyboard = gui.Control.extend({
	
	offset: 0,
	keys: 24,
	currKey: -1,
	noteonCallback: null,
	noteoffCallback: null,
	init: function(params) {
		this._super(params);
		this.noteonCallback = params.noteonCallback || null;
		this.noteoffCallback = params.noteoffCallback || null;
	},
	
	isABlackNote: function(note) {
		note %= 12;
		return (note==1 || note==3 || note==6 || note==8 || note==10);
	},
	
	setColorForNote: function(note) {
		if(this.currNote==note) {
				setColor(200,0,0);
		} else {
			if(this.isABlackNote(note)) {
				setColor(0,0,0);
			} else {
				setColor(255, 255, 255);
			}
		}
	},
	draw: function() {
		var keyWidth = this.width / this.keys;
			
			
		setColor(255,255,255);
		rect(this.x, this.y, this.width, this.height);
		
		for(i = 0; i < this.keys; i++) {
				
				
				
			//if(this.currKey==i+this.offset || this.isABlackNote(i+this.offset)) {
				this.setColorForNote(i+this.offset);
				rect(this.x+i*keyWidth, this.y, keyWidth, this.height);
				setColor(0,0,0);
			//}
				
			rect(this.x+i*keyWidth, this.y, 1, this.height);
		}

	},
	mousePressed: function(x, y) {
		var newNote = this.offset + Math.floor((x-this.x)*this.keys/this.width);
		if(this.currNote!=-1 && this.currNote!=newNote) {
			this.noteoffCallback(this.currNote);
		}
		
		if(this.currNote!=newNote) {
			if(this.noteonCallback!=null) {
				if(this.noteonCallback!=null) this.noteonCallback(newNote);
			}
		}
		this.currNote = newNote;
	},
	mouseDragged: function(x, y) {
		this.mousePressed(x, y);
	},
	mouseReleased: function(x, y) {
		if(this.currNote!=-1) {
			if(this.noteoffCallback!=null) {
				this.noteoffCallback(this.currNote);
			}
		}
		this.currNote = -1;

	}
});

gui.Button = gui.Control.extend({
	init: function(params) {
		this._super(params);
		this.onmousedown = params.onmousedown || function(a) {};
		this.onmouseup = params.onmouseup || function(a) {};
	},
	draw: function() {
		if(this.down) {
			setColor(200, 0, 0);
		} else if(this.over) {
			setColor(150, 150, 150);
		} else {
			setColor(100, 100, 100);
		}
		rect(this.x, this.y, this.width, this.height);
		setColor(0, 0, 0);
		drawString(this.name, this.x, this.y + this.height - 3);
	},
	mousePressed: function(x, y) {
		this.onmousedown(this.name);
	}, 
	mouseReleased: function(x, y) {
		this.onmouseup(this.name);
	}, 
	
});

gui.Slider = gui.Control.extend({
	init: function(params) {
		this._super(params);
//		this.value = 0.2;
		this.defaultValue = params.defaultValue || 0.0;
		gui.values[this.name] = this.defaultValue;
		this.min = params.min||0;
		this.max = params.max||1;
		this.height = params.height || 100;
		
	},
	
	draw: function() {
		if(this.over) {
			setColor(200,200,200);
		} else {
			setColor(150, 150, 150);
		}
		rect(this.x, this.y, this.width, this.height);
		setColor(200, 0, 0);
		
		yy = map(gui.values[this.name], this.min, this.max, this.y+this.height, this.y);
		hh = map(gui.values[this.name], this.min, this.max, 0, this.height);
		rect(this.x, yy, this.width, hh);
		setColor(0, 0, 0);
		pushMatrix();
		translate(this.x, this.y);
		rotate(90);
		drawString(this.name, 3, -3);
		popMatrix();
	},
	
	mousePressed: function(x, y) {
		this.mouseDragged(x, y);
	},
	
	mouseDragged: function(x, y) {
		gui.values[this.name]= map(y, this.y, this.y+this.height, this.max, this.min);
	}
	
});

gui.controls = [];


gui.mouseIsDown = false;


gui.add = function(el) {
	this.controls.push(el);
}
	
gui.init = function(description) {

	if(description) {
		for(i = 0; i < description.length; i++) {
			if(description[i].type=="slider") {
				this.controls.push(new gui.Slider(description[i]));
			} else if(description[i].type=="segmented") {
				this.controls.push(new gui.Segmented(description[i]));
			} else if(description[i].type=="toggle") {
				this.controls.push(new gui.Toggle(description[i]));
			} else if(description[i].type=="button") {
				this.controls.push(new gui.Button(description[i]));
			} else if(description[i].type=="keyboard") {
				this.controls.push(new gui.Keyboard(description[i]));
			}
		}
	}
	var self = this;	
	$(document).mousedown(function(e) {
		self.mouseIsDown = true;
		for(i = 0; i < self.controls.length; i++) {
			self.controls[i].down = self.controls[i].over = self.controls[i].inside(e.pageX-graphics.x, e.pageY-graphics.y);
			if(self.controls[i].down) {
			
				self.controls[i].mousePressed(e.pageX-graphics.x, e.pageY-graphics.y);
			}
		}
	});
	
	$(document).mouseup(function(e) {
		self.mouseIsDown = false;
		for(i = 0; i < self.controls.length; i++) {
			self.controls[i].down = false;
			self.controls[i].over = self.controls[i].inside(e.pageX-graphics.x, e.pageY-graphics.y);
			if(self.controls[i].over) {
				self.controls[i].mouseReleased(e.pageX-graphics.x, e.pageY-graphics.y);
			}
		}
	});
	
	$(document).mousemove(function(e) {
		if(self.mouseIsDown) {
			for(i = 0; i < self.controls.length; i++) {
				self.controls[i].down = self.controls[i].over = self.controls[i].inside(e.pageX-graphics.x, e.pageY-graphics.y);
				if(self.controls[i].down) {
					self.controls[i].mouseDragged(e.pageX-graphics.x, e.pageY-graphics.y);
				}
			}
		} else {
			for(i = 0; i < self.controls.length; i++) {
				self.controls[i].down = false;
				self.controls[i].over = self.controls[i].inside(e.pageX-graphics.x, e.pageY-graphics.y);
				if(self.controls[i].over) {
					self.controls[i].mouseMoved(e.pageX-graphics.x, e.pageY-graphics.y);
				}
			}
		}
	});
}

gui.draw = function() {
	for(kkkk = 0; kkkk < this.controls.length; kkkk++) {
		this.controls[kkkk].draw();
	}
}

