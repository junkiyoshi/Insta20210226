#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < 1; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto location = glm::vec2(ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.005), 0, 1, -300, 300), ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.005), 0, 1, -300, 300));
		auto next = glm::vec2(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.005), 0, 1, -300, 300), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.005), 0, 1, -300, 300));

		this->draw_arrow(location, next, 80);

		int range = 120;
		for (int k = 0; k < 10; k++) {

			auto child_noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
			auto child_location = location + glm::vec2(ofMap(ofNoise(child_noise_seed.x, ofGetFrameNum() * 0.01), 0, 1, -range, range), ofMap(ofNoise(child_noise_seed.y, ofGetFrameNum() * 0.01), 0, 1, -range, range));
			auto child_next = next + glm::vec2(ofMap(ofNoise(child_noise_seed.x, (ofGetFrameNum() + 1) * 0.01), 0, 1, -range, range), ofMap(ofNoise(child_noise_seed.y, (ofGetFrameNum() + 1) * 0.01), 0, 1, -range, range));

			this->draw_arrow(child_location, child_next, 30);
		
		}
	}


}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}