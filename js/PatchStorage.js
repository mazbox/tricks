

var PatchStorage = Class.extend({
	init: function(localStorageName, containerId, patchDataCallback, patchLoadCallback) {
		this.patchDataCallback = patchDataCallback;
		this.localStorageName = localStorageName;
		this.patchLoadCallback = patchLoadCallback;
		this.containerId = containerId;
		$("#"+this.containerId).html('<select class="patchSelector">'
			+'</select>'
			+'<input type="button" value="save" class="saveButton" />'
			+'<input type="button" value="delete" class="deleteButton" />	'
			+'<br />');
		
		var self = this;
		
		$("#"+this.containerId + " .saveButton").click(function() {
			var p = prompt("Please enter a name for the patch");
			if(p && p!="") {
				var patches = eval(localStorage.patches);
				var patch = self.patchDataCallback();
				patch.name = p;
				patches.push(patch);
				localStorage.patches = JSON.stringify(patches);
				self.reload();
	}
		});
		
		$("#"+this.containerId + " .deleteButton").click(function() {
			if(confirm("Are you sure you want to delete this patch?")) {
				var patches = eval(localStorage.patches);
				patches.splice($("#" + self.containerId + " .patchSelector").val(), 1);
				localStorage.patches = JSON.stringify(patches);
				self.reload();
			}
		});
		
		$("#" + this.containerId + " .patchSelector").change(function() {
			var patchIndex = $("#" + self.containerId + " .patchSelector").val();
			var patch = eval(localStorage.patches)[patchIndex];
			
			// load this object into the patch
			patchLoadCallback(patch);
		});
		
		
		
		this.reload();
	},
	
	reload: function() {
		//alert(localStorage[this.localStorageName]);
		var patches = eval(localStorage[this.localStorageName]);
		$("#" + this.containerId + " .patchSelector").html("");
		for(i = 0; i < patches.length; i++) {
			$("#" + this.containerId + " .patchSelector").append('<option value="'+i+'">'+patches[i].name+'</option>');
		}
	}
	
});

/*

function loadSelectedPatch() {
	var patchIndex = $("#patchSelector").val();
	var patch = eval(localStorage.patches)[patchIndex];
	//alert(patch.name);
}

function serializePatches(patches) {
	var s = "[";
	
	for(i = 0; i < patches.length; i++) {
		if(i!=0) s += ",";
		s += "{";
		s += "'name':'"+patches[i].name+"'";
		s += "}";
		
	}
	s += "]";
	return s;
}
function deleteSelectedPatch() {
	if(confirm("Are you sure you want to delete this patch?")) {
		var patches = eval(localStorage.patches);
		patches.splice($("#patchSelector").val(), 1);
		localStorage.patches = serializePatches(patches);
		reloadPatches();
	}
}
function savePatch() {
	var p = prompt("Please enter a name for the patch");
	if(p && p!="") {
		var patches = eval(localStorage.patches);
		var patch = { "name": p };
		patches.push(patch);
		localStorage.patches = serializePatches(patches);
		//alert(localStorage.patches);
		reloadPatches();
	}
}*/