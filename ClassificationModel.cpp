#include "ClassificationModel.h"

#include "WProgressDialog.h"

#define FUNC(F, ...) [&]() {F(__VA_ARGS__);}

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

void ClassificationModel::initInput(const std::string& filePath) {
	input = new Input(filePath);
	for (LabelView* labelView : labelController.getViews()) {
		QString text = labelView->getText();
		QColor color = labelView->getColor();
		input->getLabelManager().createLabel(text.toLocal8Bit().constData(), CGAL::Color(color.red(), color.green(), color.blue()));
	}
}

void ClassificationModel::initAnalysis(float gridResolution, unsigned int numberOfNeighbors) {
	analysis = new Analysis(*input, gridResolution, numberOfNeighbors);
}

void ClassificationModel::initFeatureManager(float radiusNeighbors, float radiusDtm) {
	featureManager = new FeatureManager(*analysis, radiusNeighbors, radiusDtm);
	for (FeatureView* featureView : featureController.getViews()) {
		// Get handle
		QString qFeatureName = featureView->getFeatureName();
		std::string featureName = qFeatureName.toLocal8Bit().constData();
		FeatureHandle handle = featureManager->getFeatureHandle(featureName);
		// Join handle and weight
		weightMap.insert(std::pair<FeatureHandle, float>(std::move(handle), featureView->getWeight()));
	}
}

void ClassificationModel::initClassifier() {
	classifier = new Classifier(*featureManager);
}

void ClassificationModel::applyWeights() {
	for (auto& w : weightMap)
		classifier->addWeight(WeightGroup(w.first, w.second));
}

void ClassificationModel::applyEffects() {
	for (EffectView* effectView : effectController.getViews()) {
		// Get handles
		LabelHandle labelHandle = input->getLabelManager().getLabel(effectView->getSelectedLabelName().toLocal8Bit().constData()).handle;
		FeatureHandle featureHandle = featureManager->getFeatureHandle(effectView->getSelectedFeatureName().toLocal8Bit().constData());
		// Apply effects
		if(effectView->getSelectedEffect().toLocal8Bit().constData() == std::string(EFFECT_NEUTRAL))
			classifier->addEffect(EffectGroup(std::move(labelHandle), std::move(featureHandle), CGALclassifier::NEUTRAL));
		else if (effectView->getSelectedEffect().toLocal8Bit().constData() == std::string(EFFECT_PENALIZING))
			classifier->addEffect(EffectGroup(std::move(labelHandle), std::move(featureHandle), CGALclassifier::PENALIZING));
		else if (effectView->getSelectedEffect().toLocal8Bit().constData() == std::string(EFFECT_FAVORING))
			classifier->addEffect(EffectGroup(std::move(labelHandle), std::move(featureHandle), CGALclassifier::FAVORING));
	}
}

void ClassificationModel::run(float gridResolution, unsigned int numberOfNeighbors, float radiusNeighbors, float radiusDtm, const ClassificationType& classificationType) {

	unsigned int max = 4;
	unsigned int progress = 0;

	WProgressDialog progressDialog("Title", "Label", 0, max);

	progressDialog.setLabel("Loading input");
	initInput(filePath);
	progressDialog.setValue(++progress);

	progressDialog.setLabel("Loading features");
	initAnalysis(gridResolution, numberOfNeighbors);
	initFeatureManager(radiusNeighbors, radiusDtm);
	progressDialog.setValue(++progress);

	progressDialog.setLabel("Initializing classification");
	initClassifier();
	applyWeights();
	applyEffects();
	progressDialog.setValue(++progress);

	progressDialog.setLabel("Classifying");
	classifier->classify(classificationType);
	classifier->save();
	progressDialog.setValue(++progress);
}