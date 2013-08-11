# ofxTBTexture

extend ofTexture

## How to use

1. Add ofxTBTexture to your project and include ofxTBTexture.h

## API

### ofxTBTexture

* ofxTBTexture() : tex(_tex) {};
* ofxTBTexture(ofTexture &tex) : tex(tex) {}

Example:
	
	ofFbo fbo;
	/* some code for fbo */
	
	ofxTBTexture tex(fbo.getTextureReference());

* ofxTBTexture &operator=(const ofTexture &tex)

Example:

	ofImage image;
	image.loadImage("foo.png");
	
	ofxTBTexture tex;
	tex = img.getTextureReference();

* void draw(const ofPoint ps[4], const ofPoint tps[4], int n = 4);
* void draw(const ofPoint ps[4], const ofRectangle &r, int n = 4);
* void draw(const ofPoint &p1, const ofPoint &p2, const ofPoint &p3, const ofPoint &p4, const ofRectangle &r, int n = 4);

__TODO__

* void drawCircle(const ofPoint &center, float radius);

__TODO__

* void drawTriangleFan(const ofPoint * const ps, const ofPoint * const tps, int vertexNum);

__TODO__

* inline const ofTexture &getRawOfTexture() const;

Get original ofTexture

Example:

	ofFbo fbo;
	/* some code for fbo */
	
	ofxTBTexture tex(fbo.getTextureReference());
	
	ofTexture tex2 = tex.getRawOfTexture();

## Update history

### 2013/08/12 ver 0.01 beta release

## License

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create new issue, if there is a problem.
And please throw pull request, if you have a cool idea!!