#include "Function.h"
#include "math.h"
#include "Arm.h"

class ArmExtrusion : public Function {
public:
	CounterForce() {
	}
	double get(double x) {
		return X1 + LENGTH*sin((x + START_ANGLE) * 3.14159/180);
	}
};
