ofxTLGlitch
===========

ofxTLGlitch is a openframeworks addon. This addon make it easy to glitch your movie and image as you like. The concept of this library is easy to use and play. So you can glitch any given frame of your favorite movie in advance, because of timeline based. 

## Demo

### <a href="http://vimeo.com/40434954">View on Vimeo</a>

If you are interested, I hope that you try ofxTLGlitch using your favorite movie. Have a good time!

<img src="https://github.com/after12am/ofxTLGlitch/blob/master/emptyExample/bin/screenshot1.jpg" width="100%" />

## Usage

method for glitching your video.

```
void testApp::setup() {
    glitch.loadVideo('/path/to/video');
}
```

method for glitching your image.

```
void testApp::setup() {
    glitch.loadImage('/path/to/image', duration);
}
```

## License

Copyright (c) 2012-2016 Satoshi Okami. See the LICENSE file for license rights and limitations (MIT).
