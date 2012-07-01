/**
 *  QuadWarp.cpp
 *
 *  Created by Marek Bereza on 18/10/2011.
 */

#include "ShaderQuadWarp.h"
void tricks::gl::util::ShaderQuadWarp::setup(int width, int height) {
	fbo.allocate(width, height);
	loadShader();
	/*tl = ofVec2f(0, 0);
	bl = ofVec2f(0, 1);
	tr = ofVec2f(1, 0);
	br = ofVec2f(1, 1);*/
}

void tricks::gl::util::ShaderQuadWarp::begin() {
	fbo.begin();
}

void tricks::gl::util::ShaderQuadWarp::end() {
	fbo.end();
	shader.begin();
	shader.setUniformTexture("tex", fbo.getTextureReference(0), 0);
	shader.setUniform2f("BL", bl.x, bl.y);
	shader.setUniform2f("TL", tl.x, tl.y);
	shader.setUniform2f("BR", br.x, br.y);
	shader.setUniform2f("TR", tr.x, tr.y);
	shader.setUniform2f("renderSize", ofGetWidth(), ofGetHeight());
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}


void tricks::gl::util::ShaderQuadWarp::loadShader() {

	 string frag = 
	 
	 "uniform sampler2DRect tex;\n"
	 "varying vec2 texCoord;\n"
	 "void main()\n"
	 "{\n"
	 "	vec4 color = texture2DRect(tex,texCoord);\n"
	 "	gl_FragColor = color;\n"
	 "}\n";
	 
	 string vert = 
	 
	 
	 
	 "uniform vec2 BL, BR, TL, TR;\n"
	 "uniform vec2 renderSize;\n"
	 "varying vec2 texCoord;\n"
	 "void main() {\n"
	 // transform from QC object coords to 0...1
	 //		"vec2 p = (vec2(gl_Vertex.x, gl_Vertex.y) + 1.) * 0.5;\n"
	 "vec2 p = vec2(gl_Vertex.x, gl_Vertex.y)/renderSize;"
	 "p.y = 1.0 - p.y;"
	 // interpolate bottom edge x coordinate
	 "vec2 x1 = mix(BL, BR, p.x);"
	 
	 // interpolate top edge x coordinate
	 "vec2 x2 = mix(TL, TR, p.x);"
	 
	 // interpolate y position
	 "p = mix(x1, x2, p.y);"
	 
	 // transform from 0...1 to QC screen coords
	 "p *= renderSize;"
	 
"	 vec4 tc = gl_ModelViewProjectionMatrix * vec4(p, 0, 1);"
"	texCoord = tc.xy;"
	 "gl_Position 	= gl_ModelViewProjectionMatrix * vec4(p, 0, 1);"
	 "gl_FrontColor	= gl_Color;"
	 "gl_TexCoord[0]	= gl_TextureMatrix[0] * gl_MultiTexCoord0;"
	"texCoord = gl_TexCoord[0].xy;"
	 "}";
	 

	
	/*
	 string frag = 
	 
	 "uniform sampler2DRect tex;\n"
	 "void main()\n"
	 "{\n"
	 "	vec4 color = texture2DRect(tex,gl_TexCoord[0].st);\n"
	 "	gl_FragColor = color;\n"
	 "}\n";
	 
	 string vert = 
	 
	 
	 
	 "uniform vec2 BL, BR, TL, TR;\n"
	 "uniform vec2 renderSize;\n"
	 
	 "void main() {\n"
	 // transform from QC object coords to 0...1
	 //		"vec2 p = (vec2(gl_Vertex.x, gl_Vertex.y) + 1.) * 0.5;\n"
	 "vec2 p = vec2(gl_Vertex.x, gl_Vertex.y)/renderSize;"
	 "p.y = 1.0 - p.y;"
	 // interpolate bottom edge x coordinate
	 "vec2 x1 = mix(BL, BR, p.x);"
	 
	 // interpolate top edge x coordinate
	 "vec2 x2 = mix(TL, TR, p.x);"
	 
	 // interpolate y position
	 "p = mix(x1, x2, p.y);"
	 
	 // transform from 0...1 to QC screen coords
	 "p *= renderSize;"
	 
	 
	 "gl_Position 	= gl_ModelViewProjectionMatrix * vec4(p, 0, 1);"
	 "gl_FrontColor	= gl_Color;"
	 "gl_TexCoord[0]	= gl_TextureMatrix[0] * gl_MultiTexCoord0;"
	 "}";
	 
	 */
	
	/*
	
	 string frag = 
	 
	 "uniform sampler2DRect tex;\n"
	"uniform vec2 BL, BR, TL, TR;\n"
	"uniform vec2 renderSize;\n"
	
	 "void main()\n"
	 "{\n"
	
	// transform from QC object coords to 0...1
	//		"vec2 p = (vec2(gl_Vertex.x, gl_Vertex.y) + 1.) * 0.5;\n"
	"vec2 p = gl_TexCoord[0].st/renderSize;"
	"p.y = 1.0 - p.y;"
	// interpolate bottom edge x coordinate
	"vec2 x1 = mix(BL, BR, p.x);"
	
	// interpolate top edge x coordinate
	"vec2 x2 = mix(TL, TR, p.x);"
	
	// interpolate y position
	"p = mix(x1, x2, p.y);"
	
	// transform from 0...1 to QC screen coords
	"p *= renderSize;"
	
	
	 "	vec4 color = texture2DRect(tex,p);\n"
	 "	gl_FragColor = color;\n"
	 "}\n";
	 
	string vert = 
	"void main() {\n"
	"	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
	"	gl_Position = ftransform();\n"
	"} \n";
	 
	
	*/
	shader.setupShaderFromSource(GL_VERTEX_SHADER, vert);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
	shader.linkProgram();

}