/*
 *  ofxSubtitles.h
 *  Colaborama
 *
 *  Created by Patricio González Vivo on 22/10/10.
 *  Copyright 2010 PatricioGonzalezVivo.com. All rights reserved.
 *
 */
#ifndef _ofxSUBTITLES
#define _ofxSUBTITLES

#include "ofMain.h"

#include <iomanip>
#include <strstream>

#include <iostream>
#include <fstream>
#include <vector>

//using namespace std; 

/*typedef struct {
	float	inSec;
	float	outSec;
	string	text;
}subTitle;*/

class subTitle{
public:
    subTitle(){
        inSec=0;
        outSec=0;
        text="";
    }
    string getText();
    
    float inSec;
    float outSec;
    string text;
};

class ofxSubtitles{
public:
    
	vector<subTitle>	subtitles;

	ofxSubtitles();
    ~ofxSubtitles();
	
	void		load(const string& filePath);
	void		save(const string& filePath);
		
	void		add(float inSec, string text);
	void		add(float inSec, float outSec, string text);
	
	int			getHowMany(float _fromSec, float _untilSec);
	int			getFirstSubN(float _fromSec );
	string		getLineAt(float _inSec){subTitle s = getSubTitleAt(_inSec); return s.getText(); };
	subTitle	getSubTitleAt(float _inSec);
	
	bool		isStringAt(string search, float sec);
	
	void		replace(string searchString, string replaceFor, float sec);
	
	ofTrueTypeFont	* font;
	void		loadfont(const string& fontPath);//{font.loadFont(fontPath,13,true,true,true);};
    void        linkFont(ofTrueTypeFont * _font);
	bool        bFontLinked;
    
	int			screenWidth, screenHeight;
	void		setScreen(int width, int height){screenWidth = width; screenHeight = height; };
	
	ofColor		color;
	void		setColor(int r, int g, int b){color.r = r; color.g = g; color.b = b;};
	void		setColor(int r, int g, int b, int a){color.r = r; color.g = g; color.b = b; color.a = a;};
	
	void		draw(float inSec){draw(0,0,screenWidth,screenHeight,inSec);};
	void		draw(int x, int y, float inSec){draw(x,y,screenWidth,screenHeight,inSec);};
	void		draw(int x, int y, int w, int h, float inSec);
    
    float getTotSecs();
    
    //auto
    void initAuto();
    void setWaiting();
    void setCurText();
    
    void setTime(float now);
    string getAutoText();
    
    struct AutoSubtitle{
        string curTxt = "";
        float nextTime = 0;
        int curSub = -1;
        bool isNextNext = true;
    } autoSub;
    //---
    
    //tags
    struct StaticTag{
        StaticTag(string _tag, string _string){
            make(_tag,_string);
        }
        void make(string _tag, string _string){
            idx.clear();
            originals.clear();
            tagName=_tag;
            changeTo=_string;
        }
        string tagName = "tag";
        string changeTo= "";
        vector<string> originals;
        vector<int> idx;
    };
    
    void applyTags(vector<StaticTag> & tags, float fromSec=0, float toSec=-1);
    bool applyTag(StaticTag & tag, int subIdx);
    bool applyTag(StaticTag & tag, string & _txt);
    void applyTagFromIdx(StaticTag & tag);
    void applyTagsFromIdx(vector<StaticTag> & tags);
    //---
};
#endif 
