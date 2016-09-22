#include "RetroFinder.h"

#define PEG_HEIGHT 1
#define PEG_LENGTH 1
#define TARGET_DISTANCE 1

RetroFinder::RetroFinder(AxisCamera *cam) : CameraObjectFinder(cam) {
	m_targets = NULL;
};

CameraObject *RetroFinder::findObject(ColorImage *image) {
	BinaryImage* t_bin = image->ThresholdRGB(0,15,0,15,235,255); //Good starting values
	delete m_targets;
	m_targets = t_bin->GetOrderedParticleAnalysisReports(); //order particles by size
	delete t_bin;
	if(m_targets->size() == 0)
	{
		return NULL; //if no targets found return null
	}
	
	
	//New Code - uses particle closest to center
	
	ParticleAnalysisReport *t_brep = findCenter();
	
	ParticleAnalysisReport* t_rep1 = new ParticleAnalysisReport;
	ParticleAnalysisReport* t_rep2 = new ParticleAnalysisReport;
	
	findBottomTwo(t_brep->center_mass_x,25,&t_rep1,&t_rep2);
	
	CameraObject* t_best = new CameraObject;
	t_best->xAngle = t_rep2->center_mass_x;
	t_best->yAngle = t_rep2->center_mass_y;
	t_best->size = t_rep2->particleArea;
	t_best->score = t_rep2->particleToImagePercent;
	t_best->dist = getDistance(toAngle(t_rep2->center_mass_y),toAngle(t_rep1->center_mass_y));
	
	return t_best;
}
 float RetroFinder::getDistance(double angle1, double angle2){
	 float t_distance, t_height;
	 t_distance = (tan(angle1)+ TARGET_DISTANCE)/(tan(angle1)-tan(angle2));
	 t_height = (tan(angle1) * PEG_LENGTH + TARGET_DISTANCE)/((tan(angle1)/(tan(angle2)) - 1));
	 if (t_height != PEG_HEIGHT)
		 t_distance = 0;
	 return t_distance;
 }
 
ParticleAnalysisReport* RetroFinder::findCenter() //Find horizontal center
{
	ParticleAnalysisReport *t_brep;
	for(unsigned int a = 0;a < m_targets->size();a++)
	{
		ParticleAnalysisReport* t_rep = &m_targets[0][a];
		if(t_brep != NULL)
		{
			double t_old = abs(t_brep->center_mass_x - width/2);
			double t_new = abs(t_rep->center_mass_x - width/2);
			if(t_new < t_old) t_brep = t_rep;
		}
		else
		{
			t_brep = t_rep;
		}
	}
	return t_brep;
}

//I looked on the internets and they say to use double pointers so there
void RetroFinder::findBottomTwo(int x,int maxError,ParticleAnalysisReport **_rep1,ParticleAnalysisReport **_rep2)
{
	if(m_targets->size() < 2) {
		_rep1 = _rep2 = NULL;
		return;
	}
		
	vector<ParticleAnalysisReport*>* column = new vector<ParticleAnalysisReport*>;
	for(unsigned int i = 0;i < m_targets->size();i++)
	{
		ParticleAnalysisReport* t_rep = &m_targets[0][i];
		if(abs(x - t_rep->center_mass_x) < maxError) {
			column->push_back(t_rep);
		}
	}
	for(unsigned int i = 0;i < column->size();i++)
	{
		ParticleAnalysisReport* t_rep = &m_targets[0][i];
		if(t_rep->center_mass_y < (*_rep1)->center_mass_y)
			*_rep1 = t_rep;
		if(t_rep->center_mass_y > (*_rep1)->center_mass_y && t_rep < *_rep2)
			*_rep2 = t_rep;
	}
}
