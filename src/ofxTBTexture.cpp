//
//  ofxTBTexture.cpp
//
//  Created by ISHII 2bit.
//
//

#include "ofxTBTexture.h"

void ofxTBTexture::draw(const ofPoint ps[4], const ofPoint tps[4], int n) {
    ofTextureData &texData = this->tex.texData;
    
	// Enable alpha channel if has one
	bool blending = ofGetStyle().blendingMode;
	if (texData.glTypeInternal == GL_RGBA && blending == OF_BLENDMODE_DISABLED) {
		ofEnableAlphaBlending();
	}
	
	// make sure we are on unit 0 - we may change this when setting shader samplers
	// before glEnable or else the shader gets confused
	/// ps: maybe if bUsingArbTex is enabled we should use glActiveTextureARB?
	glActiveTexture(GL_TEXTURE0);
	
	// Enable texturing
	glEnable(texData.textureTarget);
	
	// bind the texture
	glBindTexture(texData.textureTarget, (GLuint)texData.textureID);
	
	// -------------------------------------------------
	// complete hack to remove border artifacts.
	// slightly, slightly alters an image, scaling...
	// to remove the border.
	// we need a better solution for this, but
	// to constantly add a 2 pixel border on all uploaded images
	// is insane..
	// -------------------------------------------------
	
	glPushMatrix();
	
    const ofPoint &p1 = ps[0], &p2 = ps[1], &p3 = ps[2], &p4 = ps[3];
    const ofPoint &tp1 = tps[0], &tp2 = tps[1], &tp3 = tps[2], &tp4 = tps[3];
    
	GLfloat tex_coords[] = {
		tps[0].x, tps[0].y,
		tps[1].x, tps[1].y,
		tps[3].x, tps[3].y,
		tps[2].x, tps[2].y,
	};
    
	GLfloat verts[] = {
		ps[0].x, ps[0].y, ps[0].z,
		ps[1].x, ps[1].y, ps[1].z,
		ps[3].x, ps[3].y, ps[3].z,
		ps[2].x, ps[2].y, ps[2].z,
	};
	
    for(int i = 0; i < n; i++) {
        ofPoint t0 = p1 + (p2 - p1) * (float)(i) / n;
        ofPoint t1 = p1 + (p2 - p1) * (float)(i + 1) / n;
        ofPoint b0 = p4 + (p3 - p4) * (float)(i) / n;
        ofPoint b1 = p4 + (p3 - p4) * (float)(i + 1) / n;
        
        ofPoint tt0 = tp1 + (tp2 - tp1) * (float)(i) / n;
        ofPoint tt1 = tp1 + (tp2 - tp1) * (float)(i + 1) / n;
        ofPoint tb0 = tp4 + (tp3 - tp4) * (float)(i) / n;
        ofPoint tb1 = tp4 + (tp3 - tp4) * (float)(i + 1) / n;
        
        for(int j = 0; j < n; j++) {
            ofPoint tq1 = tt0 + (tb0 - tt0) * (float)(j) / n;
            ofPoint tq2 = tt1 + (tb1 - tt1) * (float)(j) / n;
            ofPoint tq3 = tt1 + (tb1 - tt1) * (float)(j + 1) / n;
            ofPoint tq4 = tt0 + (tb0 - tt0) * (float)(j + 1) / n;
            
            GLfloat tex_coords[] = {
                tq1.x, tq1.y,
                tq2.x, tq2.y,
                tq4.x, tq4.y,
                tq3.x, tq3.y,
            };
            
            ofPoint q1 = t0 + (b0 - t0) * (float)(j) / n;
            ofPoint q2 = t1 + (b1 - t1) * (float)(j) / n;
            ofPoint q3 = t1 + (b1 - t1) * (float)(j + 1) / n;
            ofPoint q4 = t0 + (b0 - t0) * (float)(j + 1) / n;
            
            GLfloat verts[] = {
                q1.x, q1.y, q1.z,
                q2.x, q2.y, q2.z,
                q4.x, q4.y, q4.z,
                q3.x, q3.y, q3.z
            };
            
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, verts);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
	
	glPopMatrix();
	glDisable(texData.textureTarget);
	
	// Disable alpha channel if it was disabled
	if (texData.glTypeInternal == GL_RGBA && blending == OF_BLENDMODE_DISABLED) {
		ofDisableAlphaBlending();
	}
}

void ofxTBTexture::draw(const ofPoint ps[4], const ofRectangle &r, int n) {
    ofPoint tps[4];
    
    tps[0].set(r.x, r.y);
    tps[1].set(r.x + r.width, r.y);
    tps[2].set(r.x + r.width, r.y + r.height);
    tps[3].set(r.x, r.y + r.height);
    
    draw(ps, tps, n);
}

void ofxTBTexture::draw(const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofRectangle &r, int n) {
	
    ofPoint ps[4], tps[4];
    
    ps[0] = p1;
    ps[1] = p2;
    ps[2] = p3;
    ps[3] = p4;
    
    tps[0].set(r.x, r.y);
    tps[1].set(r.x + r.width, r.y);
    tps[2].set(r.x + r.width, r.y + r.height);
    tps[3].set(r.x, r.y + r.height);
    
    draw(ps, tps, n);
}

#define DRAW_CIRCLE_RESOLUTION 32

void ofxTBTexture::drawCircle(const ofPoint &center, float radius) {
    ofPoint ps[DRAW_CIRCLE_RESOLUTION + 2];
    ofPoint tps[DRAW_CIRCLE_RESOLUTION + 2];
    ps[0] = center;
    tps[0] = ofPoint(tex.getWidth() / 2, tex.getHeight() / 2);
    float texRad = fminf(tps[0].x, tps[0].y);
    for(int i = 0; i < DRAW_CIRCLE_RESOLUTION + 1; i++) {
        ps[i + 1].set(ps[0].x + cos(2 * i / (float)DRAW_CIRCLE_RESOLUTION * M_PI) * radius,
                      ps[0].y + sin(2 * i / (float)DRAW_CIRCLE_RESOLUTION * M_PI) * radius);
        tps[i + 1].set(tps[0].x + cos(2 * i / (float)DRAW_CIRCLE_RESOLUTION * M_PI) * texRad,
                       tps[0].y + sin(2 * i / (float)DRAW_CIRCLE_RESOLUTION * M_PI) * texRad);
    }
    this->drawTriangleFan(ps, tps, DRAW_CIRCLE_RESOLUTION + 2);
}

void ofxTBTexture::drawTriangleFan(const ofPoint * const ps, const ofPoint * const tps, int vertexNum){
    ofTextureData &texData = tex.texData;
	// Enable alpha channel if has one
	bool blending = ofGetStyle().blendingMode;
	if (texData.glTypeInternal == GL_RGBA && blending == OF_BLENDMODE_DISABLED) {
		ofEnableAlphaBlending();
	}
	
	// make sure we are on unit 0 - we may change this when setting shader samplers
	// before glEnable or else the shader gets confused
	/// ps: maybe if bUsingArbTex is enabled we should use glActiveTextureARB?
	glActiveTexture(GL_TEXTURE0);
	
	// Enable texturing
	glEnable(texData.textureTarget);
	
	// bind the texture
	glBindTexture( texData.textureTarget, (GLuint)texData.textureID );
	
	// -------------------------------------------------
	// complete hack to remove border artifacts.
	// slightly, slightly alters an image, scaling...
	// to remove the border.
	// we need a better solution for this, but
	// to constantly add a 2 pixel border on all uploaded images
	// is insane..
	
	GLfloat offsetw = 0.0f;
	GLfloat offseth = 0.0f;
	
	if (texData.textureTarget == GL_TEXTURE_2D && ofIsTextureEdgeHackEnabled()) {
		offsetw = 1.0f / (texData.tex_w);
		offseth = 1.0f / (texData.tex_h);
	}
	// -------------------------------------------------
	
	glPushMatrix();
	
	GLfloat *tex_coords;
	GLfloat *verts;
	tex_coords = new GLfloat[2 * vertexNum];
	verts = new GLfloat[2 * vertexNum];
	for(int i = 0; i < 2 * vertexNum; i += 2) {
		tex_coords[i] = tps[i / 2].x;
		tex_coords[i + 1] = tps[i / 2].y;
		
		verts[i] = ps[i / 2].x;
		verts[i + 1] = ps[i / 2].y;
	}
	
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer(2, GL_FLOAT, 0, tex_coords );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, verts );
	glDrawArrays( GL_TRIANGLE_FAN, 0, vertexNum );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	
	glPopMatrix();
	glDisable(texData.textureTarget);
	
	// Disable alpha channel if it was disabled
	if (texData.glTypeInternal == GL_RGBA && blending == OF_BLENDMODE_DISABLED) {
		ofDisableAlphaBlending();
	}
}
