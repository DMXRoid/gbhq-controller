class GBHQ;

class GBHQ {
	public:
		GBHQ();
		void loop();
		void pinOn(int);
		void pinOff(int);

	private:
		int pinConfig[8];
		void setupPins();
};

void initGBHQ();
GBHQ* getGBHQController();