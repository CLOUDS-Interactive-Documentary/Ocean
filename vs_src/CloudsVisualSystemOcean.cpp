//
//  CloudsVisualSystemOcean.cpp
//  VSCloudsRezanator
//
//  Created by James George on 5/31/13.
//
//

#include "CloudsVisualSystemOcean.h"

CloudsVisualSystemOcean::CloudsVisualSystemOcean(){
	windSpeed = 32;
    oceanTileSizeX = 200;
    oceanTileSizeY = 200;
	drawOcean = true;
}

string CloudsVisualSystemOcean::getSystemName(){
	return "Ocean";
}

void CloudsVisualSystemOcean::selfSetup(){
	generateOcean();
	
}

void CloudsVisualSystemOcean::generateOcean(){
	ocean.size = ofVec3f(int(oceanTileSizeX), 1.0, int(oceanTileSizeY));
    ocean.windSpeed = windSpeed;
    ocean.setup();
	
	renderer.setup(&ocean, 9, 9);
}

void CloudsVisualSystemOcean::selfSetupGuis(){
	
	oceanGui = new ofxUISuperCanvas("OCEAN", gui);
    oceanGui->copyCanvasStyle(gui);
    oceanGui->copyCanvasProperties(gui);
	
    oceanGui->setName("OceanSettings");
    oceanGui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	
	oceanGui->addSlider("OCEAN SIZE X", 10, 1000, &oceanTileSizeX);
	oceanGui->addSlider("OCEAN SIZE Y", 10, 1000, &oceanTileSizeY);
	oceanGui->addSlider("WIND SPEED Y", 2, 1000, &windSpeed);
	
	oceanGui->addButton("REGENERATE", &shouldRegenerateOcean);
	
	oceanGui->addSlider("WAVE SPEED", 0, 10, &ocean.waveSpeed);
	oceanGui->addSlider("WAVE SCALE", 0, 100.0, &ocean.waveScale);
	oceanGui->addSlider("WAVE CHOPPINESS", 0, 20, &ocean.choppyScale);

	oceanGui->addToggle("USE BUOYANT CAM", &useOceanCam);
	oceanGui->addSlider("BASE WIDTH", 2, 50, &oceanCamera.baseWidth);
	oceanGui->addSlider("LIFT HEIGHT", 0, 100, &oceanCamera.lift);
	
	oceanGui->addLabel("RENDERING");
	oceanGui->addToggle("DRAW POINTS", &drawPoints);
	oceanGui->addSlider("POINT ALPHA", 0, 1.0, &pointAlpha);
	oceanGui->addSlider("POINT SIZE", .5, 4, &pointSize);
	
	oceanGui->addToggle("DRAW WIREFRAME", &drawWireframe);
	oceanGui->addSlider("WIREFRAME ALPHA", 0, 1.0, &wireframeAlpha);
	
	oceanGui->addToggle("DRAW OCEAN", &drawOcean);
	oceanGui->addSlider("OCEAN ALPHA", 0, 1.0, &oceanAlpha);

	oceanGui->addRangeSlider("FOG RANGE", 0, 5000, &fogMinDepth, &fogMaxDepth);
	oceanGui->addSlider("FOG DENSITY", 0, .3, &fogDensity);

	ofAddListener(oceanGui->newGUIEvent, this, &CloudsVisualSystemOcean::selfGuiEvent);
	
    guis.push_back(oceanGui);
    guimap[oceanGui->getName()] = oceanGui;
	
	oceanCamera.ocean = &ocean;
	
	blendMode = OF_BLENDMODE_ALPHA;
	
	reloadShader();

}

void CloudsVisualSystemOcean::selfUpdate(){

	ocean.setFrameNum( ofGetFrameNum() );
	
    ocean.update();
	renderer.update();
	
	oceanCamera.update();
}

void CloudsVisualSystemOcean::selfDrawBackground(){
	
}

void CloudsVisualSystemOcean::selfDrawDebug(){
	
}

void CloudsVisualSystemOcean::selfSceneTransformation(){
	
}

void CloudsVisualSystemOcean::selfDraw(){
//	mat->begin();
	
	if(!useOceanCam){
		oceanCamera.drawDebug();
	}

	glPushAttrib(GL_POINT_BIT | GL_POLYGON_BIT | GL_FOG_BIT);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(pointSize);

	glEnable(GL_FOG);
	glFogi(GL_FOG_COORD_SRC, GL_FOG_COORDINATE);
	glFogf(GL_FOG_START, fogMinDepth);
	glFogf(GL_FOG_END, fogMaxDepth);
	glFogf(GL_FOG_DENSITY, powf(fogDensity,2));

	
	oceanShader.begin();
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255, pointAlpha*255);
	if(drawPoints) renderer.drawVertices();
	
	ofSetColor(255, wireframeAlpha*255);
	if(drawWireframe) renderer.drawWireframe();

	glPolygonOffset(-1, 0);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255, oceanAlpha*255);
	if(drawOcean) renderer.draw();
	
	oceanShader.end();
	
	glPopAttrib();
	
	ofEnableAlphaBlending();
	
//	mat->end();
}

void CloudsVisualSystemOcean::selfExit(){
	
}

void CloudsVisualSystemOcean::selfBegin(){
	
}

void CloudsVisualSystemOcean::selfEnd(){
	
}

void CloudsVisualSystemOcean::selfKeyPressed(ofKeyEventArgs & args){
	if(args.key == 'r'){
		reloadShader();
	}
}

void CloudsVisualSystemOcean::selfKeyReleased(ofKeyEventArgs & args){
	
}

void CloudsVisualSystemOcean::selfMouseDragged(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemOcean::selfMouseMoved(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemOcean::selfMousePressed(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemOcean::selfMouseReleased(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemOcean::selfSetupGui(){
	
}

void CloudsVisualSystemOcean::selfGuiEvent(ofxUIEventArgs &e){
	if(e.widget->getName() == "REGENERATE" && ((ofxUIButton*)e.widget)->getValue() ){
		generateOcean();
	}
	
}

void CloudsVisualSystemOcean::selfSetupSystemGui(){
	
}

void CloudsVisualSystemOcean::guiSystemEvent(ofxUIEventArgs &e){
	
}

void CloudsVisualSystemOcean::reloadShader(){
	
	oceanShader.load(getVisualSystemDataPath() + "shaders/ocean");
}

void CloudsVisualSystemOcean::selfSetupRenderGui(){
	vector<string> modes;
	modes.push_back("alpha");
	modes.push_back("add");
	modes.push_back("screen");
	
	//modes.push_back("sub");
	//modes.push_back("mult");
//	modes.push_back("disable");
	
	//rdrGui->addRadio("blending", modes);


}

void CloudsVisualSystemOcean::guiRenderEvent(ofxUIEventArgs &e){
	
}
