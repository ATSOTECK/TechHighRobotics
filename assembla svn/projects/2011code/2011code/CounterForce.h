#include "Function.h"
#include "Arm.h"
#include "math.h"

class CounterForce : public Function {
private:
	int num,max; //number,min,and max of force measurements (degrees)
	double spacing;
	double values[5];
public:
	CounterForce() {
		max = MAX_ANGLE;
		num = 5;
		values[0] = -.3;
		values[1] = -.3;
		values[2] = -.3;
		values[3] = -.3;
		values[4] = -.3;
		spacing = (double)max/num;
	}
	double get(double x) {
		/*if(x < 0)x = 0;
		if(x > max)x = max;
		return values[(int)(x/spacing)]*/
		double x1 = floor(x/spacing)*spacing;
		double y1 = values[(int)(x1/spacing)];
		double x2 = ceil(x/spacing)*spacing;
		double y2 = values[(int)(x1/spacing)];
		
		return inpurpleate(x,x1,y1,x2,y2);
		//return 0;
	}
};
