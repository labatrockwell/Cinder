#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ciSpacebrew.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Template : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
	void update();
	void draw();
    
    void onMessage( const Spacebrew::Message &msg );
    
    Spacebrew::ConnectionRef spacebrew;
    Color myColor;

};

void Template::onMessage( const Spacebrew::Message &msg)
{
    if (msg.name == "backgroundOn") {
        if (msg.value == "true") {
            myColor = Color(255, 255, 255);
        } else {
            myColor = Color(0, 0, 0);
        }
    }
}

void Template::setup()
{
    
    string host = "sandbox.spacebrew.cc"; // change to localhost to test Spacebrew local server
    string name = "cinder-example";
    string description = "It's amazing";
    
    spacebrew = Spacebrew::Connection::create( this, host, name, description );
    
    spacebrew->addSubscribe("backgroundOn", Spacebrew::TYPE_BOOLEAN);
    spacebrew->addPublish("cinder-mouse", "boolean", "false");
    
    spacebrew->connect();
    
    spacebrew->addListener( &Template::onMessage, this);
    
    myColor = Color(0,0,0);
}

void Template::mouseDown( MouseEvent event )
{
    spacebrew->sendBoolean("cinder-mouse", true);
}

void Template::mouseUp( MouseEvent event )
{
    spacebrew->sendBoolean("cinder-mouse", false);
}

void Template::update()
{
    
}

void Template::draw()
{
	// clear out the window with black
	gl::clear(  myColor  );
}

CINDER_APP_NATIVE( Template, RendererGl )
