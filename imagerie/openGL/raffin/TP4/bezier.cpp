#include "bezier.h"

int Factorial(int x) {
	if(x == 0)
		return 1;
  return (x == 1 ? x : x * Factorial(x - 1));
}

Bezier::Bezier(List* control)
{
	controlPoints = new List();
	for (List::iterator it = control -> begin(); it != control-> end(); ++it) {
		controlPoints->push_back(*it);
	}
}

point3 Bezier::evaluate(float t) const{
	point3 point(0,0,0);
	unsigned int degree = controlPoints->size();
	for(unsigned int i=0; i<degree; ++i){
		point += controlPoints->at(i) * ( 
											( ( Factorial(degree-1) )
											/
											(( Factorial(i) ) * ( Factorial(degree-1-i) ) ) )
											*
											( pow(t,i) )
											*
											( pow( ( 1-t ),( degree-1-i )) )
										);
	}
	return point;
}

List* Bezier::getControlPoints() const{
	return controlPoints;
}

List* Bezier::getPoints(float step) const{
	if(step > 0.5)
		step = 0.5;
	else if(step < 0)
		step = 0.5;

	List* points = new List();

	for(float i=1.0; i>0.0; i-=step){
		points->push_back(evaluate(i));
	}

	return points;
}