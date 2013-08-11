//
//  ofxTBTexture.h
//
//  Created by ISHII 2bit.
//
//

#ifndef __ofxTBTexture__
#define __ofxTBTexture__

#include "ofMain.h"
#include "ofTexture.h"

class ofxTBTexture {
public:
    ofxTBTexture() : tex(_tex) {};
    ofxTBTexture(ofTexture &tex) : tex(tex) {}
    
    ofxTBTexture &operator=(const ofTexture &tex) {
        this->tex = tex;
        return *this;
    }
    
    void draw(const ofPoint ps[4], const ofPoint tps[4], int n = 4);
    void draw(const ofPoint ps[4], const ofRectangle &r, int n = 4);
	void draw(const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofRectangle &r, int n = 4);
    void drawCircle(const ofPoint &center, float radius);
    
	void drawTriangleFan(const ofPoint * const ps, const ofPoint * const tps, int vertexNum);
    
    inline const ofTexture &getRawOfTexture() const {
        return tex;
    }
    
    // inherit from ofTexture
    
    inline void draw(const ofPoint & p1, const ofPoint & p2, const ofPoint & p3, const ofPoint & p4)  { tex.draw(p1, p2, p3, p4); }
	inline void draw(float x, float y) { tex.draw(x, y); }
	inline void draw(float x, float y, float z) { tex.draw(x, y, z); }
	inline void draw(float x, float y, float w, float h) { tex.draw(x, y, w, h); }
	inline void draw(float x, float y, float z, float w, float h) { tex.draw(x, y, z, w, h); }
	
	inline void drawSubsection(float x, float y, float w, float h, float sx, float sy) { tex.drawSubsection(x, y, w, h, sx, sy); }
	inline void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy) { tex.drawSubsection(x, y, z, w, h, sx, sy); }
	inline void drawSubsection(float x, float y, float w, float h, float sx, float sy, float sw, float sh) { tex.drawSubsection(x, y, w, h, sx, sy, sw, sh); }
	inline void drawSubsection(float x, float y, float z, float w, float h, float sx, float sy, float sw, float sh) { tex.drawSubsection(x, y, z, w, h, sx, sy, sw, sh); };
    
	inline void readToPixels(ofPixels & pixels) { tex.readToPixels(pixels); }
	inline void readToPixels(ofShortPixels & pixels) { tex.readToPixels(pixels); }
	inline void readToPixels(ofFloatPixels & pixels) { tex.readToPixels(pixels); }
    
	//for the advanced user who wants to draw textures in their own way
	inline void bind() { tex.bind(); }
	inline void unbind() { tex.unbind(); }
private:
    ofTexture &tex;
    ofTexture _tex;
};

#endif /* defined(__ofxTBTexture__) */
