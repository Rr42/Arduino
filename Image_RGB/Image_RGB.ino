#include <Adafruit_GFX.h>   
#include <SWTFT.h> 
#include <TouchScreen.h>
#include <SD.h>

#define SD_CS 53     

#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   

#define TS_MINY 275
#define TS_MINX 263
#define TS_MAXY 962
#define TS_MAXX 902

#define PENRADIUS 3
#define MINPRESSURE 100
#define MAXPRESSURE 700

#define BUFFPIXEL 20

SWTFT tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint p;
int B=10,G=11,R=12;
double r=0,g=0,b=0;

void setup()
{
  pinMode(YP, OUTPUT);
  pinMode(YM, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  Serial.begin(9600);

  Serial.println("Initializing RGB LED... ");
  Serial.println("Red...");
  digitalWrite(R,HIGH);
  delay(1000);
  digitalWrite(R,0);
  Serial.println("Green...");
  digitalWrite(G,HIGH);
  delay(1000);
  digitalWrite(G,0);
  Serial.println("Blue...\n");
  digitalWrite(B,HIGH);
  delay(1000);
  digitalWrite(B,0);

  Serial.println("Initializing LCD... ");

  tft.reset();

  uint16_t identifier = tft.readID();
 
  Serial.print(F("Found LCD driver chip ID: "));
  Serial.println(identifier, HEX);
    
  tft.begin(identifier);

  tft.fillScreen(0);

  Serial.print("Hight: ");
  Serial.print(tft.height());
  Serial.print(" ;Width: ");
  Serial.println(tft.width());

  Serial.println("LCD Initialized\n");

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) 
  {
    Serial.println(F("failed!"));
    return;
  }
  else
  {
    Serial.println(" SD Card Found and Initialized\n");    
  }

  Serial.println("Preparing Screen");
  tft.setRotation(0);
  tft.fillScreen(0);
  Serial.println("Screen Ready\n");
  
  Serial.println("Printing Image");
  bmpDraw("pic.bmp", 0, 0);
  Serial.println("Image Printed\n");
}

void loop()
{
  p = ts.getPoint();
  p.y += p.x;
  p.x = p.y-p.x;
  p.y = p.y-p.x;

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = tft.width()-(map(p.x, TS_MAXX, TS_MINX, tft.width(), 0));
    p.y = tft.height()-(map(p.y, TS_MAXY, TS_MINY, tft.height(), 0));
    Serial.println("x: "+ String(p.x) + ";y: " + String(p.y));
    digitalWrite(R,LOW);
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
    rgb("pic.bmp",p.x,p.y);

  }

}

void rgb(char *filename, int x, int y) 
{
  File     bmpFile;
  int      bmpWidth, bmpHeight;   
  uint8_t  bmpDepth;              
  uint32_t bmpImageoffset;        
  uint32_t rowSize;               
  uint8_t  sdbuffer[3*BUFFPIXEL]; 
  uint16_t lcdbuffer[BUFFPIXEL];  
  uint8_t  buffidx = sizeof(sdbuffer);
  boolean  flip    = true;        
  int      w, h, row, col;
  uint32_t pos = 0, startTime = millis();
  int count=0;

  if((x >= tft.width()) || (y >= tft.height())) return;
  
  if ((bmpFile = SD.open(filename)) == NULL) 
  {
    Serial.println(F("File not found"));
    return;
  }

  if(read16(bmpFile) == 0x4D42) 
  { 
    (void)read32(bmpFile);
    (void)read32(bmpFile); 
    
    bmpImageoffset = read32(bmpFile);
    
    (void)read32(bmpFile);
    
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);

    if((x >= bmpWidth) || (y >= bmpHeight)) return;
    
    if(read16(bmpFile) == 1) 
    { 
      bmpDepth = read16(bmpFile);
      
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) 
      {
        rowSize = (bmpWidth * 3 + 3) & ~3;

        if(bmpHeight < 0) 
        {
          bmpHeight = -bmpHeight;
          flip      = false;
        }
        
        w = bmpWidth;
        h = bmpHeight;
       
        for (row=0; row<x+1; row++) 
        { 
          if(flip) 
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { 
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
          }

          for (col=0; col<y+1; col++)
          {
            if (buffidx >= sizeof(sdbuffer)) 
            {
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; 
            }
            
            if(row<x+1 && row>x-1 && col<y+1 && col>y-1)
            {
              b += sdbuffer[buffidx++];
              g += sdbuffer[buffidx++];
              r += sdbuffer[buffidx++];
              count++;
            }

          } 
        } 

        b /=count; b=(int)b;
        g /=count; g=(int)g;
        r /=count; r=(int)r;

        Serial.println("R: " +String(r)+";G: "+String(g)+";B: "+String(b));
        if(!((r+5>g && g+5>r) || (r+5>b &&b+5>r) || (g+5>b && b+5>g)))
        {
          if(r>g && r>b)
          {
            r+=20;
            g-=7;
            b-=7;
          }
          
          if(g>r && g>b)
          {
            r-=7;
            g+=15;
            b-=7;
          }

          if(b>g && b>r)
          {
            r-=7;
            g-=7;
            b+=15;
          }
        } 

        if(b<0)
          b=0;
        if(g<0)
          g=0;
        if(r<0)
          r=0;

        Serial.println("R: " +String(r)+";G: "+String(g)+";B: "+String(b));
        
        analogWrite(R,r);
        analogWrite(G,g);
        analogWrite(B,b);
        r=g=b=0;
      } 
    }
  }
}


// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.
void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
