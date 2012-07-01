/**
 *  BrightContSatFilter.cpp
 *
 *  Created by Marek Bereza on 12/10/2011.
 */

#include "OutputFilter.h"

tricks::gl::effects::OutputFilter::OutputFilter() {
	brightness = 1;
	contrast = 1;
	saturation = 1;
}

void tricks::gl::effects::OutputFilter::setup() {
	loadShader();

}


void tricks::gl::effects::OutputFilter::draw(ofTexture &tex) {
	shader.begin();
	shader.setUniformTexture("tex", tex, 0);
	shader.setUniform1f("brightness", brightness);
	shader.setUniform1f("contrast", contrast);
	shader.setUniform1f("saturation", saturation);
	tex.draw(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}

void tricks::gl::effects::OutputFilter::loadShader() {
	
	string frag = 

	"uniform sampler2DRect tex;\n"
	"uniform float brightness;\n"
	"uniform float contrast;\n"
	"uniform float saturation;\n"
	
	
	"// For all settings: 1.0 = 100% 0.5=50% 1.5 = 150%\n"
	"vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con)\n"
	"{\n"
	"	// Increase or decrease theese values to adjust r, g and b color channels seperately\n"
	"	const float AvgLumR = 0.5;\n"
	"	const float AvgLumG = 0.5;\n"
	"	const float AvgLumB = 0.5;\n"
		
	"	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);\n"
		
	"	vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);\n"
	"	vec3 brtColor = color * brt;\n"
	"	float intensityf = dot(brtColor, LumCoeff);\n"
	"	vec3 intensity = vec3(intensityf, intensityf, intensityf);\n"
	"	vec3 satColor = mix(intensity, brtColor, sat);\n"
	"	vec3 conColor = mix(AvgLumin, satColor, con);\n"
	"	return conColor;\n"
	"}\n"
	
	
	"void main()\n"
	"{\n"
		
	"	vec4 color = texture2DRect(tex,gl_TexCoord[0].st);\n"
		
		
	"	color.rgb = ContrastSaturationBrightness(color.rgb, brightness, saturation, contrast);\n"
	"	gl_FragColor = color;\n"
	"}\n";
	
	string vert = 
	"void main() {\n"
	"	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
	"	gl_Position = ftransform();\n"
	"} \n";
	
	shader.setupShaderFromSource(GL_VERTEX_SHADER, vert);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
	shader.linkProgram();

}