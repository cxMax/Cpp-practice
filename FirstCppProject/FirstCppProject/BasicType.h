
class BasicType
{
public:
	BasicType();
	~BasicType();

	int convert() {
		bool b = 42; //b = true , if c = 0 , it's false;
		int i = b; // i = 1
		i = 3.14; // i = 3
		double pi = i; //pi = 3.0
		unsigned char c = -1; // c = 255
		signed char c2 = 256; 
		int c = true; // c = 1 , else c = 0;
	
	}
};
