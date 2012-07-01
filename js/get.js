function getParamString() {
	var parts = location.href.split("?");
	if(parts.length>=2) return parts[1];
	else return "";
}

function getParams() {
	var paramStr = getParamString();
	if(paramStr!="") {
		var paramParts = paramStr.split("&");
		var params = {};
		for(var i = 0; i < paramParts.length; i++) {
			var parts = paramParts[i].split("=");
			params[parts[0]] = parts[1];
		}
		return params;
	}
	return {};
}