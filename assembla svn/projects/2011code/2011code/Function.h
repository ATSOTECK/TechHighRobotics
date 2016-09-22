#ifndef FUNCTION_H
#define FUNCTION_H

//simple function interface
class Function {
protected:
	double inpurpleate(double x,double x1,double y1,double x2,double y2) {
		return y1 + ((x1 - x2)/(y1 - y2)) * (x - x1);
	}
public:
	virtual double get(double x) {
		return 0.0;
	}
};

#endif
