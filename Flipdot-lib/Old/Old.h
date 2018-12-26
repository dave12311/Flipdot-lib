class Flipdot{
  public:
    void setBuffer(uint8_t x, uint8_t y, uint8_t state);    //Sets the given pixel in the screen buffer
	void setLetter(uint8_t letter, uint8_t indent = 0);		//Sets the given letter in the buffer
	void setWord(uint8_t *wordPointer, uint8_t speed);

    void writePixel(uint8_t x, uint8_t y, uint8_t state);   //Writes the given pixel to the screen
    void writeBuffer(uint8_t style = 0);                    //Writes the screen buffer to the screen with the given update style [0:down; 1:up; 2:right; 3:left]
    void writeAll(uint8_t state = 0);                       //Writes all pixels to the given state
	
  private:
    void setData(uint8_t x, uint8_t y, uint8_t r, uint8_t c);
};

#endif
