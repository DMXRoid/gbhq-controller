

class SDController {
	public:
		SDController();
		void init();
		void read(char*);

	private:
		uint8_t cardType;
		bool initialized;

};

void initSD();