#include "ClassificationModel.h"

ClassificationModel::ClassificationModel(const std::string& _filePath, const LabelController& _labelController, const FeatureController& _featureController, const EffectController& _effectController)
	: filePath(_filePath), labelController(_labelController), featureController(_featureController), effectController(_effectController), 
	input(nullptr), analysis(nullptr), featureManager(nullptr), classifier(nullptr) {
}

ClassificationModel::~ClassificationModel() {
	if (input != nullptr) delete input;
	if (analysis != nullptr) delete analysis;
	if (featureManager != nullptr) delete featureManager;
	if (classifier != nullptr) delete classifier;
}

void ClassificationModel::run() {

	/*
	// Experimental
	std::string filePath = QFileDialog::getOpenFileName(this, tr("Open Point Cloud File"), "../Data", tr("PLY (*.ply)")).toLocal8Bit().constData();
	Input input(filePath);

	input.getLabelManager().createLabel("ground", CGAL::Color(122, 108, 99));
	input.getLabelManager().createLabel("vegetation", CGAL::Color(0, 255, 0));
	input.getLabelManager().createLabel("roof", CGAL::Color(255, 124, 0));

	float gridResolution = 0.1f; //float gridResolution = 0.34f;
	unsigned int numberOfNeighbors = 200;
	Analysis analysis(input, gridResolution, numberOfNeighbors);

	float radiusNeighbors = 0.1f; //float radiusNeighbors = 1.7f;
	float radiusDtm = 5.0f; //float radiusDtm = 15.0f;
	FeatureManager featureManager(analysis, radiusNeighbors, radiusDtm);

	Classifier classifier(featureManager);

	// Weights
	FeatureHandle distanceToPlane = featureManager.getDistanceToPlane();
	classifier.addWeight(WeightGroup(distanceToPlane, 6.75e-2f));

	FeatureHandle dispersion = featureManager.getDispersion();
	classifier.addWeight(WeightGroup(dispersion, 5.45e-1f));

	FeatureHandle elevation = featureManager.getElevation();
	classifier.addWeight(WeightGroup(elevation, 1.47e1f));

	// Labels
	LabelHandle ground = input.getLabelManager().getLabel("ground").handle;
	classifier.addEffect(EffectGroup(ground, distanceToPlane, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(ground, dispersion, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(ground, elevation, CGALclassifier::PENALIZING));

	LabelHandle vegetation = input.getLabelManager().getLabel("vegetation").handle;
	classifier.addEffect(EffectGroup(vegetation, distanceToPlane, CGALclassifier::FAVORING));
	classifier.addEffect(EffectGroup(vegetation, dispersion, CGALclassifier::FAVORING));
	classifier.addEffect(EffectGroup(vegetation, elevation, CGALclassifier::PENALIZING));

	LabelHandle roof = input.getLabelManager().getLabel("roof").handle;
	classifier.addEffect(EffectGroup(roof, distanceToPlane, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(roof, dispersion, CGALclassifier::NEUTRAL));
	classifier.addEffect(EffectGroup(roof, elevation, CGALclassifier::FAVORING));

	// Classify
	classifier.classify(ClassificationType::RAW);
	classifier.save();
	*/

	input = new Input(filePath);

	// Create labels
	for (LabelView* labelView : labelController.getViews()) {
		QString text = labelView->getText();
		QColor color = labelView->getColor();
		input->getLabelManager().createLabel(text.toLocal8Bit().constData(), CGAL::Color(color.red(), color.green(), color.blue()));
	}

	// Create Analysis
	float gridResolution = 0.1f; //float gridResolution = 0.34f;
	unsigned int numberOfNeighbors = 200;
	Analysis analysis(*input, gridResolution, numberOfNeighbors);

	// Create features
	float radiusNeighbors = 0.1f; //float radiusNeighbors = 1.7f;
	float radiusDtm = 5.0f; //float radiusDtm = 15.0f;
	FeatureManager featureManager(analysis, radiusNeighbors, radiusDtm);

}