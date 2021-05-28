#pragma once

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Classification.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Point_set_3/IO.h>
#include <CGAL/Real_timer.h>

#include "TrainController.h"

typedef CGAL::Simple_cartesian<double> CKernel;
typedef CKernel::Point_3 CPoint;
typedef CGAL::Point_set_3<CPoint> Point_set;
typedef Kernel::Iso_cuboid_3 Iso_cuboid_3;
typedef Point_set::Point_map PointMap;
typedef Point_set::Property_map<float> Imap;
namespace Classification = CGAL::Classification;

typedef Classification::Label_handle												CLabelHandle;
typedef Classification::Feature_handle												CFeatureHandle;
typedef Classification::Label_set													CLabelSet;
typedef Classification::Feature_set													CFeatureSet;
typedef Classification::Sum_of_weighted_features_classifier							CGALClassifier;
typedef Classification::Point_set_feature_generator<CKernel, Point_set, PointMap>   CFeatureGenerator;

typedef Point_set CPointSet;

class TrainModel {
private:
	TrainController trainController;
	CPointSet pts;
	Imap labelMap;
	CFeatureSet* featureSet;
	CFeatureGenerator* featureGenerator;
	CLabelSet labelSet;
	CGALClassifier* classifier;
	std::vector<int> labelIndices;
	std::map<LabelView*, LabelHandle> mapLabels;
public:
	TrainModel(const TrainController& _trainController);
	TrainModel(const TrainModel& trainModel);
	TrainModel(TrainModel&& trainModel) noexcept;
	TrainModel() = default;
	~TrainModel();
private:
	void initInput();
	void calculateFeatures();
	void createLabels();
	void train();
	void classify();
	void evaluation();
	std::string& getNewFilePath(const std::string& ext);
	void save(const std::string& filePath);
	inline void save();
public:
	void run();
public:
	inline TrainController& getTrainController() {
		return trainController;
	}

	inline CPointSet& getPointSet() {
		return pts;
	}

	inline Imap& getLabelMap() {
		return labelMap;
	}

	inline CFeatureSet* getFeatureSet() {
		return featureSet;
	}

	inline CFeatureGenerator* getFeatureGenerator() {
		return featureGenerator;
	}

	inline CLabelSet& getLabelSet() {
		return labelSet;
	}

	inline CGALClassifier* getClassifier() {
		return classifier;
	}
};